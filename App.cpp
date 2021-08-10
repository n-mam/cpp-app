#include <npl.hpp>
#include "wx/wx.h"
#include "MyFrame.h"

#ifndef wxHAS_IMAGES_IN_RESOURCES
#include "images/sample.xpm"
#endif

class MyApp : public wxApp
{
  public:
  virtual bool OnInit();
  MyFrame *m_frame;
};

IMPLEMENT_APP(MyApp)
wxDECLARE_APP(MyApp);

bool MyApp::OnInit()
{
  if (!wxApp::OnInit())
    return false;

  wxInitAllImageHandlers();

  m_frame = new MyFrame(NULL);

  m_frame->SetIcon(wxICON(aaaaaaaa));

  m_frame->m_host->SetHint("host");
  m_frame->m_user->SetHint("username");
  m_frame->m_password->SetHint("password");
  m_frame->m_port->SetHint("port");

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
          auto trace = (wxGetApp().m_frame)->m_log;

          trace->BeginTextColour(wxColour(0, 0, 0));

          if (log.find("Command  :") == 0) {
            trace->BeginTextColour(wxColour(0, 58, 200));
          } else if (log.find("Response :") == 0) {
            trace->BeginTextColour(wxColour(0, 150, 0));
          }

          trace->WriteText(" " + log);
          trace->EndTextColour();
          trace->ScrollIntoView(trace->GetCaretPosition(), WXK_PAGEDOWN);
        }
      });
    });

  m_frame->Show(true);

  return true;
}