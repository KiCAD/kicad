///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Sep  1 2019)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "wx_html_report_panel.h"

#include "dialog_update_from_pcb_base.h"

///////////////////////////////////////////////////////////////////////////

DIALOG_UPDATE_FROM_PCB_BASE::DIALOG_UPDATE_FROM_PCB_BASE( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : DIALOG_SHIM( parent, id, title, pos, size, style )
{
    this->SetSizeHints( wxSize( -1,-1 ), wxDefaultSize );

    wxBoxSizer* bMainSizer;
    bMainSizer = new wxBoxSizer( wxVERTICAL );

    wxBoxSizer* bUpperSizer;
    bUpperSizer = new wxBoxSizer( wxVERTICAL );

    wxStaticBoxSizer* sbSizer1;
    sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Options") ), wxVERTICAL );

    wxBoxSizer* bSizer1;
    bSizer1 = new wxBoxSizer( wxVERTICAL );


    sbSizer1->Add( bSizer1, 1, wxEXPAND, 5 );

    wxGridBagSizer* gbSizer2;
    gbSizer2 = new wxGridBagSizer( 0, 0 );
    gbSizer2->SetFlexibleDirection( wxBOTH );
    gbSizer2->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );

    m_cbUpdateReferences = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Update References"), wxDefaultPosition, wxDefaultSize, 0 );
    m_cbUpdateReferences->SetValue(true);
    m_cbUpdateReferences->SetToolTip( _("Update references from PCB.") );

    gbSizer2->Add( m_cbUpdateReferences, wxGBPosition( 0, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

    m_cbUpdateFootprints = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Update Footprints"), wxDefaultPosition, wxDefaultSize, 0 );
    m_cbUpdateFootprints->SetToolTip( _("Update footprints from PCB.") );

    gbSizer2->Add( m_cbUpdateFootprints, wxGBPosition( 1, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

    m_cbIgnoreStandalone = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Ignore Footrints with no component associated"), wxDefaultPosition, wxDefaultSize, 0 );
    m_cbIgnoreStandalone->SetToolTip( _("Ignore footprints, which were created as standalone in PCB editor.") );

    gbSizer2->Add( m_cbIgnoreStandalone, wxGBPosition( 0, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );

    m_cbUpdateValues = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Update Values"), wxDefaultPosition, wxDefaultSize, 0 );
    m_cbUpdateValues->SetToolTip( _("Update values from PCB.") );

    gbSizer2->Add( m_cbUpdateValues, wxGBPosition( 2, 0 ), wxGBSpan( 1, 1 ), wxALL, 5 );

    m_cbIgnoreOtherProjects = new wxCheckBox( sbSizer1->GetStaticBox(), wxID_ANY, _("Ignore Errors in Other Projects"), wxDefaultPosition, wxDefaultSize, 0 );
    m_cbIgnoreOtherProjects->SetToolTip( _("If some schematic was used more than once, it can cause an error when you try to back annotate value or footprint. If this option is on, all errors caused by using schematic in other projects will be disabled.") );

    gbSizer2->Add( m_cbIgnoreOtherProjects, wxGBPosition( 1, 1 ), wxGBSpan( 1, 1 ), wxALL, 5 );


    gbSizer2->AddGrowableCol( 1 );

    sbSizer1->Add( gbSizer2, 1, wxEXPAND, 5 );


    bUpperSizer->Add( sbSizer1, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );


    bMainSizer->Add( bUpperSizer, 0, wxALL|wxEXPAND, 5 );

    wxBoxSizer* bLowerSizer;
    bLowerSizer = new wxBoxSizer( wxVERTICAL );

    bLowerSizer->SetMinSize( wxSize( 660,300 ) );
    m_messagePanel = new WX_HTML_REPORT_PANEL( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
    bLowerSizer->Add( m_messagePanel, 1, wxEXPAND | wxALL, 5 );


    bMainSizer->Add( bLowerSizer, 1, wxEXPAND|wxTOP|wxRIGHT|wxLEFT, 5 );

    m_sdbSizer1 = new wxStdDialogButtonSizer();
    m_sdbSizer1OK = new wxButton( this, wxID_OK );
    m_sdbSizer1->AddButton( m_sdbSizer1OK );
    m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
    m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
    m_sdbSizer1->Realize();

    bMainSizer->Add( m_sdbSizer1, 0, wxALL|wxEXPAND, 5 );


    this->SetSizer( bMainSizer );
    this->Layout();
    bMainSizer->Fit( this );

    // Connect Events
    m_cbUpdateReferences->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbUpdateFootprints->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbIgnoreStandalone->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbUpdateValues->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbIgnoreOtherProjects->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_sdbSizer1OK->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnUpdateClick ), NULL, this );
}

DIALOG_UPDATE_FROM_PCB_BASE::~DIALOG_UPDATE_FROM_PCB_BASE()
{
    // Disconnect Events
    m_cbUpdateReferences->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbUpdateFootprints->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbIgnoreStandalone->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbUpdateValues->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_cbIgnoreOtherProjects->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnOptionChanged ), NULL, this );
    m_sdbSizer1OK->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( DIALOG_UPDATE_FROM_PCB_BASE::OnUpdateClick ), NULL, this );

}
