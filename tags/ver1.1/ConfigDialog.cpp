//******************************************************************************
//* Name:      ConfigDialog.cpp
//* Purpose:   Configuration dialog
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#include "pch.h"
#include "ConfigDialog.h"
#include "CBSvnPluginManager.h"

using namespace CBSVN;

//(*IdInit(ConfigDialog)
const long ConfigDialog::ID_NOTEBOOK1 = wxNewId();
const long ConfigDialog::ID_PANEL2 = wxNewId();
const long ConfigDialog::ID_STATICTEXT1 = wxNewId();
const long ConfigDialog::ID_TEXTCTRL1 = wxNewId();
const long ConfigDialog::ID_BUTTON2 = wxNewId();
const long ConfigDialog::ID_STATICTEXT2 = wxNewId();
const long ConfigDialog::ID_TEXTCTRL2 = wxNewId();
const long ConfigDialog::ID_BUTTON5 = wxNewId();
const long ConfigDialog::ID_PANEL1 = wxNewId();
const long ConfigDialog::ID_BUTTON4 = wxNewId();
const long ConfigDialog::ID_BUTTON1 = wxNewId();
const long ConfigDialog::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ConfigDialog,wxDialog)
    //(*EventTable(ConfigDialog)
    //*)
END_EVENT_TABLE()

ConfigDialog::ConfigDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ConfigDialog)
    Create(0, wxID_ANY, _("CBTortoiseSVN Settings"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(244,114));
    FlexGridSizer1 = new wxFlexGridSizer(3, 0, 0, 0);
    BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
    Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(445,231), 0, _T("ID_NOTEBOOK1"));
    PanelPath = new wxPanel(Notebook1, ID_PANEL2, wxPoint(93,6), wxSize(433,205), wxTAB_TRAVERSAL, _T("ID_PANEL2"));
    StaticText1 = new wxStaticText(PanelPath, ID_STATICTEXT1, _("Subversion.exe path"), wxPoint(12,21), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    TextCtrlSVNPath = new wxTextCtrl(PanelPath, ID_TEXTCTRL1, wxEmptyString, wxPoint(128,17), wxSize(264,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    ButtonGetSvnPath = new wxButton(PanelPath, ID_BUTTON2, _("..."), wxPoint(396,16), wxSize(27,23), 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticText2 = new wxStaticText(PanelPath, ID_STATICTEXT2, _("Tortoiseproc.exe path"), wxPoint(12,51), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    TextCtrlTortoiseSVNPath = new wxTextCtrl(PanelPath, ID_TEXTCTRL2, wxEmptyString, wxPoint(128,48), wxSize(264,21), 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    ButtonGetTortoiseSVNPath = new wxButton(PanelPath, ID_BUTTON5, _("..."), wxPoint(396,48), wxSize(27,23), 0, wxDefaultValidator, _T("ID_BUTTON5"));
    Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxPoint(124,8), wxDefaultSize, wxTAB_TRAVERSAL, _T("ID_PANEL1"));
    ButtonShowDebug = new wxButton(Panel1, ID_BUTTON4, _("Show debug window"), wxPoint(16,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    Notebook1->AddPage(PanelPath, _("Paths"), false);
    Notebook1->AddPage(Panel1, _("Misc."), false);
    BoxSizer2->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
    CancelButton = new wxButton(this, ID_BUTTON1, _("cancel"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BoxSizer3->Add(CancelButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    OkButton = new wxButton(this, ID_BUTTON3, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    OkButton->SetDefault();
    BoxSizer3->Add(OkButton, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->SetSizeHints(this);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnButtonGetSvnPathClick);
    Connect(ID_BUTTON5,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnButtonGetTortoiseSVNPathClick);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnButtonShowDebugClick);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnCancelButtonClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ConfigDialog::OnOkButtonClick);
    //*)

    // Update Dialog
    TextCtrlSVNPath->SetValue(CBSvnPluginManager::GetInstance().GetSvn());
    TextCtrlTortoiseSVNPath->SetValue(CBSvnPluginManager::GetInstance().GetTortoiseproc());
}

ConfigDialog::~ConfigDialog()
{
    //(*Destroy(ConfigDialog)
    //*)
}

//******************************************************************************

void ConfigDialog::OnCancelButtonClick(wxCommandEvent& event)
{
    Close();
}

//******************************************************************************

void ConfigDialog::OnOkButtonClick(wxCommandEvent& event)
{
    CBSvnPluginManager::GetInstance().SetSvn(TextCtrlSVNPath->GetValue());
    CBSvnPluginManager::GetInstance().SetTortoiseproc(TextCtrlTortoiseSVNPath->GetValue());
    Close();
}

//******************************************************************************

void ConfigDialog::OnButtonGetSvnPathClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this,               // parent,
                     _("Get svn.exe"),   // message
                     _(""),              // defaultDir
                     _("svn.exe"),       // defaultFile
                     _("*.exe"),         // wildcard
                     wxFILE_MUST_EXIST,  // style
                     wxDefaultPosition   // pos = )
                    );
    if (dlg.ShowModal()!=wxID_OK)
        return;

    TextCtrlSVNPath->SetValue(dlg.GetPath());
}

//******************************************************************************

void ConfigDialog::OnButtonGetTortoiseSVNPathClick(wxCommandEvent& event)
{
    wxFileDialog dlg(this,                  // parent,
                     _("Get tortoiseproc.exe"), // message
                     _(""),                     // defaultDir
                     _("tortoiseproc.exe"),     // defaultFile
                     _("*.exe"),                // wildcard
                     wxFILE_MUST_EXIST,         // style
                     wxDefaultPosition          // pos = )
                    );
    if (dlg.ShowModal()!=wxID_OK)
        return;

    TextCtrlTortoiseSVNPath->SetValue(dlg.GetPath());
}

//******************************************************************************

void ConfigDialog::OnButtonShowDebugClick(wxCommandEvent& event)
{
    CBSvnPluginManager::GetInstance().ShowLogWindow(true);
}

//******************************************************************************
// End of file
