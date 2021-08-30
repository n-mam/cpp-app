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
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/gdicmn.h>
#include <wx/toolbar.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/radiobut.h>
#include <wx/statbox.h>
#include <wx/button.h>
#include <wx/listctrl.h>
#include <wx/checkbox.h>
#include <wx/simplebook.h>
#include <wx/splitter.h>
#include <wx/statusbr.h>
#include <wx/frame.h>
#include <wx/combobox.h>

///////////////////////////////////////////////////////////////////////////

#define ID_PAGE_BASE 1000

///////////////////////////////////////////////////////////////////////////////
/// Class AppFrame
///////////////////////////////////////////////////////////////////////////////
class AppFrame : public wxFrame
{
	private:

	protected:
		wxPanel* m_panel81;
		wxToolBarToolBase* m_toolHome;
		wxSplitterWindow* m_splitter;
		wxPanel* m_panel6;
		wxPanel* m_panel8;
		wxSimplebook* m_book;
		wxPanel* m_homePage;
		wxChoice* m_protocol;
		wxPanel* m_panelCCProt;
		wxRadioButton* m_radioCCProtNone;
		wxRadioButton* m_radioCCProtExplicit;
		wxRadioButton* m_radioCCProtImplicit;
		wxPanel* m_panelDCProt;
		wxRadioButton* m_radioDCProtClear;
		wxRadioButton* m_radioDCProtProtected;
		wxPanel* m_panel10;
		wxButton* m_save;
		wxButton* m_connect;
		wxPanel* m_panel9;
		MyList* iListViewSavedSessions;
		wxCheckBox* m_traceCheck;

		// Virtual event handlers, overide them in your derived class
		virtual void onToolClicked( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnTraceRightDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void m_protocolOnChoice( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnRadioCCProt( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_saveOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void m_connectOnButtonClick( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSavedSessionsListItemActivated( wxListEvent& event ) { event.Skip(); }
		virtual void OnTraceEnableCheckBox( wxCommandEvent& event ) { event.Skip(); }


	public:
		wxToolBar* m_toolBar;
		wxTextCtrl* m_trace;
		wxTextCtrl* m_host;
		wxTextCtrl* m_port;
		wxTextCtrl* m_user;
		wxTextCtrl* m_pass;
		wxStatusBar* m_status;

		AppFrame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("cpp-app"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 901,738 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~AppFrame();

		void m_splitterOnIdle( wxIdleEvent& )
		{
			m_splitter->SetSashPosition( 130 );
			m_splitter->Disconnect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitterOnIdle ), NULL, this );
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
		virtual void FTPPanelOnSize( wxSizeEvent& event ) { event.Skip(); }
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

};

