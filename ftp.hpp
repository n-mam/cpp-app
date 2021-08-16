#include <osl.hpp>

#include <wx/stdpaths.h>
#include <wx/msgdlg.h>

#include <images/up.xpm>
#include <images/down.xpm>
#include <images/delete.xpm>
#include <images/rename.xpm>

#define ID_LOCAL_BASE 4000
#define ID_REMOTE_BASE 5000

enum class EOperation : uint8_t
{
  EDelete,
  EUpload,
  EDownload
};

enum class EType : uint8_t
{
  ENone,
  EFile,
  EFolder,
  ESymlinkFile,
  ESymlinkFolder
};

struct TListFTPElement
{
  std::string e_name;
  std::string e_size;
  std::string e_ts;
  EType e_type;
};

using TListFTPElementVector = std::vector<TListFTPElement>;
using TListFTPElementVectorCallback = std::function<void (const TListFTPElementVector&)>;
using TWalkRemoteCallback = std::function<void (const std::string&, const TListFTPElementVector&)>;
using TDirectoryListCbk = std::function<void (const std::string&, const std::string&)>;

class MyFTP : public FTPPanel, public TSession
{
  public:

  NPL::SPCProtocolFTP iFTP;
  NPL::SPCProtocolFTP iFTPTransfer;
  std::string iCurrentLocalDirectory;
  std::string iCurrentRemoteDirectory;

  TListFTPElementVector m_llist;
  TListFTPElementVector m_rlist;

  MyFTP(
    wxWindow* parent,
    wxWindowID id = wxID_ANY,
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = wxTAB_TRAVERSAL)
  : FTPPanel(parent, id, pos, size, style)
  {
    iListViewLocal->Initialize(
      {"Name", "Size", "TS"},
      [this] (long item, long column) {
        return OnListGetItemText(m_llist, item, column);
      },
      [this](long item, long column) 
      {
        return OnListGetItemImage(m_llist, item, column);
      }
    );

    iListViewRemote->Initialize(
      {"Name", "Size", "TS"},
      [this] (long item, long column) {
        return OnListGetItemText(m_rlist, item, column);
      },
      [this](long item, long column) 
      {
        return OnListGetItemImage(m_rlist, item, column);
      }
    );

    iListViewLocal->SetColumnWidth(0, 225);
    iListViewRemote->SetColumnWidth(0, 225);

    UpdateLocalListView(
      wxStandardPaths::Get().GetUserDir(
        wxStandardPaths::Dir::Dir_Desktop
      ).ToStdString()
    );
  }

  virtual ~MyFTP()
  {
    StopSession();
  }

  virtual void StartSession(void)
  {
    iFTP = NPL::make_ftp(m_host.ToStdString(), wxAtoi(m_port), m_ccTls);

    iFTP->SetCredentials(m_user.ToStdString(), m_pass.ToStdString());

    iFTP->StartClient();

    GetDirectoryList(
      "/",
      [this](const std::string& path, const std::string& list) {
        UpdateRemoteListView(path, list);
      }
    );
  }

  protected:

  // Local
  virtual void iComboBoxLocalOnCombobox(wxCommandEvent& event) { event.Skip(); }

  virtual void iComboBoxLocalOnTextEnter(wxCommandEvent& event)
  {
    UpdateLocalListView(event.GetString().ToStdString());
  }

  virtual void iListViewLocalOnListItemActivated(wxListEvent& event)
  {
    auto item = iListViewLocal->GetColumnTextFromEvent(event);

    std::string dir = "";

    if (item == "..")
    {
      dir = std::filesystem::path(iCurrentLocalDirectory).parent_path().string();
    }
    else
    {
      #ifdef WIN32
      dir = iCurrentLocalDirectory + "\\" + item;
      #else
      dir = iCurrentLocalDirectory + "/" + item;
      #endif
    }

    if (std::filesystem::is_directory(dir))
    {
      UpdateLocalListView(dir);
    }

    event.Skip();
  }

  virtual void iListViewLocalOnListItemRightClick(wxListEvent& event)
  {
    auto count = iListViewLocal->GetSelectedItemCount();
    ShowListViewContextMenu(true, count);
  }

  virtual void UpdateLocalListView(const std::string& dir)
  {
    TListFTPElementVector files;

    m_llist.clear();
    m_llist.push_back({
      "..", "", "", EType::EFolder
    });
    iListViewLocal->ReInitialize();

    try
    {
      for (auto& e : std::filesystem::directory_iterator(dir))
      {
        std::error_code ec;

        if (std::filesystem::is_symlink(e, ec))
        {
          files.push_back({
            e.path().filename().string(),
            "",
            "10:25:47",
            EType::ESymlinkFile
          });
        }
        else if (std::filesystem::is_directory(e, ec))
        {
          m_llist.push_back({
            e.path().filename().string(),
            "",
            "10:25:47",
            EType::EFolder
          });
        }
        else
        {
          std::uintmax_t size = std::filesystem::file_size(e, ec);

          if (ec)
          {
            size = 0;
          }

          files.push_back({
            e.path().filename().string(),
            size ? std::to_string(size) : "",
            "10:25:47",
            EType::EFile
          });
        }
      }
    }
    catch(const std::exception& e)
    {
      m_llist.push_back({e.what(), "", "", EType::ENone});
    }

    iCurrentLocalDirectory = dir;

    RemoveDuplicates(iCurrentLocalDirectory, '\\');

    iComboBoxLocal->SetValue(iCurrentLocalDirectory);

    m_llist.insert(m_llist.end(), files.begin(), files.end());

    iListViewLocal->SetItemCount(m_llist.size());
  }

  virtual void iListViewLocalOnListItemSelected(wxListEvent& event) 
  {
    std::string text = std::to_string(iListViewLocal->GetSelectedItemCount()) + " items selected";
    //m_status->SetStatusText(text);
  }

  // Remote
  virtual void iComboBoxRemoteOnCombobox(wxCommandEvent& event) { event.Skip(); }

  virtual void iComboBoxRemoteOnTextEnter(wxCommandEvent& event)
  {
    auto path = event.GetString().ToStdString();

    GetDirectoryList(
      path,
      [this](const std::string& path, const std::string& list) {
        UpdateRemoteListView(path, list);
      });
  }

  virtual void iListViewRemoteOnListItemActivated(wxListEvent& event)
  {
    auto item = iListViewRemote->GetColumnTextFromEvent(event);

    std::string dir = "";

    if (item == "..")
    {
      dir = std::filesystem::path(iCurrentRemoteDirectory).parent_path().string();
    }
    else
    {
      dir = iCurrentRemoteDirectory + "/" + item;
    }

    RemoveDuplicates(dir, '/');

    GetDirectoryList(
      dir,
      [this](const std::string& dir, const std::string& list) {
        UpdateRemoteListView(dir, list);
      });

    event.Skip();
  }

  virtual void iListViewRemoteOnListItemRightClick(wxListEvent& event)
  {
    auto count = iListViewRemote->GetSelectedItemCount();
    ShowListViewContextMenu(false, count);
  }

  virtual void UpdateRemoteListView(const std::string& dir, const std::string& list)
  {
    TListFTPElementVector files;

    m_rlist.clear();
    m_rlist.push_back({
      "..", "", "", EType::EFolder
    });

    iListViewRemote->ReInitialize();

    auto elements = ParseDirectoryListUnix(list);

    for (auto& e : elements)
    {
      if (e.e_type == EType::EFile)
      {
        files.push_back(e);
      }
      else if (e.e_type == EType::EFolder)
      {
        m_rlist.push_back(e);
      }
    }

    iCurrentRemoteDirectory = dir;

    RemoveDuplicates(iCurrentRemoteDirectory, '/');

    iComboBoxRemote->SetValue(iCurrentRemoteDirectory);

    m_rlist.insert(m_rlist.end(), files.begin(), files.end());

    iListViewRemote->SetItemCount(m_rlist.size());
  }

  virtual void iListViewRemoteOnListItemSelected(wxListEvent& event)
  {
    std::string text = std::to_string(iListViewRemote->GetSelectedItemCount()) + " items selected";
    //m_status->SetStatusText(text);
  }

  // common
  virtual wxString OnListGetItemText(TListFTPElementVector& list, long item, long column)
  {
    wxString text;
    if (column == 0)
      text = list[item].e_name;
    else if (column == 1)
      text = list[item].e_size;
     else if (column == 2)
      text = list[item].e_ts;
    return text;
  }

  virtual int OnListGetItemImage(TListFTPElementVector& list, long item, long column)
  {
    int idx = -1;
    if (column == 0)
    {
      auto type = list[item].e_type;

      if (type == EType::EFile)
        idx = 0;
      else if (type == EType::EFolder)
        idx = 1;
    }
    return idx;
  }

  void ShowListViewContextMenu(bool local, int count)
  {
    int id;
    wxString direction;
    
    if (local)
    {
      id = ID_LOCAL_BASE;
      direction = wxString(_("Upload"));
    }
    else
    {
      id = ID_REMOTE_BASE;
      direction = wxString(_("Download"));
    }

    wxMenu *lvMenu = new wxMenu();

    wxMenuItem *itemAction = new wxMenuItem(lvMenu, id, direction, wxEmptyString, wxITEM_NORMAL);
    itemAction->SetBitmap(local ? wxBitmap(up_xpm) : wxBitmap(down_xpm));
    lvMenu->Append(itemAction), id++;

    if (count == 1)
    {
      wxMenuItem *itemRename = new wxMenuItem(lvMenu, id, wxString(_("Rename")) , wxEmptyString, wxITEM_NORMAL);
      itemRename->SetBitmap(wxBitmap(rename_xpm));
      lvMenu->Append(itemRename);
    }

    lvMenu->AppendSeparator(), id++;

    wxMenuItem *itemDelete = new wxMenuItem(lvMenu, id, wxString(_("Delete")) , wxEmptyString, wxITEM_NORMAL);
    itemDelete->SetBitmap(wxBitmap(delete_xpm));
    lvMenu->Append(itemDelete), id++;

    wxMenuItem *itemWalk = new wxMenuItem(lvMenu, id, wxString(_("Walk")) , wxEmptyString, wxITEM_NORMAL);
    lvMenu->Append(itemWalk), id++;

    lvMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFTP::OnListViewContextMenu, NULL, this);

    PopupMenu(lvMenu);
  }

  void OnListViewContextMenu(wxMouseEvent& e)
  {
    switch (e.GetId())
    {
      case ID_LOCAL_BASE: // upload
      {
        InitiateOperation(iListViewLocal, m_llist, EOperation::EUpload);
        break;
      }
      case ID_LOCAL_BASE + 1: // rename
      {
        break;
      }
      case ID_LOCAL_BASE + 2: // delete
      {
        auto answer = wxMessageBox(
          "Do you want to delete the selected items ?", 
          "Local Delete", wxYES_NO, this);

        if (answer == wxNO) break;

        auto items = iListViewLocal->GetSelectedItemIndexes();

        for (auto& item : items)
        {
          std::error_code ec;
          std::filesystem::remove_all(iCurrentLocalDirectory + "/" + m_llist[item].e_name, ec);

          if (ec) {
            LOG << ec.message();
          } else {
            UpdateLocalListView(iCurrentLocalDirectory);
          }
        }

        break;
      }
      case ID_REMOTE_BASE: // download
      {
        InitiateOperation(iListViewRemote, m_rlist, EOperation::EDownload);
        break;
      }
      case ID_REMOTE_BASE + 1: //rename
      {
        break;
      }
      case ID_REMOTE_BASE + 2: //delete
      {
        auto answer = wxMessageBox(
          "Do you want to delete the selected files ?", 
          "Remote Delete", wxYES_NO, this);

        if (answer == wxNO) break;

        InitiateOperation(iListViewRemote, m_rlist, EOperation::EDelete);

        GetDirectoryList(
          iCurrentRemoteDirectory,
          [this](const std::string& path, const std::string& list) {
            UpdateRemoteListView(path, list);
          });

        break;
      }
      case ID_REMOTE_BASE + 3: // walk
      {
        auto items = iListViewRemote->GetSelectedItemIndexes();

        for (auto& item : items)
        {
          if (m_rlist[item].e_type == EType::EFolder)
          {
            WalkRemoteFolder(m_rlist[item].e_name,
              [](const std::string& folder, const TListFTPElementVector& elements) {
                LOG << "Listing : " + folder;
                for (auto& e : elements) {
                  if (e.e_type == EType::EFile)
                    LOG << "File : " + e.e_name;
                  if (e.e_type == EType::EFolder)
                    LOG << "Folder : " + e.e_name;
                }
              }
            );
          }
          else
          {
            LOG << "File : " + m_rlist[item].e_name;
          }
        }
      }
    }
  }

  void InitiateOperation(MyList *lv, TListFTPElementVector& list, EOperation op)
  {
    auto items = lv->GetSelectedItemIndexes();

    if (!items.size()) return;

    if (!iFTPTransfer)
    {
      iFTPTransfer = NPL::make_ftp(m_host.ToStdString(), wxAtoi(m_port), m_ccTls);
      iFTPTransfer->SetCredentials(m_user.ToStdString(), m_pass.ToStdString());
      iFTPTransfer->StartClient();
    }

    for (auto& item : items)
    {
      auto local = iCurrentLocalDirectory + "/" + list[item].e_name;
      auto remote = iCurrentRemoteDirectory + "/" + list[item].e_name;

      RemoveDuplicates(remote, '/');

      if (list[item].e_type == EType::EFolder)
      {
        if (op == EOperation::EDownload) {
          WalkRemoteFolder(remote,
            [this](const std::string& folder, const TListFTPElementVector& elements) {
              // root   : /123/1
              // folder : /123/1 /123/1/11  /123/1/11/111
              auto subpath = Replace(folder, iCurrentRemoteDirectory, "");
              auto llocal = iCurrentLocalDirectory + "/" + subpath;
              std::filesystem::create_directory(llocal);

              for (auto& e : elements) {
                if (e.e_type == EType::EFile) {
                  iFTPTransfer->Download(
                    [](const char *b, size_t n) { return true; },
                    folder + "/" + e.e_name,
                    llocal + "/" + e.e_name,
                    m_dcTls);
                }
              }
            }
          );
        }
        else if (op == EOperation::EUpload) {
          iFTPTransfer->CreateDir(remote, nullptr);
          WalkLocalFolder(local, remote);
        } else if (op == EOperation::EDelete) {
          WalkRemoteFolder(remote,
            [this, remote](const std::string& path, const TListFTPElementVector& elements) {
              for (auto& e : elements) {
                if (e.e_type == EType::EFile) {
                  iFTPTransfer->RemoveFile(path + "/" + e.e_name, nullptr);
                }
              }
            });
        }
      }
      else if (list[item].e_type == EType::EFile)
      {
        if (op == EOperation::EDownload) {
          iFTPTransfer->Download(
            [](const char *b, size_t n) {
              // if (!b) LOG << "Download complete";
              return true;
            }, remote, local, m_dcTls);
        }
        else if (op == EOperation::EUpload) {
          iFTPTransfer->Upload(
            [](const char *b, size_t n) {
              return true;
            }, remote, local, m_dcTls);
        }
        else if (op == EOperation::EDelete) {
          iFTPTransfer->RemoveFile(remote, nullptr);
        }
      }
    }
  }

  void GetDirectoryList(const std::string& dir, TDirectoryListCbk cbk)
  {
    iFTP->ListDirectory(
      [list = std::string(), dir, cbk] (const char *b, size_t n) mutable {
        if (b) {
          list.append(std::string(b, n));
        } else {
          if (cbk) cbk(dir, list);
        }
        return true;
      },
      dir,
      m_dcTls
    );
  }

  TListFTPElementVector ParseDirectoryListUnix(const std::string& list)
  {
    std::string line;
    std::istringstream ss(list);
    TListFTPElementVector elements;

    while (std::getline(ss, line, '\n'))
    {
      line.pop_back();

      // -rwxr-xr-x     1 ftp ftp       29325064 Mar 07  2021 TeamViewer Setup.exe

      std::string t;
      std::vector<std::string> tokens;

      for (int i = 0; i < line.size(); i++)
      {
        auto c = line[i];

        if (c != ' ')
        {
          t += c;
        }
        else if (t.size())
        {
          tokens.push_back(t);
          t.clear();
        }
        
        if (tokens.size() == 8)
        {
          tokens.push_back(line.substr(i + 1));
          break;
        }
      }

      //for (auto& e: tokens) std::cout << e << std::endl;

      auto name = tokens[8];
      auto size = tokens[4];
      auto attrib = tokens[0];
      auto ts = tokens[5] + " " + tokens[6] + " " + tokens[7];

      auto type = EType::ENone;

      if (attrib[0] == '-')
      {
        type = EType::EFile;
      }
      else if (attrib[0] == 'd')
      {
        type = EType::EFolder;
      }

      elements.push_back({name, size, ts, type});
    }

    return elements;
  }

  void WalkRemoteFolder(const std::string& root, TWalkRemoteCallback cbk)
  {
    GetDirectoryList(root,
      [this, cbk] (const std::string& path, const std::string& list) {
        auto elements = ParseDirectoryListUnix(list);
        cbk(path, elements);
        for (auto& e : elements) {
          if (e.e_type == EType::EFolder) {
            WalkRemoteFolder(path + "/" + e.e_name, cbk);
          }
        }
      });
  }

  void WalkLocalFolder(const std::string& local, const std::string& remote)
  {
    try
    {
      for (auto& e : std::filesystem::directory_iterator(local))
      {
        std::error_code ec;

        if (std::filesystem::is_regular_file(e, ec))
        {
          iFTPTransfer->Upload(
            [](const char *b, size_t n) { return true; },
            remote + "/" + e.path().filename().string(),
            local + "/" + e.path().filename().string(),
            m_dcTls);
        }
        else if (std::filesystem::is_directory(e, ec))
        {
          iFTPTransfer->CreateDir(remote + "/" + e.path().filename().string(), nullptr);
          WalkLocalFolder(
            local + "/" + e.path().filename().string(),
            remote + "/" + e.path().filename().string()
          );
        }
        else
        {
          LOG << "WalkLocalFolder neither file nor folder";
        }
      }
    }
    catch(const std::exception& e)
    {
      LOG << "WalkLocalFolder exception : "s + e.what();
    }
  }

  virtual void FTPPanelOnSize( wxSizeEvent& event )
  {
    auto size = event.GetSize();
    m_splitter->SetSashPosition(size.GetWidth()/2 );
    event.Skip();
  }
};