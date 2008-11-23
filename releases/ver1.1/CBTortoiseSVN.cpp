//******************************************************************************
//* Name:      CBTortoiseSVN.cpp
//* Purpose:   Code::Blocks plugin using TortoiseSVN commandline interface
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#include "pch.h"
#include "CBTortoiseSVN.h"
#include "ConfigDialog.h"
#include "CBSvnPluginManager.h"

using namespace CBSVN;

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
static int idUpdate                 = wxNewId();
static int idBlame                  = wxNewId();
static int idProperties             = wxNewId();
static int idSettings               = wxNewId();
static int idMakeReadonly           = wxNewId();
static int idMakeReadWrite          = wxNewId();
static int idAbout                  = wxNewId();
static int idConfiguration          = wxNewId();
static int idExplore                = wxNewId();

static int idFileBased              = wxNewId();
static int idProjectBased           = wxNewId();
static int idWorkspaceBased         = wxNewId();

//******************************************************************************

// Implement the plugin's hooks
//CB_IMPLEMENT_PLUGIN(CBTortoiseSVN, "CBTortoiseSVN");
// Register the plugin

namespace
{
    PluginRegistrant<CBTortoiseSVN> reg(_T("CBTortoiseSVN"));
};

BEGIN_EVENT_TABLE(CBTortoiseSVN, cbPlugin)
    EVT_MENU(idAdd,                         CBTortoiseSVN::OnAdd)
    EVT_MENU(idCommit,                      CBTortoiseSVN::OnCommit)
    EVT_MENU(idDiffWithBase,                CBTortoiseSVN::OnDiffWithBase)
    EVT_MENU(idLog,                         CBTortoiseSVN::OnLog)
    EVT_MENU(idRepobrowser,                 CBTortoiseSVN::OnRepobrowser)
    EVT_MENU(idRevert,                      CBTortoiseSVN::OnRevert)
    EVT_MENU(idRevisiongraph,               CBTortoiseSVN::OnRevisiongraph)
    EVT_MENU(idLock,                        CBTortoiseSVN::OnLock)
    EVT_MENU(idUnLock,                      CBTortoiseSVN::OnUnLock)
    EVT_MENU(idCheckForModifications,       CBTortoiseSVN::OnCheckForModifications)
    EVT_MENU(idUpdate,                      CBTortoiseSVN::OnUpdate)
    EVT_MENU(idBlame,                       CBTortoiseSVN::OnBlame)
    EVT_MENU(idProperties,                  CBTortoiseSVN::OnProperties)
    EVT_MENU(idExplore,                     CBTortoiseSVN::OnExplore)
    EVT_MENU(idSettings,                    CBTortoiseSVN::OnSettings)
    EVT_MENU(idMakeReadonly,                CBTortoiseSVN::OnMakeReadonly)
    EVT_MENU(idMakeReadWrite,               CBTortoiseSVN::OnMakeReadWrite)
    EVT_MENU(idAbout,                       CBTortoiseSVN::OnAbout)
    EVT_MENU(idConfiguration,               CBTortoiseSVN::OnConfiguration)
    EVT_MENU(idFileBased,                   CBTortoiseSVN::OnFileProjectWorkspaceBased)
    EVT_MENU(idProjectBased,                CBTortoiseSVN::OnFileProjectWorkspaceBased)
    EVT_MENU(idWorkspaceBased,              CBTortoiseSVN::OnFileProjectWorkspaceBased)

    EVT_UPDATE_UI(idAdd,                    CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idCommit,                 CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idDiffWithBase,           CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idLog,                    CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idRepobrowser,            CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idRevert,                 CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idRevisiongraph,          CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idLock,                   CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idUnLock,                 CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idCheckForModifications,  CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idUpdate,                 CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idBlame,                  CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idProperties,             CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idExplore,                CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idSettings,               CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idMakeReadonly,           CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idMakeReadWrite,          CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idAbout,                  CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idConfiguration,          CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idFileBased,              CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idProjectBased,           CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idWorkspaceBased,         CBTortoiseSVN::OnUpdateUI)

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
    CBSvnPluginManager::GetInstance().Initialise();
}

//******************************************************************************

void CBTortoiseSVN::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is false, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
    CBSvnPluginManager::GetInstance().Shutdown();
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
    TortoiseSVN_submenu->Append(idUpdate,                _("Update..."),                   _("Update"));
    TortoiseSVN_submenu->AppendSeparator();

    TortoiseSVN_submenu->AppendRadioItem(idFileBased,      _("File based commands"),       _("File based commands"));
    TortoiseSVN_submenu->AppendRadioItem(idProjectBased,   _("Project based commands"),    _("Project based commands"));
    TortoiseSVN_submenu->AppendRadioItem(idWorkspaceBased, _("Workspace based commands"),  _("Workspace based commands"));

    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idMakeReadonly,          _("Make Readonly..."),            _("Make Readonly"));
    TortoiseSVN_submenu->Append(idMakeReadWrite,         _("Make Read/Write..."),          _("Make Read/Write"));
    TortoiseSVN_submenu->Append(idProperties,            _("Properties..."),               _("Properties"));

    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idExplore,               _("Explore..."),                  _("Explore"));
    TortoiseSVN_submenu->AppendSeparator();

    TortoiseSVN_submenu->Append(idSettings,              _("TortoiseSVN Settings..."),     _("TortoiseSVN Settings"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idConfiguration,         _("Plugin settings..."),          _("CBTortoiseSVN settings"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idAbout,                 _("About..."),                    _("About CBTortoiseSVN"));

    CBSvnPluginManager::GetInstance().SetFileBased(TortoiseSVN_submenu->FindItem(idFileBased)->IsChecked());
    CBSvnPluginManager::GetInstance().SetProjectBased(TortoiseSVN_submenu->FindItem(idProjectBased)->IsChecked());
    CBSvnPluginManager::GetInstance().SetWorkspaceBased(TortoiseSVN_submenu->FindItem(idWorkspaceBased)->IsChecked());

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
                bool active_file = !(!em || !em->GetActiveEditor() || !em->GetBuiltinActiveEditor());

                bool active_project=(CBSvnPluginManager::GetInstance().GetCurrentProjectBaseDir()!=_(""));
                bool active_workspace=(CBSvnPluginManager::GetInstance().GetCurrentWorkspaceBaseDir()!=_(""));

                bool file_based      = CBSvnPluginManager::GetInstance().GetFileBased()      && active_file;
                bool project_based   = CBSvnPluginManager::GetInstance().GetProjectBased()   && active_project;
                bool workspace_based = CBSvnPluginManager::GetInstance().GetWorkspaceBased() && active_workspace;

                mbar->Enable(idAdd,                     file_based || project_based || workspace_based);
                mbar->Enable(idCommit,                  file_based || project_based || workspace_based);
                mbar->Enable(idDiffWithBase,            file_based || project_based || workspace_based);
                mbar->Enable(idLog,                     file_based || project_based || workspace_based);
                mbar->Enable(idRepobrowser,             file_based || project_based || workspace_based);
                mbar->Enable(idRevert,                  file_based || project_based || workspace_based);
                mbar->Enable(idRevisiongraph,           file_based || project_based || workspace_based);
                mbar->Enable(idLock,                    file_based || project_based || workspace_based);
                mbar->Enable(idUnLock,                  file_based || project_based || workspace_based);
                mbar->Enable(idCheckForModifications,   file_based || project_based || workspace_based);
                mbar->Enable(idUpdate,                  file_based || project_based || workspace_based);
                mbar->Enable(idBlame,                   file_based                                    );
                mbar->Enable(idProperties,              file_based || project_based || workspace_based);
                mbar->Enable(idExplore,                 file_based || project_based || workspace_based);
                mbar->Enable(idMakeReadonly,            file_based                                    );
                mbar->Enable(idMakeReadWrite,           file_based                                    );
            }
        }
    }
    event.Skip();
}

//******************************************************************************

void CBTortoiseSVN::OnAdd(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("add"));
}

//******************************************************************************

void CBTortoiseSVN::OnCommit(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("commit"));
}

//******************************************************************************

void CBTortoiseSVN::OnDiffWithBase(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("diff"));
}

//******************************************************************************

void CBTortoiseSVN::OnLog(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("log"));
}

//******************************************************************************

void CBTortoiseSVN::OnRepobrowser(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("repobrowser"));
}

//******************************************************************************

void CBTortoiseSVN::OnRevert(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("revert"));
}

//******************************************************************************

void CBTortoiseSVN::OnRevisiongraph(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("revisiongraph"));
}

//******************************************************************************

void CBTortoiseSVN::OnLock(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("lock"));
}

//******************************************************************************

void CBTortoiseSVN::OnUnLock(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("unlock"));
}

//******************************************************************************

void CBTortoiseSVN::OnCheckForModifications(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("repostatus"));
}

//******************************************************************************

void CBTortoiseSVN::OnBlame(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("blame"));
}

//******************************************************************************

void CBTortoiseSVN::OnUpdate(wxCommandEvent &event)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(_("update"));
}

//******************************************************************************

void CBTortoiseSVN::OnProperties(wxCommandEvent &event)
{
    wxString filename;
    if (CBSvnPluginManager::GetInstance().GetProjectBased())
        filename=CBSvnPluginManager::GetInstance().GetCurrentProjectFilename();
    else
        if (CBSvnPluginManager::GetInstance().GetWorkspaceBased())
            filename=CBSvnPluginManager::GetInstance().GetCurrentWorkspaceFilename();
        else
            if (!CBSvnPluginManager::GetInstance().GetCurrentFilename(filename))
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

void CBTortoiseSVN::OnExplore(wxCommandEvent &event)
{
    wxString filename;
    if (CBSvnPluginManager::GetInstance().GetProjectBased())
        filename=CBSvnPluginManager::GetInstance().GetCurrentProjectBaseDir();
    else
        if (CBSvnPluginManager::GetInstance().GetWorkspaceBased())
            filename=CBSvnPluginManager::GetInstance().GetCurrentWorkspaceBaseDir();
        else
            if (!CBSvnPluginManager::GetInstance().GetCurrentFilename(filename))
                return;
    unsigned long exit_code;
    wxString commandline = _("explorer.exe ") + filename;

    CBSvnPluginManager::GetInstance().log(_("Executing: ") + commandline);

    Run(false,false,commandline,exit_code);
}

//******************************************************************************

void CBTortoiseSVN::OnSettings(wxCommandEvent &event)
{
    DWORD exit_code;
    wxString commandline = _("\"") + CBSvnPluginManager::GetInstance().GetTortoiseproc() +
                           _("\"") +  + _(" /command:settings");
    CBSvnPluginManager::GetInstance().log(_("Executing: ") + commandline);
    if (!Run(false, false, commandline, exit_code))
        wxMessageBox(_("Command \"") + commandline + _("\" failed"), _("Info"),
                     wxOK | wxICON_ERROR);
}

//******************************************************************************

void CBTortoiseSVN::OnMakeReadonly(wxCommandEvent &event)
{
    wxString filename;
    if (CBSvnPluginManager::GetInstance().GetCurrentFilename(filename))
        MakeReadonly(filename.c_str());
}

//******************************************************************************

void CBTortoiseSVN::OnMakeReadWrite(wxCommandEvent &event)
{
    wxString filename;
    if (CBSvnPluginManager::GetInstance().GetCurrentFilename(filename))
        MakeReadWrite(filename.c_str());
}

//******************************************************************************

void CBTortoiseSVN::OnConfiguration(wxCommandEvent &event)
{
    ConfigDialog dlg(NULL);
    dlg.ShowModal();
}

//******************************************************************************

void CBTortoiseSVN::OnFileProjectWorkspaceBased(wxCommandEvent &event)
{
    if (Manager::isappShuttingDown())
        return;

    wxWindow* pAppWin  = wxTheApp->GetTopWindow();
    if (!pAppWin)
        return;

    wxMenuBar *mbar = ((wxFrame*)pAppWin)->GetMenuBar();
    if (!mbar)
        return;

    CBSvnPluginManager::GetInstance().SetFileBased(mbar->IsChecked(idFileBased));
    CBSvnPluginManager::GetInstance().SetProjectBased(mbar->IsChecked(idProjectBased));
    CBSvnPluginManager::GetInstance().SetWorkspaceBased(mbar->IsChecked(idWorkspaceBased));
}

//******************************************************************************

void CBTortoiseSVN::OnAbout(wxCommandEvent &event)
{
    wxString msg;
    msg+= _("Simple TortoiseSVN interface for Codeblocks\r\n");
    msg+= _("Hosted at http://tools.assembla.com/svn/CBTortoiseSVN\r\n\r\n");
    msg+= _("By Jan van den Borst");
    wxMessageBox(msg, _("About..."), wxOK|wxICON_INFORMATION);
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
