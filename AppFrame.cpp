///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyList.h"

#include "AppFrame.h"

///////////////////////////////////////////////////////////////////////////

AppFrame::AppFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	wxBoxSizer* bSizerTop;
	bSizerTop = new wxBoxSizer( wxVERTICAL );

	m_splitterH = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxCLIP_CHILDREN );
	m_splitterH->Connect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitterHOnIdle ), NULL, this );

	m_panel5 = new wxPanel( m_splitterH, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );


	bSizer7->Add( 0, 0, 0, wxEXPAND|wxTOP, 5 );

	wxBoxSizer* bSizerQC;
	bSizerQC = new wxBoxSizer( wxHORIZONTAL );

	m_staticText1 = new wxStaticText( m_panel5, wxID_ANY, _("Host:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	bSizerQC->Add( m_staticText1, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );

	m_host = new wxTextCtrl( m_panel5, wxID_ANY, _("170.225.15.40"), wxDefaultPosition, wxSize( 150,-1 ), 0|wxBORDER_SIMPLE );
	bSizerQC->Add( m_host, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerQC->Add( 0, 0, 0, wxRIGHT|wxLEFT, 5 );

	m_staticText11 = new wxStaticText( m_panel5, wxID_ANY, _("User:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	bSizerQC->Add( m_staticText11, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_user = new wxTextCtrl( m_panel5, wxID_ANY, _("anonymous"), wxDefaultPosition, wxSize( 130,-1 ), 0|wxBORDER_SIMPLE );
	bSizerQC->Add( m_user, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerQC->Add( 0, 0, 0, wxRIGHT|wxLEFT, 5 );

	m_staticText5 = new wxStaticText( m_panel5, wxID_ANY, _("Password:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText5->Wrap( -1 );
	bSizerQC->Add( m_staticText5, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_password = new wxTextCtrl( m_panel5, wxID_ANY, _("welcome123"), wxDefaultPosition, wxSize( 130,-1 ), wxTE_PASSWORD|wxBORDER_SIMPLE );
	bSizerQC->Add( m_password, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerQC->Add( 0, 0, 0, wxRIGHT|wxLEFT, 5 );

	m_staticText6 = new wxStaticText( m_panel5, wxID_ANY, _("Port:"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	bSizerQC->Add( m_staticText6, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_port = new wxTextCtrl( m_panel5, wxID_ANY, _("21"), wxDefaultPosition, wxSize( 35,-1 ), 0|wxBORDER_SIMPLE );
	bSizerQC->Add( m_port, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizerQC->Add( 0, 0, 0, wxRIGHT|wxLEFT, 5 );

	iButtonConnect = new wxButton( m_panel5, wxID_ANY, _("Connect"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizerQC->Add( iButtonConnect, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	bSizer7->Add( bSizerQC, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizer10;
	bSizer10 = new wxBoxSizer( wxVERTICAL );

	m_log = new wxTextCtrl( m_panel5, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), wxTE_MULTILINE );
	m_log->SetFont( wxFont( 10, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxT("Consolas") ) );

	bSizer10->Add( m_log, 1, wxALL|wxEXPAND, 5 );


	bSizer7->Add( bSizer10, 1, wxEXPAND|wxRIGHT|wxLEFT, 5 );


	m_panel5->SetSizer( bSizer7 );
	m_panel5->Layout();
	bSizer7->Fit( m_panel5 );
	m_panel9 = new wxPanel( m_splitterH, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer9;
	bSizer9 = new wxBoxSizer( wxVERTICAL );

	m_splitterV = new wxSplitterWindow( m_panel9, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxCLIP_CHILDREN );
	m_splitterV->SetSashGravity( 0 );
	m_splitterV->Connect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitterVOnIdle ), NULL, this );

	m_left = new wxPanel( m_splitterV, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerLeft;
	bSizerLeft = new wxBoxSizer( wxVERTICAL );

	iComboBoxLocal = new wxComboBox( m_left, wxID_ANY, _("Local"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER );
	bSizerLeft->Add( iComboBoxLocal, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	iListViewLocal = new MyList( m_left, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL );
	bSizerLeft->Add( iListViewLocal, 1, wxEXPAND|wxALL, 5 );


	m_left->SetSizer( bSizerLeft );
	m_left->Layout();
	bSizerLeft->Fit( m_left );
	m_right = new wxPanel( m_splitterV, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerRight;
	bSizerRight = new wxBoxSizer( wxVERTICAL );

	iComboBoxRemote = new wxComboBox( m_right, wxID_ANY, _("Not Connected"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER );
	bSizerRight->Add( iComboBoxRemote, 0, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );

	iListViewRemote = new MyList( m_right, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL );
	bSizerRight->Add( iListViewRemote, 1, wxEXPAND|wxALL, 5 );


	m_right->SetSizer( bSizerRight );
	m_right->Layout();
	bSizerRight->Fit( m_right );
	m_splitterV->SplitVertically( m_left, m_right, 440 );
	bSizer9->Add( m_splitterV, 1, wxEXPAND|wxALL, 5 );


	m_panel9->SetSizer( bSizer9 );
	m_panel9->Layout();
	bSizer9->Fit( m_panel9 );
	m_splitterH->SplitHorizontally( m_panel5, m_panel9, 230 );
	bSizerTop->Add( m_splitterH, 1, wxEXPAND, 5 );


	this->SetSizer( bSizerTop );
	this->Layout();
	m_status = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	iButtonConnect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::iButtonConnectOnButtonClick ), NULL, this );
	m_log->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::m_logOnRightDown ), NULL, this );
	iComboBoxLocal->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( AppFrame::iComboBoxLocalOnCombobox ), NULL, this );
	iComboBoxLocal->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AppFrame::iComboBoxLocalOnTextEnter ), NULL, this );
	iListViewLocal->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AppFrame::iListViewLocalOnListItemActivated ), NULL, this );
	iListViewLocal->Connect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( AppFrame::iListViewLocalOnListItemRightClick ), NULL, this );
	iListViewLocal->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AppFrame::iListViewLocalOnListItemSelected ), NULL, this );
	iComboBoxRemote->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( AppFrame::iComboBoxRemoteOnCombobox ), NULL, this );
	iComboBoxRemote->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AppFrame::iComboBoxRemoteOnTextEnter ), NULL, this );
	iListViewRemote->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AppFrame::iListViewRemoteOnListItemActivated ), NULL, this );
	iListViewRemote->Connect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( AppFrame::iListViewRemoteOnListItemRightClick ), NULL, this );
	iListViewRemote->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AppFrame::iListViewRemoteOnListItemSelected ), NULL, this );
}

AppFrame::~AppFrame()
{
	// Disconnect Events
	iButtonConnect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::iButtonConnectOnButtonClick ), NULL, this );
	m_log->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::m_logOnRightDown ), NULL, this );
	iComboBoxLocal->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( AppFrame::iComboBoxLocalOnCombobox ), NULL, this );
	iComboBoxLocal->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AppFrame::iComboBoxLocalOnTextEnter ), NULL, this );
	iListViewLocal->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AppFrame::iListViewLocalOnListItemActivated ), NULL, this );
	iListViewLocal->Disconnect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( AppFrame::iListViewLocalOnListItemRightClick ), NULL, this );
	iListViewLocal->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AppFrame::iListViewLocalOnListItemSelected ), NULL, this );
	iComboBoxRemote->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( AppFrame::iComboBoxRemoteOnCombobox ), NULL, this );
	iComboBoxRemote->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( AppFrame::iComboBoxRemoteOnTextEnter ), NULL, this );
	iListViewRemote->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AppFrame::iListViewRemoteOnListItemActivated ), NULL, this );
	iListViewRemote->Disconnect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( AppFrame::iListViewRemoteOnListItemRightClick ), NULL, this );
	iListViewRemote->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( AppFrame::iListViewRemoteOnListItemSelected ), NULL, this );

}
