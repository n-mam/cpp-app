///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyList.h"

#include "AppFrame.h"

#include "images/config.xpm"

///////////////////////////////////////////////////////////////////////////

AppFrame::AppFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );
	this->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_MENU ) );

	wxBoxSizer* szTop;
	szTop = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* szTB;
	szTB = new wxBoxSizer( wxHORIZONTAL );

	m_toolBar = new wxToolBar( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORZ_LAYOUT|wxTB_HORZ_TEXT|wxTB_NODIVIDER|wxTB_TEXT );
	m_toolHome = m_toolBar->AddTool( ID_PAGE_BASE, _("Home"), wxBitmap( config_xpm ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_toolBar->Realize();

	szTB->Add( m_toolBar, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


	szTop->Add( szTB, 0, wxEXPAND|wxRIGHT|wxLEFT, 5 );

	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_NOBORDER|wxSP_THIN_SASH );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitterOnIdle ), NULL, this );

	m_panel6 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	m_trace = new wxTextCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_RICH|wxTE_RICH2 );
	m_trace->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_MODERN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	bSizer11->Add( m_trace, 1, wxTOP|wxRIGHT|wxLEFT|wxEXPAND, 5 );


	m_panel6->SetSizer( bSizer11 );
	m_panel6->Layout();
	bSizer11->Fit( m_panel6 );
	m_panel8 = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* szBook;
	szBook = new wxBoxSizer( wxVERTICAL );

	m_book = new wxSimplebook( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_homePage = new wxPanel( m_book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer14;
	bSizer14 = new wxBoxSizer( wxVERTICAL );

	wxStaticBoxSizer* szNew;
	szNew = new wxStaticBoxSizer( new wxStaticBox( m_homePage, wxID_ANY, _("New") ), wxVERTICAL );

	wxBoxSizer* szLine1;
	szLine1 = new wxBoxSizer( wxHORIZONTAL );

	m_host = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0|wxBORDER_DEFAULT );
	szLine1->Add( m_host, 1, wxALL, 5 );

	m_port = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, _("21"), wxDefaultPosition, wxSize( 55,-1 ), 0|wxBORDER_DEFAULT );
	szLine1->Add( m_port, 0, wxALL, 5 );

	wxString m_protocolChoices[] = { _("FTP"), _("SSH") };
	int m_protocolNChoices = sizeof( m_protocolChoices ) / sizeof( wxString );
	m_protocol = new wxChoice( szNew->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_protocolNChoices, m_protocolChoices, 0|wxBORDER_STATIC );
	m_protocol->SetSelection( 0 );
	szLine1->Add( m_protocol, 0, wxALL, 5 );


	szNew->Add( szLine1, 0, wxEXPAND|wxTOP, 5 );

	wxBoxSizer* szLine2;
	szLine2 = new wxBoxSizer( wxHORIZONTAL );

	m_user = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), 0|wxBORDER_DEFAULT );
	szLine2->Add( m_user, 1, wxALL, 5 );

	m_pass = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 150,-1 ), wxTE_PASSWORD|wxBORDER_DEFAULT );
	szLine2->Add( m_pass, 1, wxALL, 5 );


	szNew->Add( szLine2, 0, wxEXPAND|wxTOP, 5 );

	wxStaticBoxSizer* szProtocol;
	szProtocol = new wxStaticBoxSizer( new wxStaticBox( szNew->GetStaticBox(), wxID_ANY, _("FTPS") ), wxVERTICAL );

	wxStaticBoxSizer* szCC;
	szCC = new wxStaticBoxSizer( new wxStaticBox( szProtocol->GetStaticBox(), wxID_ANY, _("Control") ), wxHORIZONTAL );

	m_panelCCProt = new wxPanel( szCC->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer191;
	bSizer191 = new wxBoxSizer( wxHORIZONTAL );

	m_radioCCProtNone = new wxRadioButton( m_panelCCProt, wxID_ANY, _("None"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	m_radioCCProtNone->SetValue( true );
	bSizer191->Add( m_radioCCProtNone, 0, wxALL, 5 );

	m_radioCCProtExplicit = new wxRadioButton( m_panelCCProt, wxID_ANY, _("Explicit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( m_radioCCProtExplicit, 0, wxALL, 5 );

	m_radioCCProtImplicit = new wxRadioButton( m_panelCCProt, wxID_ANY, _("Implicit"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer191->Add( m_radioCCProtImplicit, 0, wxALL, 5 );


	m_panelCCProt->SetSizer( bSizer191 );
	m_panelCCProt->Layout();
	bSizer191->Fit( m_panelCCProt );
	szCC->Add( m_panelCCProt, 1, wxEXPAND | wxALL, 5 );


	szProtocol->Add( szCC, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* szDC;
	szDC = new wxStaticBoxSizer( new wxStaticBox( szProtocol->GetStaticBox(), wxID_ANY, _("Data") ), wxHORIZONTAL );

	m_panelDCProt = new wxPanel( szDC->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxHORIZONTAL );

	m_radioDCProtClear = new wxRadioButton( m_panelDCProt, wxID_ANY, _("Clear"), wxDefaultPosition, wxDefaultSize, wxRB_GROUP );
	bSizer17->Add( m_radioDCProtClear, 0, wxALL, 5 );

	m_radioDCProtProtected = new wxRadioButton( m_panelDCProt, wxID_ANY, _("Protected"), wxDefaultPosition, wxDefaultSize, 0 );
	m_radioDCProtProtected->SetValue( true );
	bSizer17->Add( m_radioDCProtProtected, 0, wxALL, 5 );


	m_panelDCProt->SetSizer( bSizer17 );
	m_panelDCProt->Layout();
	bSizer17->Fit( m_panelDCProt );
	szDC->Add( m_panelDCProt, 1, wxEXPAND | wxALL, 5 );


	szProtocol->Add( szDC, 0, wxEXPAND|wxALL, 5 );


	szNew->Add( szProtocol, 0, wxEXPAND|wxALL, 5 );


	bSizer14->Add( szNew, 1, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );


	bSizer14->Add( 0, 0, 1, wxEXPAND, 5 );

	wxBoxSizer* szLine3;
	szLine3 = new wxBoxSizer( wxHORIZONTAL );


	szLine3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_save = new wxButton( m_homePage, wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0|wxBORDER_STATIC );
	szLine3->Add( m_save, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );

	m_connect = new wxButton( m_homePage, wxID_ANY, _("Connect"), wxDefaultPosition, wxDefaultSize, 0|wxBORDER_STATIC );
	szLine3->Add( m_connect, 0, wxALL|wxALIGN_CENTER_VERTICAL, 5 );


	szLine3->Add( 0, 0, 1, wxEXPAND, 5 );


	bSizer14->Add( szLine3, 1, wxEXPAND|wxTOP|wxBOTTOM|wxRIGHT, 5 );


	bSizer13->Add( bSizer14, 1, wxEXPAND|wxRIGHT|wxLEFT, 5 );

	wxBoxSizer* bSizer19;
	bSizer19 = new wxBoxSizer( wxVERTICAL );

	iListViewSavedSessions = new MyList( m_homePage, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), wxLC_REPORT|wxLC_VIRTUAL|wxBORDER_DEFAULT );
	bSizer19->Add( iListViewSavedSessions, 1, wxEXPAND|wxALL, 5 );

	wxStaticBoxSizer* szSettings;
	szSettings = new wxStaticBoxSizer( new wxStaticBox( m_homePage, wxID_ANY, _("Settings") ), wxVERTICAL );


	szSettings->Add( 0, 0, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* szTrace;
	szTrace = new wxStaticBoxSizer( new wxStaticBox( szSettings->GetStaticBox(), wxID_ANY, _("Trace") ), wxHORIZONTAL );

	m_traceCheck = new wxCheckBox( szTrace->GetStaticBox(), wxID_ANY, _("Enable"), wxDefaultPosition, wxDefaultSize, 0 );
	m_traceCheck->SetValue(true);
	szTrace->Add( m_traceCheck, 0, wxALIGN_CENTER_VERTICAL|wxALL, 5 );


	szSettings->Add( szTrace, 0, wxEXPAND|wxALL, 5 );


	bSizer19->Add( szSettings, 1, wxEXPAND|wxALL, 5 );


	bSizer13->Add( bSizer19, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );


	m_homePage->SetSizer( bSizer13 );
	m_homePage->Layout();
	bSizer13->Fit( m_homePage );
	m_book->AddPage( m_homePage, wxEmptyString, false );

	szBook->Add( m_book, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );


	m_panel8->SetSizer( szBook );
	m_panel8->Layout();
	szBook->Fit( m_panel8 );
	m_splitter->SplitHorizontally( m_panel6, m_panel8, 130 );
	szTop->Add( m_splitter, 1, wxEXPAND|wxBOTTOM|wxRIGHT|wxLEFT, 5 );


	this->SetSizer( szTop );
	this->Layout();
	m_status = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	this->Connect( m_toolHome->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( AppFrame::onToolClicked ) );
	m_trace->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::OnTraceRightDown ), NULL, this );
	m_protocol->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AppFrame::m_protocolOnChoice ), NULL, this );
	m_radioCCProtNone->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AppFrame::OnRadioCCProt ), NULL, this );
	m_radioCCProtExplicit->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AppFrame::OnRadioCCProt ), NULL, this );
	m_radioCCProtImplicit->Connect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AppFrame::OnRadioCCProt ), NULL, this );
	m_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_saveOnButtonClick ), NULL, this );
	m_connect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_connectOnButtonClick ), NULL, this );
	iListViewSavedSessions->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AppFrame::OnSavedSessionsListItemActivated ), NULL, this );
	m_traceCheck->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AppFrame::OnTraceEnableCheckBox ), NULL, this );
}

AppFrame::~AppFrame()
{
	// Disconnect Events
	this->Disconnect( m_toolHome->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( AppFrame::onToolClicked ) );
	m_trace->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::OnTraceRightDown ), NULL, this );
	m_protocol->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AppFrame::m_protocolOnChoice ), NULL, this );
	m_radioCCProtNone->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AppFrame::OnRadioCCProt ), NULL, this );
	m_radioCCProtExplicit->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AppFrame::OnRadioCCProt ), NULL, this );
	m_radioCCProtImplicit->Disconnect( wxEVT_COMMAND_RADIOBUTTON_SELECTED, wxCommandEventHandler( AppFrame::OnRadioCCProt ), NULL, this );
	m_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_saveOnButtonClick ), NULL, this );
	m_connect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_connectOnButtonClick ), NULL, this );
	iListViewSavedSessions->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( AppFrame::OnSavedSessionsListItemActivated ), NULL, this );
	m_traceCheck->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( AppFrame::OnTraceEnableCheckBox ), NULL, this );

}

FTPPanel::FTPPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* szFTP;
	szFTP = new wxBoxSizer( wxVERTICAL );

	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxBORDER_NONE|wxCLIP_CHILDREN );
	m_splitter->SetSashGravity( 0 );

	m_left = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerLeft;
	bSizerLeft = new wxBoxSizer( wxVERTICAL );

	iComboBoxLocal = new wxComboBox( m_left, wxID_ANY, _("Local"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER );
	bSizerLeft->Add( iComboBoxLocal, 0, wxEXPAND|wxBOTTOM|wxRIGHT, 5 );

	iListViewLocal = new MyList( m_left, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL );
	bSizerLeft->Add( iListViewLocal, 1, wxEXPAND|wxTOP|wxRIGHT, 5 );


	m_left->SetSizer( bSizerLeft );
	m_left->Layout();
	bSizerLeft->Fit( m_left );
	m_right = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizerRight;
	bSizerRight = new wxBoxSizer( wxVERTICAL );

	iComboBoxRemote = new wxComboBox( m_right, wxID_ANY, _("Not Connected"), wxDefaultPosition, wxDefaultSize, 0, NULL, wxTE_PROCESS_ENTER );
	bSizerRight->Add( iComboBoxRemote, 0, wxEXPAND|wxBOTTOM, 5 );

	iListViewRemote = new MyList( m_right, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxLC_REPORT|wxLC_VIRTUAL );
	bSizerRight->Add( iListViewRemote, 1, wxEXPAND|wxTOP, 5 );


	m_right->SetSizer( bSizerRight );
	m_right->Layout();
	bSizerRight->Fit( m_right );
	m_splitter->SplitVertically( m_left, m_right, -1 );
	szFTP->Add( m_splitter, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


	this->SetSizer( szFTP );
	this->Layout();

	// Connect Events
	this->Connect( wxEVT_SIZE, wxSizeEventHandler( FTPPanel::FTPPanelOnSize ) );
	iComboBoxLocal->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FTPPanel::iComboBoxLocalOnCombobox ), NULL, this );
	iComboBoxLocal->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( FTPPanel::iComboBoxLocalOnTextEnter ), NULL, this );
	iListViewLocal->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( FTPPanel::iListViewLocalOnListItemActivated ), NULL, this );
	iListViewLocal->Connect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( FTPPanel::iListViewLocalOnListItemRightClick ), NULL, this );
	iListViewLocal->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FTPPanel::iListViewLocalOnListItemSelected ), NULL, this );
	iComboBoxRemote->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FTPPanel::iComboBoxRemoteOnCombobox ), NULL, this );
	iComboBoxRemote->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( FTPPanel::iComboBoxRemoteOnTextEnter ), NULL, this );
	iListViewRemote->Connect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( FTPPanel::iListViewRemoteOnListItemActivated ), NULL, this );
	iListViewRemote->Connect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( FTPPanel::iListViewRemoteOnListItemRightClick ), NULL, this );
	iListViewRemote->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FTPPanel::iListViewRemoteOnListItemSelected ), NULL, this );
}

FTPPanel::~FTPPanel()
{
	// Disconnect Events
	this->Disconnect( wxEVT_SIZE, wxSizeEventHandler( FTPPanel::FTPPanelOnSize ) );
	iComboBoxLocal->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FTPPanel::iComboBoxLocalOnCombobox ), NULL, this );
	iComboBoxLocal->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( FTPPanel::iComboBoxLocalOnTextEnter ), NULL, this );
	iListViewLocal->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( FTPPanel::iListViewLocalOnListItemActivated ), NULL, this );
	iListViewLocal->Disconnect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( FTPPanel::iListViewLocalOnListItemRightClick ), NULL, this );
	iListViewLocal->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FTPPanel::iListViewLocalOnListItemSelected ), NULL, this );
	iComboBoxRemote->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FTPPanel::iComboBoxRemoteOnCombobox ), NULL, this );
	iComboBoxRemote->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( FTPPanel::iComboBoxRemoteOnTextEnter ), NULL, this );
	iListViewRemote->Disconnect( wxEVT_COMMAND_LIST_ITEM_ACTIVATED, wxListEventHandler( FTPPanel::iListViewRemoteOnListItemActivated ), NULL, this );
	iListViewRemote->Disconnect( wxEVT_COMMAND_LIST_ITEM_RIGHT_CLICK, wxListEventHandler( FTPPanel::iListViewRemoteOnListItemRightClick ), NULL, this );
	iListViewRemote->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( FTPPanel::iListViewRemoteOnListItemSelected ), NULL, this );

}
