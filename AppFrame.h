///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
class MyList;

#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/textctrl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/combobox.h>
#include <wx/listctrl.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AppFrame
///////////////////////////////////////////////////////////////////////////////
class AppFrame : public wxFrame
{
	private:

	protected:
		wxSplitterWindow* m_splitterH;
		wxPanel* m_panel5;
		wxStaticText* m_staticText1;
		wxStaticText* m_staticText11;
		wxStaticText* m_staticText5;
		wxStaticText* m_staticText6;
		wxPanel* m_panel9;
		wxSplitterWindow* m_splitterV;
		wxPanel* m_left;
		wxPanel* m_right;

		// Virtual event handlers, overide them in your derived class
		virtual void iButtonConnectOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_logOnRightDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void iComboBoxLocalOnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void iComboBoxLocalOnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void iListViewLocalOnListItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void iListViewLocalOnListItemRightClick( wxListEvent& event ) { event.Skip(); }
		virtual void iListViewLocalOnListItemSelected( wxListEvent& event ) { event.Skip(); }
		virtual void iComboBoxRemoteOnCombobox( wxCommandEvent& event ) { event.Skip(); }
		virtual void iComboBoxRemoteOnTextEnter( wxCommandEvent& event ) { event.Skip(); }
		virtual void iListViewRemoteOnListItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void iListViewRemoteOnListItemRightClick( wxListEvent& event ) { event.Skip(); }
		virtual void iListViewRemoteOnListItemSelected( wxListEvent& event ) { event.Skip(); }


	public:
		wxTextCtrl* m_host;
		wxTextCtrl* m_user;
		wxTextCtrl* m_password;
		wxTextCtrl* m_port;
		wxButton* iButtonConnect;
		wxTextCtrl* m_log;
		wxComboBox* iComboBoxLocal;
		MyList* iListViewLocal;
		wxComboBox* iComboBoxRemote;
		MyList* iListViewRemote;
		wxStatusBar* m_status;

		AppFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("cpp-app"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 906,690 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~AppFrame();

		void m_splitterHOnIdle( wxIdleEvent& )
		{
			m_splitterH->SetSashPosition( 230 );
			m_splitterH->Disconnect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitterHOnIdle ), NULL, this );
		}

		void m_splitterVOnIdle( wxIdleEvent& )
		{
			m_splitterV->SetSashPosition( 440 );
			m_splitterV->Disconnect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitterVOnIdle ), NULL, this );
		}

};

