#include "AppFrame.h"
#include "MyList.h"
#include "ftp.hpp"

#define ID_LOG_BASE 3000

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
  } 
 
  virtual ~MyFrame() {}

  protected:

  virtual void m_saveOnButtonClick( wxCommandEvent& event )
  {
    event.Skip();
  }
  
  virtual void m_connectOnButtonClick( wxCommandEvent& event )
  {
    auto host = m_host->GetValue().ToStdString();
    auto user = m_user->GetValue().ToStdString();
    auto pass = m_password->GetValue().ToStdString();
    auto port = m_port->GetValue().ToStdString();

    auto ftppanel = new MyFTP(m_book);

    m_book->ShowNewPage(ftppanel);
    // iFTP = NPL::make_ftp(iHost, wxAtoi(iPort), NPL::TLS::Yes);

    // iFTP->SetCredentials(iUser, iPass);

    // iFTP->StartClient();

    // GetDirectoryList(
    //   "/",
    //   [this](const std::string& path, const std::string& list){
    //     UpdateRemoteListView(path, list);
    //   });

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