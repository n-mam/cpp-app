#include "AppFrame.h"
#include "MyList.h"
#include "ftp.hpp"

#include <fstream>

#include "images/host.xpm"

#define ID_LOG_BASE 2000

struct TListSessionElement
{
  wxString e_host;
  wxString e_prot;
  wxString e_port;
  wxString e_user;
  wxString e_pass;
};

using TListSessionElementVector = std::vector<TListSessionElement>;

class MyFrame : public AppFrame
{
  public:

  MyFrame(
    wxWindow* parent,
    wxWindowID id = wxID_ANY,
    const wxString& title = _("app"),
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxSize( 700,550 ),
    long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)
  : AppFrame(parent, id, title, pos, size, style)
  {
    iListViewSavedSessions->Initialize(
      {"Host", "Protocol", "Port", "Username", "Password"},
      [this] (long item, long column) {
        std::string text;
        if (column == 0)
          text = m_slist[item].e_host;
        else if (column == 1)
          text = m_slist[item].e_prot;
        else if (column == 2)
          text = m_slist[item].e_port;
        else if (column == 3)
          text = m_slist[item].e_user;
        else if (column == 4)
          text = m_slist[item].e_pass;
        return text;
      },
      [this](long item, long column)
      {
        if (column == 0)
        { 
          return 0;
        }
        return -1;
      }
    );
    iListViewSavedSessions->SetColumnWidth(0, 150);
    iListViewSavedSessions->SetColumnWidth(1, 70);
    iListViewSavedSessions->SetColumnWidth(2, 50);
    //https://trac.wxwidgets.org/ticket/18393
    //iListViewSavedSessions->EnableCheckBoxes(true);
    LoadConfiguration("C:/Users/Divya Surana/Desktop/cfg.txt");
    iListViewSavedSessions->SetItemCount(m_slist.size());
    m_splitter->Unsplit(m_panel6);
    m_host->SetFocus();
  }
 
  virtual ~MyFrame() {}

  TListSessionElementVector m_slist;

  protected:

  std::vector<std::pair<int, wxPanel *>> iSessionPanels;

  void onToolClicked( wxCommandEvent& event )
  {
    m_book->SetSelection(event.GetId() % ID_PAGE_BASE);
  }
 
  void m_traceOnCheckBox( wxCommandEvent& event )
  {
    if (event.IsChecked()) {
      m_splitter->SplitHorizontally(m_panel6, m_panel8, 140);
    } else {
      m_splitter->Unsplit(m_panel6);
    }
  }

  TListSessionElement GetSessionDetails(void)
  {
    auto host = m_host->GetValue();
    auto port = m_port->GetValue();
    auto user = m_user->GetValue();
    auto pass = m_pass->GetValue();
    auto prot = m_protocol->GetString(
      m_protocol->GetSelection());

    if (!host.size() || !user.size() || !pass.size() || !port.size() || !prot.size())
    {
      wxMessageBox(
       "Please specify all the values", 
        "Error", wxOK, this);
      return {};
    }

    m_host->Clear();
    m_port->Clear();
    m_user->Clear();
    m_pass->Clear();

    return {host, prot, port, user, pass};
  }

  virtual void m_saveOnButtonClick( wxCommandEvent& event )
  {
    auto session = GetSessionDetails();
    if (!session.e_host.size()) return;
    iListViewSavedSessions->ReInitialize();
    m_slist.push_back(session);
    iListViewSavedSessions->SetItemCount(m_slist.size());
  }

  virtual void iListViewSavedSessionsOnListItemActivated(wxListEvent& event)
  { 
    auto host = iListViewSavedSessions->GetColumnTextFromEvent(event, 0);
    auto prot = iListViewSavedSessions->GetColumnTextFromEvent(event, 1);
    auto port = iListViewSavedSessions->GetColumnTextFromEvent(event, 2);
    auto user = iListViewSavedSessions->GetColumnTextFromEvent(event, 3);
    auto pass = iListViewSavedSessions->GetColumnTextFromEvent(event, 4);
    LaunchSession({host, prot, port, user, pass});
  }

  virtual void m_connectOnButtonClick(wxCommandEvent& event)
  {
    std::vector<TListSessionElement> list;

    // quick connect session
    auto sess = GetSessionDetails();

    if (sess.e_host.size())
    {
      list.push_back(sess);
    }

    // checked sessions from the saved sessions

    if (!list.size()) return;

    for (auto& session : list)
    {
      LaunchSession(session);
    }
  }

  void LaunchSession(const TListSessionElement& session)
  {
    wxPanel *page = nullptr;

    if (session.e_prot == "FTP") 
    {
      page = new MyFTP(m_book);
    }
    else if (session.e_prot == "SSH")
    {
      //page = new MySSH(m_book);
    }
 
    if (!page) return;

    auto id = ID_PAGE_BASE + 1 + iSessionPanels.size();

    iSessionPanels.push_back({id, page});

    m_book->ShowNewPage(page);

    auto tool = m_toolBar->AddTool(id, session.e_prot + "@" + session.e_host, wxBitmap(host_xpm), wxNullBitmap, wxITEM_RADIO);

    tool->Toggle();

    m_toolBar->Realize();

    this->Connect(tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MyFrame::onToolClicked));

    if (session.e_prot == "FTP") 
    {
      auto ftppage = dynamic_cast<MyFTP *>(page);
        ftppage->InitiateConnect(
          session.e_host.ToStdString(),
          session.e_port.ToStdString(),
          session.e_user.ToStdString(),
          session.e_pass.ToStdString());
    }
  }

  void m_logOnRightDown(wxMouseEvent& event)
  {
    wxMenu *logMenu = new wxMenu();

    wxMenuItem *itemSave = new wxMenuItem(logMenu, ID_LOG_BASE, wxString(_("Save")), wxEmptyString, wxITEM_NORMAL);
    logMenu->Append(itemSave);

    wxMenuItem *itemClear = new wxMenuItem(logMenu, ID_LOG_BASE + 1, wxString(_("Clear")) , wxEmptyString, wxITEM_NORMAL);
    logMenu->Append(itemClear);

    logMenu->Connect(wxEVT_COMMAND_MENU_SELECTED, (wxObjectEventFunction) &MyFrame::OnLogContextMenu, NULL, this);

    PopupMenu(logMenu);
  }

  void OnLogContextMenu(wxMouseEvent& e)
  {
    auto id = e.GetId();

    switch(id)
    {
      case ID_LOG_BASE:  //save
      {

        break;
      }
      case ID_LOG_BASE + 1: //clear
      {
        m_log->Clear();
        m_log->Update();
        break;
      }
    }
  }

  void LoadConfiguration(std::string const& filepath)
  {
    std::ifstream is(filepath);

    if (!is) return;

    is.seekg(0, is.end);
    int length = is.tellg();
    is.seekg(0, is.beg);

    char *buffer = new char [length];

    is.read(buffer, length);

    is.close();

    ParseConfiguration(buffer);

    delete[] buffer;
  }

  void ParseConfiguration(char * buf)
  {
    std::string line;
    std::istringstream ss(buf);
    TListSessionElement session;

    while (std::getline(ss, line))
    {
      size_t index = line.find(":");

      if (index != std::string::npos)
      {
        wxString key, val;

        key = line.substr(0, index);
        val = line.substr(index + 1);

        key.Trim(true);
        key.Trim(false);
        val.Trim(true);
        val.Trim(false);

        if (key.CmpNoCase("Host") == 0) {
          session.e_host = val;
        } else if (key.CmpNoCase("Port") == 0) {
          session.e_port = val;
        } else if (key.CmpNoCase("User") == 0) {
          session.e_user = val;
        } else if (key.CmpNoCase("Pass") == 0) {
          session.e_pass = val;
        } else if (key.CmpNoCase("Prot") == 0) {
          session.e_prot = val;
        }
      }

      if (session.e_host.size() && 
          session.e_user.size() && 
          session.e_pass.size() && 
          session.e_port.size() && 
          session.e_prot.size())
      {
        m_slist.push_back(session);
        session.e_host.Clear();
        session.e_user.Clear();
        session.e_pass.Clear();
        session.e_port.Clear();
        session.e_prot.Clear();
      }
    }
  }
};