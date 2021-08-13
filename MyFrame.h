#include "AppFrame.h"
#include "TSession.h"
#include "MyList.h"
#include "ftp.hpp"

#include <fstream>

#define ID_LOG_BASE 2000

using TListSessionVector = std::vector<TSession>;

class MyFrame : public AppFrame
{
  public:

  MyFrame(
    wxWindow* parent,
    wxWindowID id = wxID_ANY,
    const wxString& title = _("app"),
    const wxPoint& pos = wxDefaultPosition,
    const wxSize& size = wxSize( 735,600 ),
    long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)
  : AppFrame(parent, id, title, pos, size, style)
  {
    iListViewSavedSessions->Initialize(
      {"Host", "Protocol", "Port", "Username"},
      [this] (long item, long column) {
        std::string text;
        if (column == 0)
          text = m_slist[item].m_host;
        else if (column == 1)
          text = m_slist[item].m_prot;
        else if (column == 2)
          text = m_slist[item].m_port;
        else if (column == 3)
          text = m_slist[item].m_user;
        return text;
      },
      [this](long item, long column)
      {
        if (column == 0)
          return 2;
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
    m_panelDCProt->Enable(false);
    //m_splitter->Unsplit(m_panel6);
    m_host->SetFocus(); 
  }

  virtual ~MyFrame() {}

  TListSessionVector m_slist;

  protected:

  virtual void m_saveOnButtonClick(wxCommandEvent& event)
  {
    auto session = GetSessionDetails();

    if (!session.m_host.size()) return;

    std::stringstream ss;

    ss << "Host : " << session.m_host << "\n";
    ss << "Port : " << session.m_port << "\n";
    ss << "User : " << session.m_user << "\n";
    ss << "Pass : " << session.m_pass << "\n";
    auto szFlags = std::to_string(
      static_cast<int>(session.m_ccTls) | (1 << static_cast<int>(session.m_dcTls))
    );
    ss << "TLS : "  << szFlags << "\n";
    ss << "Prot : " << session.m_prot << "\n\n";

    WriteConfiguration("C:/Users/Divya Surana/Desktop/cfg.txt", ss.str());

    iListViewSavedSessions->ReInitialize();
    m_slist.push_back(session);
    iListViewSavedSessions->SetItemCount(m_slist.size());
  }

  virtual void m_connectOnButtonClick(wxCommandEvent& event)
  {
    std::vector<TSession> list;

    // quick connect session
    auto session = GetSessionDetails();

    if (session.m_host.size())
    {
      list.push_back(session);
    }

    // checked sessions from the saved sessions
    //https://trac.wxwidgets.org/ticket/18393

    if (!list.size()) return;

    for (auto& s : list)
    {
      LaunchSession(s);
    }
  }

  TSession GetSessionDetails(void)
  {
    TSession session;

    session.m_host = m_host->GetValue();
    session.m_port = m_port->GetValue();
    session.m_user = m_user->GetValue();
    session.m_pass = m_pass->GetValue();
    session.m_prot = m_protocol->GetString(
      m_protocol->GetSelection());

    if (!session.m_host.size() ||
        !session.m_port.size() || 
        !session.m_user.size() || 
        !session.m_pass.size() || 
        !session.m_prot.size())
    {
      wxMessageBox(
       "Please specify all the values", 
       "Error", wxOK, this);
      return {};
    }

    session.m_ccTls = NPL::TLS::No;
    session.m_dcTls = NPL::TLS::No;

    if (session.m_prot == "FTP")
    {
      if (m_radioCCProtExplicit->GetValue())
      {
        session.m_ccTls = NPL::TLS::Yes;
      }
      else if (m_radioCCProtImplicit->GetValue())
      {
        session.m_ccTls = NPL::TLS::Implicit;
      }

      if (session.m_ccTls != NPL::TLS::No)
      {
        if (m_radioDCProtProtected->GetValue())
        {
          session.m_dcTls = NPL::TLS::Yes;
        }
      }
    }
    else if (session.m_prot == "SSH")
    {
    }

    m_host->Clear();
    m_port->Clear();
    m_user->Clear();
    m_pass->Clear();

    return session;
  }

  void LaunchSession(const TSession& session)
  {
    wxPanel *page = nullptr;

    auto id = ID_PAGE_BASE + m_book->GetPageCount();

    if (session.m_prot == "FTP")
    {
      page = new MyFTP(m_book);
    }
 
    if (!page) return;

    auto tool = m_toolBar->AddRadioTool(id, session.m_prot + "@" + session.m_host, wxBitmap(host_xpm));

    m_book->ShowNewPage(page);

    tool->Toggle();

    m_toolBar->Realize();

    this->Connect(tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MyFrame::onToolClicked));

    auto s = dynamic_cast<TSession *>(page);

    *s = session;

    s->StartSession();
  }

  virtual void OnSavedSessionsListItemActivated(wxListEvent& event)
  {
    LaunchSession(m_slist[event.GetIndex()]);
  }

  void OnLogRightDown(wxMouseEvent& event)
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

  void OnRadioCCProt(wxCommandEvent& event)
  {
    if (m_radioCCProtNone->GetValue()) {
      m_panelDCProt->Enable(false);
    } else {
      m_panelDCProt->Enable(true);
    }
    event.Skip();
  }

  void onToolClicked(wxCommandEvent& event)
  {
    m_book->SetSelection(event.GetId() % ID_PAGE_BASE);
  }
 
  void OnTraceCheckBox(wxCommandEvent& event)
  {
    if (event.IsChecked()) {
      m_splitter->SplitHorizontally(m_panel6, m_panel8, 140);
    } else {
      m_splitter->Unsplit(m_panel6);
    }
  }

  void WriteConfiguration(std::string const& filepath, const std::string& buffer)
  {
    std::ofstream os;

    os.open(filepath, std::ios_base::app);

    os.seekp(0, os.end);

    os.write(buffer.c_str(), buffer.size());

    os.close();
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
    TSession session;
    std::string line;
    std::istringstream ss(buf);

    session.m_ccTls = NPL::TLS::No;
    session.m_dcTls = NPL::TLS::No;

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
          session.m_host = val;
        } else if (key.CmpNoCase("Port") == 0) {
          session.m_port = val;
        } else if (key.CmpNoCase("User") == 0) {
          session.m_user = val;
        } else if (key.CmpNoCase("Pass") == 0) {
          session.m_pass = val;
        } else if (key.CmpNoCase("Prot") == 0) {
          session.m_prot = val;
        } else if (key.CmpNoCase("TLS") == 0) {
          auto flags = wxAtoi(val);
          if (!flags) {
            session.m_ccTls = session.m_dcTls = NPL::TLS::No;
          } else {
            if (flags & 0x01) {
              session.m_ccTls = NPL::TLS::Yes;
            }
            if (flags & 0x02) {
              session.m_dcTls = NPL::TLS::Yes; 
            }
          }
        }
      }

      if (session.m_host.size() && 
          session.m_user.size() && 
          session.m_pass.size() && 
          session.m_port.size() && 
          session.m_prot.size())
      {
        m_slist.push_back(session);
        session.m_host.Clear();
        session.m_user.Clear();
        session.m_pass.Clear();
        session.m_port.Clear();
        session.m_prot.Clear();
        session.m_ccTls = NPL::TLS::No;
        session.m_dcTls = NPL::TLS::No;
      }
    }
  }
};