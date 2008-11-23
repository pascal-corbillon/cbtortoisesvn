//******************************************************************************
//* Name:      LogDialog.cpp
//* Purpose:   Log dialog
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#include "pch.h"
#include "LogDialog.h"

//(*IdInit(LogDialog)
const long LogDialog::ID_NOTEBOOK1 = wxNewId();
const long LogDialog::ID_PANEL1 = wxNewId();
const long LogDialog::ID_LISTBOX1 = wxNewId();
const long LogDialog::ID_STATICTEXT1 = wxNewId();
const long LogDialog::ID_BUTTON2 = wxNewId();
const long LogDialog::ID_BUTTON1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(LogDialog,wxDialog)
	//(*EventTable(LogDialog)
	//*)
END_EVENT_TABLE()

LogDialog::LogDialog(wxWindow* parent,wxWindowID id)
{
	//(*Initialize(LogDialog)
	Create(0, wxID_ANY, _("Log window"), wxDefaultPosition, wxDefaultSize, wxSTAY_ON_TOP|wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(382,207));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	BoxSizer1 = new wxBoxSizer(wxHORIZONTAL);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxDefaultSize, 0, _T("ID_NOTEBOOK1"));
	Panel1 = new wxPanel(Notebook1, ID_PANEL1, wxPoint(22,64), wxSize(458,243), wxTAB_TRAVERSAL, _T("ID_PANEL1"));
	ListBoxLogging = new wxListBox(Panel1, ID_LISTBOX1, wxPoint(0,0), wxSize(504,304), 0, 0, wxVSCROLL|wxHSCROLL|wxALWAYS_SHOW_SB, wxDefaultValidator, _T("ID_LISTBOX1"));
	Notebook1->AddPage(Panel1, _("Logging"), false);
	BoxSizer1->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer2 = new wxBoxSizer(wxHORIZONTAL);
	StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("(*)   Most recent entry on top"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
	BoxSizer2->Add(StaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer3 = new wxBoxSizer(wxHORIZONTAL);
	ButtonClear = new wxButton(this, ID_BUTTON2, _("Clear"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer3->Add(ButtonClear, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ButtonOK = new wxButton(this, ID_BUTTON1, _("OK"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BoxSizer3->Add(ButtonOK, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer1->Add(BoxSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogDialog::OnButtonClearClick);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&LogDialog::OnButtonOKClick);
	//*)
}

LogDialog::~LogDialog()
{
	//(*Destroy(LogDialog)
	//*)
}

//******************************************************************************

void LogDialog::Log(const wxString& s)
{
    ListBoxLogging->InsertItems(1,&s,0);
}

//******************************************************************************

void LogDialog::OnButtonClearClick(wxCommandEvent& event)
{
    ListBoxLogging->Clear();
}

//******************************************************************************

void LogDialog::OnButtonOKClick(wxCommandEvent& event)
{
    Close();
}

//******************************************************************************
// End of file

