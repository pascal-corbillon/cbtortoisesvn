//******************************************************************************
//* Name:      LogDialog.h
//* Purpose:   Log dialog
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#ifndef LOGDIALOG_H
#define LOGDIALOG_H

//(*Headers(LogDialog)
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/listbox.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
//*)

class LogDialog: public wxDialog
{
	public:

		LogDialog(wxWindow* parent,wxWindowID id=wxID_ANY);
		virtual ~LogDialog();

		//(*Identifiers(LogDialog)
		static const long ID_NOTEBOOK1;
		static const long ID_PANEL1;
		static const long ID_LISTBOX1;
		static const long ID_STATICTEXT1;
		static const long ID_BUTTON2;
		static const long ID_BUTTON1;
		//*)

		void Log(const wxString& s);

	protected:

		//(*Handlers(LogDialog)
		void OnButtonClearClick(wxCommandEvent& event);
		void OnButtonOKClick(wxCommandEvent& event);
		//*)

		//(*Declarations(LogDialog)
		wxFlexGridSizer* FlexGridSizer1;
		wxBoxSizer* BoxSizer1;
		wxNotebook* Notebook1;
		wxPanel* Panel1;
		wxListBox* ListBoxLogging;
		wxBoxSizer* BoxSizer2;
		wxStaticText* StaticText1;
		wxBoxSizer* BoxSizer3;
		wxButton* ButtonClear;
		wxButton* ButtonOK;
		//*)

	private:

		DECLARE_EVENT_TABLE()
};

#endif
