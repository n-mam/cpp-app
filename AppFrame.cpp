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

	wxBoxSizer* szTop;
	szTop = new wxBoxSizer( wxVERTICAL );

	m_splitter = new wxSplitterWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxSP_3D|wxSP_LIVE_UPDATE|wxBORDER_STATIC|wxCLIP_CHILDREN );
	m_splitter->Connect( wxEVT_IDLE, wxIdleEventHandler( AppFrame::m_splitterOnIdle ), NULL, this );

	m_nav = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* szNav;
	szNav = new wxBoxSizer( wxVERTICAL );

	m_listBox1 = new wxListBox( m_nav, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0, NULL, 0|wxBORDER_DEFAULT );
	m_listBox1->Append( _("Home") );
	szNav->Add( m_listBox1, 1, wxEXPAND|wxTOP|wxBOTTOM|wxLEFT, 5 );


	m_nav->SetSizer( szNav );
	m_nav->Layout();
	szNav->Fit( m_nav );
	m_page = new wxPanel( m_splitter, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxBoxSizer* szPage;
	szPage = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer11;
	bSizer11 = new wxBoxSizer( wxVERTICAL );

	m_log = new wxRichTextCtrl( m_page, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0|wxBORDER_DEFAULT|wxHSCROLL|wxVSCROLL|wxWANTS_CHARS );
	bSizer11->Add( m_log, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


	szPage->Add( bSizer11, 1, wxEXPAND, 5 );

	m_book = new wxSimplebook( m_page, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE );
	m_home = new wxPanel( m_book, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_NONE|wxTAB_TRAVERSAL );
	wxBoxSizer* szHome;
	szHome = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer12;
	bSizer12 = new wxBoxSizer( wxHORIZONTAL );

	wxStaticBoxSizer* szNew;
	szNew = new wxStaticBoxSizer( new wxStaticBox( m_home, wxID_ANY, _("New") ), wxVERTICAL );

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

	wxBoxSizer* szLine3;
	szLine3 = new wxBoxSizer( wxHORIZONTAL );


	szLine3->Add( 0, 0, 1, wxEXPAND, 5 );

	m_save = new wxButton( szNew->GetStaticBox(), wxID_ANY, _("Save"), wxDefaultPosition, wxDefaultSize, 0|wxBORDER_STATIC );
	szLine3->Add( m_save, 0, wxALL, 5 );

	m_connect = new wxButton( szNew->GetStaticBox(), wxID_ANY, _("Connect"), wxDefaultPosition, wxDefaultSize, 0|wxBORDER_STATIC );
	szLine3->Add( m_connect, 0, wxALL, 5 );


	szLine3->Add( 0, 0, 1, wxEXPAND, 5 );


	szNew->Add( szLine3, 0, wxEXPAND, 5 );


	bSizer12->Add( szNew, 0, wxALL|wxEXPAND, 5 );

	wxStaticBoxSizer* szTrace;
	szTrace = new wxStaticBoxSizer( new wxStaticBox( m_home, wxID_ANY, _("Trace") ), wxVERTICAL );


	bSizer12->Add( szTrace, 1, wxEXPAND|wxALL, 5 );


	szHome->Add( bSizer12, 1, wxEXPAND, 5 );

	wxStaticBoxSizer* szSaved;
	szSaved = new wxStaticBoxSizer( new wxStaticBox( m_home, wxID_ANY, _("Saved") ), wxVERTICAL );

	iListViewSavedSessions = new MyList( szSaved->GetStaticBox(), wxID_ANY, wxDefaultPosition, wxSize( -1,150 ), wxLC_REPORT|wxBORDER_DEFAULT );
	szSaved->Add( iListViewSavedSessions, 1, wxEXPAND|wxALL, 5 );


	szHome->Add( szSaved, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


	m_home->SetSizer( szHome );
	m_home->Layout();
	szHome->Fit( m_home );
	m_book->AddPage( m_home, _("a page"), false );

	szPage->Add( m_book, 1, wxEXPAND|wxTOP|wxBOTTOM, 5 );


	m_page->SetSizer( szPage );
	m_page->Layout();
	szPage->Fit( m_page );
	m_splitter->SplitVertically( m_nav, m_page, 150 );
	szTop->Add( m_splitter, 1, wxEXPAND, 5 );


	this->SetSizer( szTop );
	this->Layout();
	m_status = this->CreateStatusBar( 1, wxSTB_SIZEGRIP, wxID_ANY );

	this->Centre( wxBOTH );

	// Connect Events
	m_log->Connect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::m_logOnRightDown ), NULL, this );
	m_save->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_saveOnButtonClick ), NULL, this );
	m_connect->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( AppFrame::m_connectOnButtonClick ), NULL, this );
}

AppFrame::~AppFrame()
{
	// Disconnect Events
	m_log->Disconnect( wxEVT_RIGHT_DOWN, wxMouseEventHandler( AppFrame::m_logOnRightDown ), NULL, this );
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
	m_splitter->SplitVertically( m_left, m_right, 260 );
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
