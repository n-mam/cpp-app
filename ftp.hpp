#include <osl.hpp>

#include <wx/stdpaths.h>
#include <wx/msgdlg.h> 

#include <images/up.xpm>
#include <images/down.xpm>
#include <images/delete.xpm>
#include <images/rename.xpm>

#define ID_LOCAL_BASE 4000
#define ID_REMOTE_BASE 5000

enum class ETransfer : uint8_t
{
  EUpload,
  EDownload
};

using TListElementCbk = std::function<void (TListElement&&)>;
using TDirectoryListCbk = std::function<void (const std::string&, const std::string&)>;

uint64_t g_total = 0, g_complete = 0;

class MyFTP : public FTPPanel
{
  public:

  std::string iHost;
  std::string iUser;
  std::string iPass;
  std::string iPort;

  NPL::SPCProtocolFTP iFTP;
  NPL::SPCProtocolFTP iFTPTransfer;
  std::string iCurrentDirectoryLocal;
  std::string iCurrentDirectoryRemote;

  MyFTP(
    wxWindow* parent,
    wxWindowID id = wxID_ANY,
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxDefaultSize,
    long style = wxTAB_TRAVERSAL)
  : FTPPanel(parent, id, pos, size, style)
  {
    iListViewLocal->Initialize({"Name", "Size", "TS"});
    iListViewRemote->Initialize({"Name", "Size", "TS"});
    iListViewLocal->SetColumnWidth(0, 225);
    iListViewRemote->SetColumnWidth(0, 225);
    UpdateLocalListView(
      wxStandardPaths::Get().GetUserDir(
        wxStandardPaths::Dir::Dir_Desktop).ToStdString());
  }

  virtual ~MyFTP() {}

  virtual void InitiateConnect(std::string host, std::string port, std::string user, std::string pass)
  {
    iHost = host;
    iPort = port;
    iUser = user;
    iPass = pass;

    iFTP = NPL::make_ftp(iHost, wxAtoi(iPort), NPL::TLS::Yes);

    iFTP->SetCredentials(iUser, iPass);

    iFTP->StartClient();

    GetDirectoryList(
      "/",
      [this](const std::string& path, const std::string& list){
        UpdateRemoteListView(path, list);
      });
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
      dir = std::filesystem::path(iCurrentDirectoryLocal).parent_path().string();
    }
    else
    {
      #ifdef WIN32
      dir = iCurrentDirectoryLocal + "\\" + item;
      #else
      dir = iCurrentDirectoryLocal + "/" + item;
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
    TListElementVector files;

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
          iListViewLocal->m_list.push_back({
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
      iListViewLocal->m_list.push_back({e.what(), "", "", EType::ENone});
    }

    iCurrentDirectoryLocal = dir;

    RemoveDuplicates(iCurrentDirectoryLocal, '\\');

    iComboBoxLocal->SetValue(iCurrentDirectoryLocal);

    iListViewLocal->m_list.insert(iListViewLocal->m_list.end(), files.begin(), files.end());

    iListViewLocal->SetItemCount(iListViewLocal->m_list.size());
  }

  // Remote
  virtual void iListViewRemoteOnListItemRightClick(wxListEvent& event)
  {
    auto count = iListViewRemote->GetSelectedItemCount();
    ShowListViewContextMenu(false, count);
  }

  virtual void iComboBoxRemoteOnCombobox(wxCommandEvent& event) { event.Skip(); }

  virtual void iComboBoxRemoteOnTextEnter(wxCommandEvent& event)
  {
    auto path = event.GetString().ToStdString();

    GetDirectoryList(
      path,
      [this](const std::string& path, const std::string& list){
        UpdateRemoteListView(path, list);
      });
  }

  virtual void iListViewRemoteOnListItemActivated(wxListEvent& event)
  {
    auto item = iListViewRemote->GetColumnTextFromEvent(event);

    std::string dir = "";

    if (item == "..")
    {
      dir = std::filesystem::path(iCurrentDirectoryRemote).parent_path().string();
    }
    else
    {
      dir = iCurrentDirectoryRemote + "/" + item;
    }

    RemoveDuplicates(dir, '/');

    GetDirectoryList(
      dir,
      [this](const std::string& dir, const std::string& list){
          UpdateRemoteListView(dir, list);
      });

    event.Skip();
  }

  virtual void UpdateRemoteListView(const std::string& dir, const std::string& list)
  {
    TListElementVector files;

    iListViewRemote->ReInitialize();

    ParseDirectoryListUnix(list, [&](TListElement&& element){
      if (element.e_type == EType::EFile)
      {
        files.push_back(element);
      }
      else if (element.e_type == EType::EFolder)
      {
        iListViewRemote->m_list.push_back(element);
      }
    });

    iCurrentDirectoryRemote = dir;

    RemoveDuplicates(iCurrentDirectoryRemote, '/');

    iComboBoxRemote->SetValue(iCurrentDirectoryRemote);

    iListViewRemote->m_list.insert(iListViewRemote->m_list.end(), files.begin(), files.end());

    iListViewRemote->SetItemCount(iListViewRemote->m_list.size());
  }

  virtual void iListViewLocalOnListItemSelected( wxListEvent& event ) 
  {
    std::string text = std::to_string(iListViewLocal->GetSelectedItemCount()) + " items selected";
    //m_status->SetStatusText(text);
  }

  virtual void iListViewRemoteOnListItemSelected( wxListEvent& event )
  {
    std::string text = std::to_string(iListViewRemote->GetSelectedItemCount()) + " items selected";
    //m_status->SetStatusText(text);
  }

  // common
  void OnListViewContextMenu(wxMouseEvent& e)
  {
    auto id = e.GetId();

    switch(id)
    {
      case ID_LOCAL_BASE: //upload
      {
        auto items = iListViewLocal->GetSelectedItems();

        for (auto& item : items)
        {
          LOG << item.e_name + " : " + std::to_string(static_cast<uint8_t>(item.e_type));
        }

        break;
      }
      case ID_LOCAL_BASE + 1: //rename
      {
        break;
      }
      case ID_LOCAL_BASE + 2: //delete
      {
        auto items = iListViewLocal->GetSelectedItems();

        auto answer = wxMessageBox(
          "Do you want to delete the selected files ?", 
          "Local Delete", wxYES_NO, this);

        if (answer == wxNO) break;

        for (auto& item : items)
        {
          std::error_code ec;
          std::filesystem::remove_all(iCurrentDirectoryLocal + "/" + item.e_name, ec);

          if (ec)
          {
            LOG << ec.message();
          }
          else
          {
            UpdateLocalListView(iCurrentDirectoryLocal);
          }
        }

        break;
      }
      case ID_REMOTE_BASE: //download
      {
        auto items = iListViewRemote->GetSelectedItems();

        if (!items.size()) break;

        if (!iFTPTransfer)
        {
          iFTPTransfer = NPL::make_ftp(iHost, wxAtoi(iPort), NPL::TLS::Yes);
          iFTPTransfer->SetCredentials(iUser, iPass);
          iFTPTransfer->StartClient();
        }

        for (auto& item : items)
        {
          auto local = iCurrentDirectoryLocal + "/" + item.e_name;
          auto remote = iCurrentDirectoryRemote + "/" + item.e_name;

          if (item.e_type == EType::EFolder)
          {
            RemoveDuplicates(remote, '/');
            std::filesystem::create_directory(local);
            TransferFolder(local, remote, ETransfer::EDownload);
          }
          else if (item.e_type == EType::EFile)
          {
            iFTPTransfer->Download(
              [](const char *b, size_t n) {
                // if (!b) LOG << "Download complete";
                return true;
              },
              remote,
              local,
              NPL::DCProt::Protected
            );
          }
        }

        break;
      }
      case ID_REMOTE_BASE + 1: //rename
      {
        break;
      }
      case ID_REMOTE_BASE + 2: //delete
      {
        auto items = iListViewRemote->GetSelectedItems();

        auto answer = wxMessageBox(
          "Do you want to delete the selected files ?", 
          "Remote Delete", wxYES_NO, this);

        if (answer == wxNO) break;

        break;
      }
    }
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

    lvMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFTP::OnListViewContextMenu, NULL, this);

    PopupMenu(lvMenu);
  }

  void GetDirectoryList(const std::string& dir, TDirectoryListCbk cbk)
  {
    iFTP->ListDirectory(
      [list = std::string(), dir, cbk] (const char *b, size_t n) mutable
      {
        if (b)
        {
          list.append(std::string(b, n));
        }
        else
        {
          if (cbk) cbk(dir, list);
        }
        return true;
      },
      dir,
      NPL::DCProt::Protected
    );
  }

  void ParseDirectoryListUnix(const std::string& list, TListElementCbk cbk)
  {
    std::string line;
    std::istringstream ss(list);

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

      if (cbk) cbk({name, size, ts, type});
    }
  }

  void TransferFolder(const std::string& local, const std::string& remote, ETransfer direction)
  {
    g_total = g_complete = 0;

    GetDirectoryList(remote,
      [this, local, direction](const std::string& path, const std::string& list) 
      {
        // list for path
        ParseDirectoryListUnix(list,
          [this, local, path, direction](TListElement&& e)
          {
            if (e.e_type == EType::EFolder)
            {
              std::filesystem::create_directory(local + "/" + e.e_name);
              TransferFolder(local + "/" + e.e_name, path + "/" + e.e_name, direction);
            }
            else
            {
              if (direction == ETransfer::EDownload)
              {
                std::string text = "status Total Files : " + 
                                   std::to_string(++g_total) + 
                                   ", Finished : " + std::to_string(g_complete);
                LOG << text;

                iFTPTransfer->Download(
                  [](const char *b, size_t n) {
                    if (!b)
                    {
                      std::string text = "status Total Files : " + 
                                         std::to_string(g_total) + 
                                         ", Finished : " + 
                                         std::to_string(++g_complete);
                      LOG << text;                     
                    }
                    return true;
                  },
                  path + "/" + e.e_name,
                  local + "/" + e.e_name,
                  NPL::DCProt::Protected
                );
              }
              else if (direction == ETransfer::EUpload)
              {

              }
            }
        });
      });

  }
};