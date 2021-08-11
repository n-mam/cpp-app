#include "AppFrame.h"
#include "MyList.h"
#include "ftp.hpp"

#include <fstream>

#include "images/host.xpm"

#define ID_LOG_BASE 2000
 
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
      {"Host", "Port", "Protocol", "Username", "Password"});
    iListViewSavedSessions->SetColumnWidth(0, 150);
    iListViewSavedSessions->SetColumnWidth(1, 50);
    iListViewSavedSessions->SetColumnWidth(2, 65);
    iListViewSavedSessions->EnableCheckBoxes(true);
    LoadConfiguration("C:/Users/Divya Surana/Desktop/cfg.txt");
    m_splitter->Unsplit(m_panel6);
    m_host->SetFocus();
  }

  virtual ~MyFrame() {}

  protected:

  struct TSessionDetails
  {
    wxString host;
    wxString port;
    wxString user;
    wxString pass;
    wxString prot;
  };

  std::vector<std::pair<int, wxPanel *>> iSessionPanels;

  void onToolClicked( wxCommandEvent& event )
  {
    m_book->SetSelection(event.GetId() % ID_PAGE_BASE);
  }
 
  void m_traceOnCheckBox( wxCommandEvent& event )
  {
    if (event.IsChecked()) {
      m_splitter->SplitHorizontally(m_panel6, m_panel8, 150);
    } else {
      m_splitter->Unsplit(m_panel6);
    }
  }

  TSessionDetails GetSessionDetails(void)
  {
    auto host = m_host->GetValue();
    auto port = m_port->GetValue();
    auto user = m_user->GetValue();
    auto pass = m_password->GetValue();
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
    m_password->Clear();

    return {host, port, user, pass, prot};
  }

  virtual void m_saveOnButtonClick( wxCommandEvent& event )
  {
    auto session = GetSessionDetails();
    if (!session.host.size()) return;
    ShowSavedSession(session);
  }

  void ShowSavedSession(TSessionDetails session)
  {
    auto [host, port, user, pass, prot] = session;

    auto idx = iListViewSavedSessions->InsertItem(
      iListViewSavedSessions->GetItemCount(), host);

    iListViewSavedSessions->SetItem(idx, 1, port);
    iListViewSavedSessions->SetItem(idx, 2, prot);
    iListViewSavedSessions->SetItem(idx, 3, user);
    iListViewSavedSessions->SetItem(idx, 4, pass);
  }

  virtual void iListViewSavedSessionsOnListItemActivated( wxListEvent& event )
  { 
    auto host = iListViewSavedSessions->GetColumnTextFromEvent(event, 0);
    auto port = iListViewSavedSessions->GetColumnTextFromEvent(event, 1);
    auto prot = iListViewSavedSessions->GetColumnTextFromEvent(event, 2);
    auto user = iListViewSavedSessions->GetColumnTextFromEvent(event, 3);
    auto pass = iListViewSavedSessions->GetColumnTextFromEvent(event, 4);
    LaunchSession({host, port, user, pass, prot});
  }

  virtual void m_connectOnButtonClick( wxCommandEvent& event )
  {
    std::vector<TSessionDetails> list;

    // quick connect session
    auto sess = GetSessionDetails();

    if (sess.host.size())
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

  void LaunchSession(const TSessionDetails& session)
  {
    wxPanel *page = nullptr;

    if (session.prot == "FTP") 
    {
      page = new MyFTP(m_book);
    }
    else if (session.prot == "SSH")
    {
      //page = new MySSH(m_book);
    }
 
    if (!page) return;

    auto id = ID_PAGE_BASE + 1 + iSessionPanels.size();

    iSessionPanels.push_back({id, page});

    m_book->ShowNewPage(page);

    auto tool = m_toolBar->AddTool(id, session.prot + "@" + session.host, wxBitmap(host_xpm), wxNullBitmap, wxITEM_RADIO);

    tool->Toggle();

    m_toolBar->Realize();

    this->Connect(tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MyFrame::onToolClicked));

    if (session.prot == "FTP") 
    {
      auto ftppage = dynamic_cast<MyFTP *>(page);
        ftppage->InitiateConnect(
          session.host.ToStdString(),
          session.port.ToStdString(),
          session.user.ToStdString(),
          session.pass.ToStdString());
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
    std::ifstream is(filepath, std::ifstream::binary);

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
    TSessionDetails session;

    while (std::getline(ss, line, '\n'))
    {
      if (line.back() == '\n') 
        line.pop_back();

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
          session.host = val;
        } else if (key.CmpNoCase("Port") == 0) {
          session.port = val;
        } else if (key.CmpNoCase("User") == 0) {
          session.user = val;
        } else if (key.CmpNoCase("Pass") == 0) {
          session.pass = val;
        } else if (key.CmpNoCase("Prot") == 0) {
          session.prot = val;
        }
      }

      if (session.host.size() && 
          session.user.size() && 
          session.pass.size() && 
          session.port.size() && 
          session.prot.size())
      {
        ShowSavedSession(session);
        session.host.Clear();
        session.user.Clear();
        session.pass.Clear();
        session.port.Clear();
        session.prot.Clear();
      }
    }
  }
};