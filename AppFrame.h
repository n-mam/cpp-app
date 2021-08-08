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

#include <wx/richtext/richtextctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/toolbar.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/textctrl.h>
#include <wx/choice.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/simplebook.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/combobox.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class AppFrame
///////////////////////////////////////////////////////////////////////////////
class AppFrame : public wxFrame
{
	private:

	protected:
		wxSplitterWindow* m_splitter3;
		wxPanel* m_panel6;
		wxToolBar* m_toolBar1;
		wxToolBarToolBase* m_tool_home;
		wxToolBarToolBase* m_tool2;
		wxPanel* m_panel8;
		wxSimplebook* m_book;
		wxPanel* m_panel9;
		wxChoice* m_protocol;
		wxButton* m_save;
		wxButton* m_connect;
		MyList* iListViewSavedSessions;

		// Virtual event handlers, overide them in your derived class
		virtual void m_logOnRightDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void m_tool_homeOnToolClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_protocolOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_saveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_connectOnButtonClick( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxRichTextCtrl* m_log;
		wxTextCtrl* m_host;
		wxTextCtrl* m_port;
		wxTextCtrl* m_user;
		wxTextCtrl* m_password;
		wxStatusBar* m_status;

		AppFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("cpp-app"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 901,738 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~AppFrame();

		void m_splitter3OnIdle( wxIdleEvent& )
		{
			m_splitter3->SetSashPosition( 150 );
			m_splitter3->Disconnect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitter3OnIdle ), NULL, this );
		}

};

///////////////////////////////////////////////////////////////////////////////
/// Class FTPPanel
///////////////////////////////////////////////////////////////////////////////
class FTPPanel : public wxPanel
{
	private:

	protected:
		wxSplitterWindow* m_splitter;
		wxPanel* m_left;
		wxPanel* m_right;

		// Virtual event handlers, overide them in your derived class
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
		wxComboBox* iComboBoxLocal;
		MyList* iListViewLocal;
		wxComboBox* iComboBoxRemote;
		MyList* iListViewRemote;

		FTPPanel( wxWindow* parent, wxWindowID id = wxID_ANY, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,300 ), long style = wxTAB_TRAVERSAL, const wxString& name = wxEmptyString );
		~FTPPanel();

		void m_splitterOnIdle( wxIdleEvent& )
		{
			m_splitter->SetSashPosition( 320 );
			m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( FTPPanel::m_splitterOnIdle ), NULL, this );
		}

};

