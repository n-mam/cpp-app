#include "AppFrame.h"
#include "MyList.h"
#include "ftp.hpp"

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
    const wxSize& size = wxSize( 700,600 ),
    long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL)
  : AppFrame(parent, id, title, pos, size, style)
  {
    iListViewSavedSessions->Initialize({"Host", "Port", "Protocol", "Username", "Password"});
    m_splitter->Unsplit(m_panel6);
    m_host->SetFocus();
  }
 
  virtual ~MyFrame() {}

  protected:

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

  virtual void m_saveOnButtonClick( wxCommandEvent& event )
  {
    event.Skip();
  }
  
  virtual void m_connectOnButtonClick( wxCommandEvent& event )
  {
    auto host = m_host->GetValue().ToStdString();
    auto port = m_port->GetValue().ToStdString();
    auto user = m_user->GetValue().ToStdString();
    auto pass = m_password->GetValue().ToStdString();
    auto proto = m_protocol->GetString(
      m_protocol->GetSelection()).ToStdString();

    if (!host.size() || !user.size() || !pass.size() || !port.size() || !proto.size())
    {
      wxMessageBox(
       "Please specify all the values", 
        "Error", wxOK, this);
      return;
    }

    wxPanel *page = nullptr;

    if (proto == "FTP") 
    {
      page = new MyFTP(m_book);
    }
 
    if (!page) return;

    auto id = ID_PAGE_BASE + 1 + iSessionPanels.size();

    iSessionPanels.push_back({id, page});

    m_book->ShowNewPage(page);

    auto tool = m_toolBar->AddTool(id, proto + "@" + host, wxBitmap(host_xpm), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL);

    tool->Toggle();

    m_toolBar->Realize();

    this->Connect(tool->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler(MyFrame::onToolClicked));

    if (proto == "FTP") 
    {
      auto ftppage = dynamic_cast<MyFTP *>(page);
      ftppage->InitiateConnect(host, port, user, pass);
    }

    event.Skip();
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

  //common
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

};
