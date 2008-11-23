//******************************************************************************
//* Name:      CBTortoiseSVN.cpp
//* Purpose:   Code::Blocks plugin using TortoiseSVN commandline interface
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#include "CBTortoiseSVN.h"
#include "cbeditor.h"
#include "editormanager.h"
#include "licenses.h"
#include "cbproject.h"
#include <windows.h>

//******************************************************************************

static int idCBTortoiseSVN          = wxNewId();
static int idAdd                    = wxNewId();
static int idCommit                 = wxNewId();
static int idDiffWithBase           = wxNewId();
static int idLog                    = wxNewId();
static int idRepobrowser            = wxNewId();
static int idRevert                 = wxNewId();
static int idRevisiongraph          = wxNewId();
static int idLock                   = wxNewId();
static int idUnLock                 = wxNewId();
static int idCheckForModifications  = wxNewId();
static int idBlame                  = wxNewId();
static int idProperties             = wxNewId();
static int idSettings               = wxNewId();
static int idOnMakeReadonly         = wxNewId();
static int idOnMakeReadWrite        = wxNewId();
static int idOnAbout                = wxNewId();

//******************************************************************************

// Implement the plugin's hooks
//CB_IMPLEMENT_PLUGIN(CBTortoiseSVN, "CBTortoiseSVN");
// Register the plugin

namespace
{
    PluginRegistrant<CBTortoiseSVN> reg(_T("CBTortoiseSVN"));
};

BEGIN_EVENT_TABLE(CBTortoiseSVN, cbPlugin)
    EVT_MENU(idAdd,                   CBTortoiseSVN::OnAdd)
    EVT_MENU(idCommit,                CBTortoiseSVN::OnCommit)
    EVT_MENU(idDiffWithBase,          CBTortoiseSVN::OnDiffWithBase)
    EVT_MENU(idLog,                   CBTortoiseSVN::OnLog)
    EVT_MENU(idRepobrowser,           CBTortoiseSVN::OnRepobrowser)
    EVT_MENU(idRevert,                CBTortoiseSVN::OnRevert)
    EVT_MENU(idRevisiongraph,         CBTortoiseSVN::OnRevisiongraph)
    EVT_MENU(idLock,                  CBTortoiseSVN::OnLock)
    EVT_MENU(idUnLock,                CBTortoiseSVN::OnUnLock)
    EVT_MENU(idCheckForModifications, CBTortoiseSVN::OnCheckForModifications)
    EVT_MENU(idBlame,                 CBTortoiseSVN::OnBlame)
    EVT_MENU(idProperties,            CBTortoiseSVN::OnProperties)
    EVT_MENU(idSettings,              CBTortoiseSVN::OnSettings)
    EVT_MENU(idOnMakeReadonly,        CBTortoiseSVN::OnMakeReadonly)
    EVT_MENU(idOnMakeReadWrite,       CBTortoiseSVN::OnMakeReadWrite)
    EVT_MENU(idOnAbout,               CBTortoiseSVN::OnAbout)


    EVT_UPDATE_UI(idAdd,                   CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idCommit,                CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idDiffWithBase,          CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idLog,                   CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idRepobrowser,           CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idRevert,                CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idRevisiongraph,         CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idLock,                  CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idUnLock,                CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idCheckForModifications, CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idBlame,                 CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idProperties,            CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idSettings,              CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idOnMakeReadonly,        CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idOnMakeReadWrite,       CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idOnAbout,               CBTortoiseSVN::OnUpdateUI)
END_EVENT_TABLE()

//******************************************************************************

void CBTortoiseSVN::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
}

//******************************************************************************

void CBTortoiseSVN::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is false, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

//******************************************************************************

void CBTortoiseSVN::BuildMenu(wxMenuBar *menuBar)
{
    // insert menu items
    wxMenu *TortoiseSVN_submenu = new wxMenu;
    TortoiseSVN_submenu->Append(idDiffWithBase,          _("Diff with base..."),           _("Diff with base"));
    TortoiseSVN_submenu->Append(idAdd,                   _("Add..."),                      _("Add"));
    TortoiseSVN_submenu->Append(idCommit,                _("Commit..."),                   _("Commit"));
    TortoiseSVN_submenu->Append(idLog,                   _("Log..."),                      _("Log"));
    TortoiseSVN_submenu->Append(idRepobrowser,           _("Repobrowser..."),              _("Repobowser"));
    TortoiseSVN_submenu->Append(idRevisiongraph,         _("Revisiongraph..."),            _("Revisiongraph"));
    TortoiseSVN_submenu->Append(idLock,                  _("Lock..."),                     _("Lock"));
    TortoiseSVN_submenu->Append(idUnLock,                _("UnLock..."),                   _("UnLock"));
    TortoiseSVN_submenu->Append(idRevert,                _("Revert..."),                   _("Revert"));
    TortoiseSVN_submenu->Append(idBlame,                 _("Blame..."),                    _("Blame"));
    TortoiseSVN_submenu->Append(idCheckForModifications, _("Check for modifications..."),  _("Check for modifications"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idOnMakeReadonly,        _("Make Readonly..."),            _("Make Readonly"));
    TortoiseSVN_submenu->Append(idOnMakeReadWrite,       _("Make Read/Write..."),          _("Make Read/Write"));
    TortoiseSVN_submenu->Append(idProperties,            _("Properties..."),               _("Properties"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idSettings,              _("TortoiseSVN Settings..."),     _("TortoiseSVN Settings"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idOnAbout,               _("About..."),                    _("About CBTortoiseSVN"));

    int ToolsPos = menuBar->FindMenu(_("&Tools"));

    if ( ToolsPos == wxNOT_FOUND )
        menuBar->Append(TortoiseSVN_submenu,_("TortoiseSVN"));
    else
        menuBar->Insert(ToolsPos,TortoiseSVN_submenu,_("TortoiseSVN"));
}

//******************************************************************************

void CBTortoiseSVN::RemoveMenu(wxMenuBar *menuBar)
{
    wxMenu *menu = 0;
    wxMenuItem *item = menuBar->FindItem(idCBTortoiseSVN, &menu);

    if (menu && item)
        menu->Remove(item);
}

//******************************************************************************

void CBTortoiseSVN::OnUpdateUI(wxUpdateUIEvent &event)
{
    if (!Manager::isappShuttingDown())
    {
        wxWindow* pAppWin  = wxTheApp->GetTopWindow();
        if (pAppWin)
        {
            wxMenuBar *mbar = ((wxFrame*)pAppWin)->GetMenuBar();
            if (mbar)
            {
                EditorManager *em = Manager::Get()->GetEditorManager();

                // Enabled if there's a source file opened (be sure it isn't the "Start here" page)
                bool disable = !em || !em->GetActiveEditor() || !em->GetBuiltinActiveEditor();
                mbar->Enable(idAdd,                     !disable);
                mbar->Enable(idCommit,                  !disable);
                mbar->Enable(idDiffWithBase,            !disable);
                mbar->Enable(idLog,                     !disable);
                mbar->Enable(idRepobrowser,             !disable);
                mbar->Enable(idRevert,                  !disable);
                mbar->Enable(idRevisiongraph,           !disable);
                mbar->Enable(idLock,                    !disable);
                mbar->Enable(idUnLock,                  !disable);
                mbar->Enable(idCheckForModifications,   !disable);
                mbar->Enable(idBlame,                   !disable);
                mbar->Enable(idProperties,              !disable);
                mbar->Enable(idOnMakeReadonly,          !disable);
                mbar->Enable(idOnMakeReadWrite,         !disable);
            }
        }
    }
    event.Skip();
}

//******************************************************************************

bool CBTortoiseSVN::Run(bool blocked, bool hidden, const wxString& command, DWORD& exit_code )
{
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory( &si, sizeof(si) );
    si.cb = sizeof(si);
    ZeroMemory( &pi, sizeof(pi) );

    if (hidden)
    {
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = SW_HIDE;
    }

    exit_code=0;

    wxWCharBuffer buf = command.wc_str(wxConvLocal);
    WCHAR* COMMAND = buf.data();

    // Start the child process.
    bool result = CreateProcess( NULL, COMMAND, NULL, NULL, FALSE, 0,
                                 NULL, NULL, &si, &pi );

    if (blocked)
    {
        // Wait until child process exits.
        WaitForSingleObject( pi.hProcess, INFINITE );

        // Get the return value of the child process
        result = result && GetExitCodeProcess(pi.hProcess, &exit_code);
    }

    // Close process and thread handles.
    CloseHandle( pi.hProcess );
    CloseHandle( pi.hThread );
    return result;
}

//******************************************************************************

bool CBTortoiseSVN::GetCurrentFilename(wxString& filename)
{
    EditorManager* man = Manager::Get()->GetEditorManager();
    if (!man)
        return false;

    // prevent invocation on "start here"
    cbEditor* builtin_active_editor = man->GetBuiltinActiveEditor();
    if (!builtin_active_editor)
        return false;

    EditorBase* active_editor = man->GetActiveEditor();
    if (!active_editor)
        return false;

    filename = active_editor->GetFilename();
    return true;
}

//******************************************************************************

bool CBTortoiseSVN::FileUnderVersionControl(const wxString& filename)
{
    DWORD exit_code;
    wxString commandline = _("svn status \"") + filename + _("\"");
    if (Run(true, true, commandline, exit_code))
        return (exit_code==0);
    else
        return false;
}

//******************************************************************************

void CBTortoiseSVN::RunSimpleTortoiseSVNCommand(const wxString& command)
{
    wxString filename;
    if (!GetCurrentFilename(filename))
        return;

    if (!FileUnderVersionControl(filename))
    {
        wxMessageBox(_("File is not a working copy or svn.exe not found."), _("Info"),
                     wxOK | wxICON_INFORMATION);
        return;
    }

    wxString commandline =
        _("TortoiseProc /command:")
        + command
        + _(" /path:\"")
        + filename
        +_("\" /notempfile");

    DWORD exit_code;
    if (!Run(false, false, commandline, exit_code))
        wxMessageBox(_("Command \"") + commandline + _("\" failed"), _("Info"),
                     wxOK | wxICON_ERROR);
}

//******************************************************************************

void CBTortoiseSVN::OnAdd(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("add"));
}

//******************************************************************************

void CBTortoiseSVN::OnCommit(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("commit"));
}

//******************************************************************************

void CBTortoiseSVN::OnDiffWithBase(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("diff"));
}

//******************************************************************************

void CBTortoiseSVN::OnLog(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("log"));
}

//******************************************************************************

void CBTortoiseSVN::OnRepobrowser(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("repobrowser"));
}

//******************************************************************************

void CBTortoiseSVN::OnRevert(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("revert"));
}

//******************************************************************************

void CBTortoiseSVN::OnRevisiongraph(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("revisiongraph"));
}

//******************************************************************************

void CBTortoiseSVN::OnLock(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("lock"));
}

//******************************************************************************

void CBTortoiseSVN::OnUnLock(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("unlock"));
}

//******************************************************************************

void CBTortoiseSVN::OnCheckForModifications(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("repostatus"));
}

//******************************************************************************

void CBTortoiseSVN::OnBlame(wxCommandEvent &event)
{
    RunSimpleTortoiseSVNCommand(_("blame"));
}

//******************************************************************************

void CBTortoiseSVN::OnProperties(wxCommandEvent &event)
{
    wxString filename;
    if (!GetCurrentFilename(filename))
        return;

    SHELLEXECUTEINFO sei;

    ZeroMemory(&sei,sizeof(sei));
    sei.cbSize = sizeof(sei);
    sei.lpFile = filename.c_str();
    sei.lpVerb = _("properties");
    sei.fMask  = SEE_MASK_INVOKEIDLIST;
    ShellExecuteEx(&sei);
}
//******************************************************************************

void CBTortoiseSVN::OnSettings(wxCommandEvent &event)
{
    DWORD exit_code;
    wxString commandline = _("TortoiseProc /command:settings");
    if (!Run(false, false, commandline, exit_code))
        wxMessageBox(_("Command \"") + commandline + _("\" failed"), _("Info"),
                     wxOK | wxICON_ERROR);
}

//******************************************************************************

void CBTortoiseSVN::OnMakeReadonly(wxCommandEvent &event)
{
    wxString filename;
    if (GetCurrentFilename(filename))
        MakeReadonly(filename.c_str());
}

//******************************************************************************

void CBTortoiseSVN::OnMakeReadWrite(wxCommandEvent &event)
{
    wxString filename;
    if (GetCurrentFilename(filename))
        MakeReadWrite(filename.c_str());
}

//******************************************************************************

void CBTortoiseSVN::OnAbout(wxCommandEvent &event)
{
    wxMessageBox(_("Simple ToirtoiseSVN interface for Codeblocks\r\nBy Jan van den Borst"), _("About..."),
                 wxOK | wxICON_INFORMATION);

}

//******************************************************************************

void CBTortoiseSVN::MakeReadonly( LPCTSTR lpFileName)
{
    DWORD dwFileAttributes = GetFileAttributes( lpFileName);

    long mask = dwFileAttributes;

    if (dwFileAttributes & FILE_ATTRIBUTE_READONLY)
        return;

    mask = dwFileAttributes | FILE_ATTRIBUTE_READONLY;
    SetFileAttributes( lpFileName, mask);
}

//******************************************************************************

void CBTortoiseSVN::MakeReadWrite( LPCTSTR lpFileName)
{
    DWORD dwFileAttributes = GetFileAttributes( lpFileName);

    if (!( dwFileAttributes & FILE_ATTRIBUTE_READONLY))
        return;

    long mask = dwFileAttributes & (~FILE_ATTRIBUTE_READONLY);
    SetFileAttributes( lpFileName, mask);
}

//******************************************************************************
// End of file
