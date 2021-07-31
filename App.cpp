#include <npl.hpp>
#include "wx/wx.h"
#include "ftp.hpp"

#ifndef wxHAS_IMAGES_IN_RESOURCES
  #include "images/sample.xpm"
#endif

class MyApp : public wxApp
{
  public:

  virtual bool OnInit();
  FrameFTP *m_frame;
};

IMPLEMENT_APP(MyApp)
wxDECLARE_APP(MyApp);

bool MyApp::OnInit()
{
  if ( !wxApp::OnInit() )
    return false;

  wxInitAllImageHandlers();

  m_frame = new FrameFTP(NULL);

  m_frame->SetIcon(wxICON(aaaaaaaa));

  NPL::CLogger::SetLogCallback(
    [](const std::string& msg)
    {
      //OutputDebugStringA(msg.c_str());
      wxGetApp().CallAfter([log = msg]() {
        if (log.find("status ") == 0)
        {
          (wxGetApp().m_frame)->m_status->SetStatusText(
            log.substr(strlen("status")));
        }
        else
        {
          (wxGetApp().m_frame)->m_log->AppendText(" " + log);
        }
      });
    });

  m_frame->Show(true);

  return true;
}