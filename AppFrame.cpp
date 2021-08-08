///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "MyList.h"

#include "AppFrame.h"

#include "images/config.xpm"
#include "images/host.xpm"

///////////////////////////////////////////////////////////////////////////

AppFrame::AppFrame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	this->SetFont( wxFont( wxNORMAL_FONT->GetPointSize(), wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_NORMAL, false, wxEmptyString ) );

	wxBoxSizer* szTop;
	szTop = new wxBoxSizer( wxVERTICAL );

	m_splitter3 = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_LIVE_UPDATE|wxSP_THIN_SASH );
	m_splitter3->Connect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitter3OnIdle ), NULL, this );

	m_panel6 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	m_log = new wxRichTextCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( -1,-1 ), 0|wxBORDER_DEFAULT|wxHSCROLL|wxVSCROLL|wxWANTS_CHARS );
	bSizer11->Add( m_log, 1, wxTOP|wxRIGHT|wxLEFT|wxEXPAND, 5 );

	m_toolBar1 = new wxToolBar( m_panel6, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTB_HORZ_LAYOUT|wxTB_HORZ_TEXT|wxTB_NODIVIDER|wxTB_TEXT );
	m_tool_home = m_toolBar1->AddTool( wxID_ANY, _("Home"), wxBitmap( config_xpm ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_tool2 = m_toolBar1->AddTool( wxID_ANY, _("tool"), wxBitmap( host_xpm ), wxNullBitmap, wxITEM_RADIO, wxEmptyString, wxEmptyString, NULL );

	m_toolBar1->Realize();

	bSizer11->Add( m_toolBar1, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


	m_panel6->SetSizer( bSizer11 );
	m_panel6->Layout();
	bSizer11->Fit( m_panel6 );
	m_panel8 = new wxPanel( m_splitter3, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer17;
	bSizer17 = new wxBoxSizer( wxVERTICAL );

	m_book = new wxSimplebook( m_panel8, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel9 = new wxPanel( m_book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* bSizer13;
	bSizer13 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* szNew;
	szNew = new wxStaticBoxSizer( new wxStaticBox( m_panel9, wxID_ANY, _("New") ), wxVERTICAL );

	wxBoxSizer* szLine1;
	szLine1 = new wxBoxSizer( wxHORIZONTAL );

	m_host = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 180,-1 ), 0|wxBORDER_DEFAULT );
	szLine1->Add( m_host, 1, wxALL, 5 );

	m_port = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 45,-1 ), 0|wxBORDER_DEFAULT );
	szLine1->Add( m_port, 0, wxALL, 5 );

	wxString m_protocolChoices[] = { _("FTP"), _("SSH"), _("WSS") };
	int m_protocolNChoices = sizeof( m_protocolChoices ) / sizeof( wxString );
	m_protocol = new wxChoice( szNew->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxDefaultSize, m_protocolNChoices, m_protocolChoices, 0|wxBORDER_STATIC );
	m_protocol->SetSelection( 0 );
	szLine1->Add( m_protocol, 0, wxALL, 5 );


	szNew->Add( szLine1, 0, 0, 5 );

	wxBoxSizer* szLine2;
	szLine2 = new wxBoxSizer( wxHORIZONTAL );

	m_user = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxBORDER_DEFAULT );
	szLine2->Add( m_user, 1, wxALL, 5 );

	m_password = new wxTextCtrl( szNew->GetStaticBox(), wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxBORDER_DEFAULT );
	szLine2->Add( m_password, 1, wxALL, 5 );


	szNew->Add( szLine2, 0, wxEXPAND, 5 );

	wxStaticBoxSizer* szProtocol;
	szProtocol = new wxStaticBoxSizer( new wxStaticBox( szNew->GetStaticBox(), wxID_ANY, _("FTP") ), wxVERTICAL );


	szNew->Add( szProtocol, 1, wxEXPAND|wxALL, 5 );

	wxBoxSizer* szLine3;
	szLine3 = new wxBoxSizer( wxHORIZONTAL );


	szLine3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_save = new wxButton( szNew->GetStaticBox(), wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0|wxBORDER_STATIC );
	szLine3->Add( m_save, 0, wxALL, 5 );

	m_connect = new wxButton( szNew->GetStaticBox(), wxID_ANY, _("Connect"), wxDefaultPosition, wxDefaultSize, 0|wxBORDER_STATIC );
	szLine3->Add( m_connect, 0, wxALL, 5 );


	szLine3->Add( 0, 0, 1, wxEXPAND, 5 );


	szNew->Add( szLine3, 0, wxEXPAND, 5 );


	bSizer13->Add( szNew, 0, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

	wxStaticBoxSizer* szSaved;
	szSaved = new wxStaticBoxSizer( new wxStaticBox( m_panel9, wxID_ANY, _("Saved") ), wxVERTICAL );

	iListViewSavedSessions = new MyList( szSaved->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLC_REPORT|wxBORDER_DEFAULT );
	szSaved->Add( iListViewSavedSessions, 1, wxEXPAND|wxALL, 5 );


	bSizer13->Add( szSaved, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


	m_panel9->SetSizer( bSizer13 );
	m_panel9->Layout();
	bSizer13->Fit( m_panel9 );
	m_book->AddPage( m_panel9, _("a page"), false );

	bSizer17->Add( m_book, 1, wxEXPAND|wxBOTTOM, 5 );


	m_panel8->SetSizer( bSizer17 );
	m_panel8->Layout();
	bSizer17->Fit( m_panel8 );
	m_splitter3->SplitHorizontally( m_panel6, m_panel8, 150 );
	szTop->Add( m_splitter3, 1, wxEXPAND, 5 );


	this->SetSizer( szTop );
	this->Layout();
	m_status = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	m_log->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::m_logOnRightDown ), NULL, this );
	this->Connect( m_tool_home->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( AppFrame::m_tool_homeOnToolClicked ) );
	m_protocol->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AppFrame::m_protocolOnChoice ), NULL, this );
	m_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_saveOnButtonClick ), NULL, this );
	m_connect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_connectOnButtonClick ), NULL, this );
}

AppFrame::~AppFrame()
{
	// Disconnect Events
	m_log->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::m_logOnRightDown ), NULL, this );
	this->Disconnect( m_tool_home->GetId(), wxEVT_COMMAND_TOOL_CLICKED, wxCommandEventHandler( AppFrame::m_tool_homeOnToolClicked ) );
	m_protocol->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( AppFrame::m_protocolOnChoice ), NULL, this );
	m_save->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_saveOnButtonClick ), NULL, this );
	m_connect->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_connectOnButtonClick ), NULL, this );

}

FTPPanel::FTPPanel( wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size, long style, const wxString& name ) : wxPanel( parent, id, pos, size, style, name )
{
	wxBoxSizer* szFTP;
	szFTP = new wxBoxSizer( wxVERTICAL );

	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxBORDER_NONE|wxCLIP_CHILDREN );
	m_splitter->SetSashGravity( 0 );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( FTPPanel::m_splitterOnIdle ), NULL, this );

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
	m_splitter->SplitVertically( m_left, m_right, 320 );
	szFTP->Add( m_splitter, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


	this->SetSizer( szFTP );
	this->Layout();

	// Connect Events
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
