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

using namespace CBTSVN;

//******************************************************************************

// Main menu
static int idCBTortoiseSVN                  = wxNewId();
static int idAdd                            = wxNewId();
static int idRemove                         = wxNewId();
static int idCommit                         = wxNewId();
static int idDiffWithBase                   = wxNewId();
static int idLog                            = wxNewId();
static int idRepobrowser                    = wxNewId();
static int idRevert                         = wxNewId();
static int idRevisiongraph                  = wxNewId();
static int idLock                           = wxNewId();
static int idUnLock                         = wxNewId();
static int idCheckForModifications          = wxNewId();
static int idUpdate                         = wxNewId();
static int idBlame                          = wxNewId();
static int idProperties                     = wxNewId();
static int idSettings                       = wxNewId();
static int idMakeReadonly                   = wxNewId();
static int idMakeReadWrite                  = wxNewId();
static int idAbout                          = wxNewId();
static int idConfiguration                  = wxNewId();
static int idExplore                        = wxNewId();
static int idCheckout                       = wxNewId();
static int idCleanup                        = wxNewId();
static int idMerge                          = wxNewId();
static int idConflictEditor                 = wxNewId();
static int idFileBased                      = wxNewId();
static int idProjectBased                   = wxNewId();
static int idWorkspaceBased                 = wxNewId();

// popup menu
static int idPopupAdd                       = wxNewId();
static int idPopupRemove                    = wxNewId();
static int idPopupCommit                    = wxNewId();
static int idPopupProperties                = wxNewId();
static int idPopupDiffWithBase              = wxNewId();
static int idPopupLog                       = wxNewId();
static int idPopupRepobrowser               = wxNewId();
static int idPopupRevert                    = wxNewId();
static int idPopupRevisiongraph             = wxNewId();
static int idPopupLock                      = wxNewId();
static int idPopupUnLock                    = wxNewId();
static int idPopupCheckForModifications     = wxNewId();
static int idPopupBlame                     = wxNewId();
static int idPopupUpdate                    = wxNewId();
static int idPopupExplore                   = wxNewId();
static int idPopupCleanup                   = wxNewId();
static int idPopupMerge                     = wxNewId();
static int idPopupConflictEditor            = wxNewId();

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
    EVT_MENU(idRemove,                      CBTortoiseSVN::OnRemove)
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
    EVT_MENU(idCheckout,                    CBTortoiseSVN::OnCheckout)
    EVT_MENU(idCleanup,                     CBTortoiseSVN::OnCleanup)
    EVT_MENU(idMerge,                       CBTortoiseSVN::OnMerge)
    EVT_MENU(idConflictEditor,              CBTortoiseSVN::OnConflictEditor)

    EVT_MENU(idPopupAdd,                    CBTortoiseSVN::OnPopupAdd)
    EVT_MENU(idPopupRemove,                 CBTortoiseSVN::OnPopupRemove)
    EVT_MENU(idPopupProperties,             CBTortoiseSVN::OnPopupProperties)
    EVT_MENU(idPopupCommit,                 CBTortoiseSVN::OnPopupCommit)
    EVT_MENU(idPopupProperties,             CBTortoiseSVN::OnPopupProperties)
    EVT_MENU(idPopupDiffWithBase,           CBTortoiseSVN::OnPopupDiffWithBase)
    EVT_MENU(idPopupLog,                    CBTortoiseSVN::OnPopupLog)
    EVT_MENU(idPopupRepobrowser,            CBTortoiseSVN::OnPopupRepobrowser)
    EVT_MENU(idPopupRevert,                 CBTortoiseSVN::OnPopupRevert)
    EVT_MENU(idPopupRevisiongraph,          CBTortoiseSVN::OnPopupRevisiongraph)
    EVT_MENU(idPopupLock,                   CBTortoiseSVN::OnPopupLock)
    EVT_MENU(idPopupUnLock,                 CBTortoiseSVN::OnPopupUnLock)
    EVT_MENU(idPopupCheckForModifications,  CBTortoiseSVN::OnPopupCheckForModifications)
    EVT_MENU(idPopupBlame,                  CBTortoiseSVN::OnPopupBlame)
    EVT_MENU(idPopupUpdate,                 CBTortoiseSVN::OnPopupUpdate)
    EVT_MENU(idPopupExplore,                CBTortoiseSVN::OnPopupExplore)
    EVT_MENU(idPopupCleanup,                CBTortoiseSVN::OnPopupCleanup)
    EVT_MENU(idPopupMerge,                  CBTortoiseSVN::OnPopupMerge)
    EVT_MENU(idPopupConflictEditor,         CBTortoiseSVN::OnPopupConflictEditor)

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
    EVT_UPDATE_UI(idCheckout,               CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idCleanup,                CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idMerge,                  CBTortoiseSVN::OnUpdateUI)
    EVT_UPDATE_UI(idConflictEditor,         CBTortoiseSVN::OnUpdateUI)

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

bool CBTortoiseSVN::GetFileUnderVersionControl(CBSvnPluginManager::SourceMenu menu, const wxString& filename)
{
    if (CBSvnPluginManager::GetInstance().GetMaxIntegrationPerformance())
        return true;

    bool result;
    if (m_cache.find(filename)==m_cache.end())
    {
        result=CBSvnPluginManager::GetInstance().FileUnderVersionControl(filename);
        m_cache[filename]=result;
    }
    else
        result=m_cache[filename];
    return result;
}

//******************************************************************************

void CBTortoiseSVN::OnAdd(wxCommandEvent &event)                        {Add(MAIN_MENU);}
void CBTortoiseSVN::OnPopupAdd(wxCommandEvent &event)                   {Add(POPUP_MENU);}

void CBTortoiseSVN::OnRemove(wxCommandEvent &event)                     {Remove(MAIN_MENU);}
void CBTortoiseSVN::OnPopupRemove(wxCommandEvent &event)                {Remove(POPUP_MENU);}

void CBTortoiseSVN::OnCommit(wxCommandEvent &event)                     {Commit(MAIN_MENU);}
void CBTortoiseSVN::OnPopupCommit(wxCommandEvent &event)                {Commit(POPUP_MENU);}

void CBTortoiseSVN::OnDiffWithBase(wxCommandEvent &event)               {DiffWithBase(MAIN_MENU);}
void CBTortoiseSVN::OnPopupDiffWithBase(wxCommandEvent &event)          {DiffWithBase(POPUP_MENU);}

void CBTortoiseSVN::OnLog(wxCommandEvent &event)                        {Log(MAIN_MENU);}
void CBTortoiseSVN::OnPopupLog(wxCommandEvent &event)                   {Log(POPUP_MENU);}

void CBTortoiseSVN::OnRepobrowser(wxCommandEvent &event)                {Repobrowser(MAIN_MENU);}
void CBTortoiseSVN::OnPopupRepobrowser(wxCommandEvent &event)           {Repobrowser(POPUP_MENU);}

void CBTortoiseSVN::OnRevert(wxCommandEvent &event)                     {Revert(MAIN_MENU);}
void CBTortoiseSVN::OnPopupRevert(wxCommandEvent &event)                {Revert(POPUP_MENU);}

void CBTortoiseSVN::OnRevisiongraph(wxCommandEvent &event)              {Revisiongraph(MAIN_MENU);}
void CBTortoiseSVN::OnPopupRevisiongraph(wxCommandEvent &event)         {Revisiongraph(POPUP_MENU);}

void CBTortoiseSVN::OnLock(wxCommandEvent &event)                       {Lock(MAIN_MENU);}
void CBTortoiseSVN::OnPopupLock(wxCommandEvent &event)                  {Lock(POPUP_MENU);}

void CBTortoiseSVN::OnUnLock(wxCommandEvent &event)                     {UnLock(MAIN_MENU);}
void CBTortoiseSVN::OnPopupUnLock(wxCommandEvent &event)                {UnLock(POPUP_MENU);}

void CBTortoiseSVN::OnCheckForModifications(wxCommandEvent &event)      {CheckForModifications(MAIN_MENU);}
void CBTortoiseSVN::OnPopupCheckForModifications(wxCommandEvent &event) {CheckForModifications(POPUP_MENU);}

void CBTortoiseSVN::OnBlame(wxCommandEvent &event)                      {Blame(MAIN_MENU);}
void CBTortoiseSVN::OnPopupBlame(wxCommandEvent &event)                 {Blame(POPUP_MENU);}

void CBTortoiseSVN::OnUpdate(wxCommandEvent &event)                     {Update(MAIN_MENU);}
void CBTortoiseSVN::OnPopupUpdate(wxCommandEvent &event)                {Update(POPUP_MENU);}

void CBTortoiseSVN::OnProperties(wxCommandEvent &event)                 {Properties(MAIN_MENU);}
void CBTortoiseSVN::OnPopupProperties(wxCommandEvent &event)            {Properties(POPUP_MENU);}

void CBTortoiseSVN::OnExplore(wxCommandEvent &event)                    {Explore(MAIN_MENU);}
void CBTortoiseSVN::OnPopupExplore(wxCommandEvent &event)               {Explore(POPUP_MENU);}

void CBTortoiseSVN::OnCleanup(wxCommandEvent &event)                    {Cleanup(MAIN_MENU);}
void CBTortoiseSVN::OnPopupCleanup(wxCommandEvent &event)               {Cleanup(POPUP_MENU);}

void CBTortoiseSVN::OnMerge(wxCommandEvent &event)                      {Merge(MAIN_MENU);}
void CBTortoiseSVN::OnPopupMerge(wxCommandEvent &event)                 {Merge(POPUP_MENU);}

void CBTortoiseSVN::OnConflictEditor(wxCommandEvent &event)             {ConflictEditor(MAIN_MENU);}
void CBTortoiseSVN::OnPopupConflictEditor(wxCommandEvent &event)        {ConflictEditor(POPUP_MENU);}

void CBTortoiseSVN::OnCheckout(wxCommandEvent &event)                   {Checkout(MAIN_MENU);}

//******************************************************************************

void CBTortoiseSVN::BuildMenu(wxMenuBar *menuBar)
{

    if (!CBSvnPluginManager::GetInstance().GetMainMenuIntegration())
        return;

    // insert menu items
    wxMenu *TortoiseSVN_submenu = new wxMenu;

    TortoiseSVN_submenu->Append(idDiffWithBase,          _("Diff with base..."),           _("Diff with base"));
    TortoiseSVN_submenu->Append(idAdd,                   _("Add..."),                      _("Add"));
    TortoiseSVN_submenu->Append(idRemove,                _("Remove..."),                   _("Remove"));
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
    TortoiseSVN_submenu->Append(idCheckout,              _("Checkout..."),                 _("Checkout"));
    TortoiseSVN_submenu->Append(idCleanup,               _("Cleanup..."),                  _("Cleanup"));
    TortoiseSVN_submenu->Append(idMerge,                 _("Merge..."),                    _("Merge"));
    TortoiseSVN_submenu->Append(idConflictEditor,        _("Conflict editor..."),          _("Conflict editor"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idSettings,              _("TortoiseSVN Settings..."),     _("TortoiseSVN Settings"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idConfiguration,         _("Plugin settings..."),          _("CBTortoiseSVN settings"));
    TortoiseSVN_submenu->AppendSeparator();
    TortoiseSVN_submenu->Append(idAbout,                 _("About..."),                    _("About CBTortoiseSVN"));

    MAIN_MENU.SetFileBased(TortoiseSVN_submenu->FindItem(idFileBased)->IsChecked());
    MAIN_MENU.SetProjectBased(TortoiseSVN_submenu->FindItem(idProjectBased)->IsChecked());
    MAIN_MENU.SetWorkspaceBased(TortoiseSVN_submenu->FindItem(idWorkspaceBased)->IsChecked());

    int ToolsPos = menuBar->FindMenu(_("&Tools"));

    if (ToolsPos == wxNOT_FOUND)
        menuBar->Append(TortoiseSVN_submenu,_("TortoiseSVN"));
    else
        menuBar->Insert(ToolsPos,TortoiseSVN_submenu,_("TortoiseSVN"));
}

//******************************************************************************

void CBTortoiseSVN::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    if (!IsAttached())
        return;

    bool file_based=true;
    bool project_based=false;

    if (type == mtEditorManager)
    {
        if (!CBSvnPluginManager::GetInstance().GetEditorIntegration())
            return;

        cbEditor* ed = Manager::Get()->GetEditorManager()->GetBuiltinActiveEditor();
        if (!ed)
            return;

        POPUP_MENU.SetFileBased(true);
        POPUP_MENU.SetProjectBased(false);
        POPUP_MENU.SetWorkspaceBased(false);
        POPUP_MENU.SetFilename(ed->GetFilename());
    }
    else if (type == mtProjectManager && menu)
    {
        if (!CBSvnPluginManager::GetInstance().GetProjectManagerIntegration())
            return;

        project_based  = (data && data->GetKind() == FileTreeData::ftdkProject);
        file_based     = (data && data->GetKind() == FileTreeData::ftdkFile);

        if (!(project_based || file_based))
            return;

        if (project_based)
        {
            // popup menu on a project
            POPUP_MENU.SetFileBased(false);
            POPUP_MENU.SetProjectBased(true);
            POPUP_MENU.SetWorkspaceBased(false);
            POPUP_MENU.SetFilename(data->GetProject()->GetFilename());
        }
        else if (file_based)
        {
            // popup menu on a file
            POPUP_MENU.SetFileBased(true);
            POPUP_MENU.SetProjectBased(false);
            POPUP_MENU.SetWorkspaceBased(false);
            POPUP_MENU.SetFilename(data->GetProjectFile()->file.GetFullPath());
        }
    }

    bool SVN_file=GetFileUnderVersionControl(CBSvnPluginManager::smPopupMenu, POPUP_MENU.GetFilename());

    wxMenu* submenu = new wxMenu;
    if (SVN_file)                submenu->Append(idPopupDiffWithBase,             _("Diff with base"));
    if (!SVN_file)                submenu->Append(idPopupAdd,                      _("Add"));
    if (SVN_file&&file_based)    submenu->Append(idPopupRemove,                   _("Remove"));
    if (SVN_file)                submenu->Append(idPopupCommit,                   _("Commit"));
    if (SVN_file)                submenu->Append(idPopupLog,                      _("Log"));
    if (SVN_file)                submenu->Append(idPopupRepobrowser,              _("Reprobrowser"));
    if (SVN_file)                submenu->Append(idPopupRevisiongraph,            _("Revision graph"));
    if (SVN_file)                submenu->Append(idPopupLock,                     _("Lock"));
    if (SVN_file)                submenu->Append(idPopupUnLock,                   _("Unlock"));
    if (SVN_file)                submenu->Append(idPopupRevert,                   _("Revert"));
    if (SVN_file&&file_based)    submenu->Append(idPopupBlame,                    _("Blame"));
    if (SVN_file)                submenu->Append(idPopupCheckForModifications,    _("Check for modifications"));
    if (SVN_file)                submenu->Append(idPopupUpdate,                   _("Update"));
    submenu->AppendSeparator();
    submenu->Append(idPopupProperties,                                            _("Properties"));
    submenu->Append(idPopupExplore,                                               _("Explore"));
    submenu->AppendSeparator();
    if (SVN_file&&project_based) submenu->Append(idPopupCleanup,                  _("Cleanup"));
    if (SVN_file&&project_based) submenu->Append(idPopupMerge,                    _("Merge"));
    if (SVN_file&&project_based) submenu->Append(idPopupConflictEditor,           _("Conflict editor"));
    if (SVN_file&&project_based) submenu->AppendSeparator();
    submenu->Append(idSettings,                                                   _("TortoiseSVN Settings"));
    submenu->Append(idConfiguration,                                              _("Plugin settings"));
    menu->AppendSeparator();
    menu->AppendSubMenu(submenu,                                                  _("TortoiseSVN"));
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
                wxString filename;
                bool file_based      = MAIN_MENU.GetFileBased();
                bool project_based   = MAIN_MENU.GetProjectBased();
                bool workspace_based = MAIN_MENU.GetWorkspaceBased();

                if (file_based){filename=GetEditorFilename();}
                if (project_based){filename=GetProjectFilename();}
                if (workspace_based){filename=GetWorkspaceFilename();}

                if (filename!=MAIN_MENU.GetFilename())
                {
                    MAIN_MENU.SetFilename(filename);
                    LogMenu(MAIN_MENU);
                }

                file_based=file_based&&(filename!=_(""));
                project_based=project_based&&(filename!=_(""));
                workspace_based=workspace_based&&(filename!=_(""));

                bool SVN_file=GetFileUnderVersionControl(CBSvnPluginManager::smMainMenu, MAIN_MENU.GetFilename());

                mbar->Enable(idAdd,                  !SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idRemove,                SVN_file && (file_based));
                mbar->Enable(idCommit,                SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idDiffWithBase,          SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idLog,                   SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idRepobrowser,           SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idRevert,                SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idRevisiongraph,         SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idLock,                  SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idUnLock,                SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idCheckForModifications, SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idUpdate,                SVN_file && (file_based || project_based || workspace_based));
                mbar->Enable(idBlame,                 SVN_file && (file_based));
                mbar->Enable(idCleanup,               SVN_file && (project_based || workspace_based));
                mbar->Enable(idMerge,                 SVN_file && (project_based || workspace_based));
                mbar->Enable(idConflictEditor,        SVN_file && (project_based || workspace_based));
                mbar->Enable(idProperties,                         file_based || project_based || workspace_based);
                mbar->Enable(idExplore,                            file_based || project_based || workspace_based);
                mbar->Enable(idMakeReadonly,                       file_based);
                mbar->Enable(idMakeReadWrite,                      file_based);
            }
        }
    }
    event.Skip();
}

//******************************************************************************

void CBTortoiseSVN::Add(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("add"));
}

//******************************************************************************

void CBTortoiseSVN::Remove(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("remove"));
}

//******************************************************************************

void CBTortoiseSVN::Commit(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu,_("commit"));
}

//******************************************************************************

void CBTortoiseSVN::Cleanup(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu,_("cleanup"));
}

//******************************************************************************

void CBTortoiseSVN::DiffWithBase(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("diff"));
}

//******************************************************************************

void CBTortoiseSVN::Log(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("log"));
}

//******************************************************************************

void CBTortoiseSVN::Repobrowser(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("repobrowser"));
}

//******************************************************************************

void CBTortoiseSVN::Revert(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("revert"));
}

//******************************************************************************

void CBTortoiseSVN::Revisiongraph(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("revisiongraph"));
}

//******************************************************************************

void CBTortoiseSVN::Lock(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("lock"));
}

//******************************************************************************

void CBTortoiseSVN::UnLock(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu,_("unlock"));
}

//******************************************************************************

void CBTortoiseSVN::CheckForModifications(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("repostatus"));
}

//******************************************************************************

void CBTortoiseSVN::Blame(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu,_("blame"));
}

//******************************************************************************

void CBTortoiseSVN::Update(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("update"));
}

//******************************************************************************

void CBTortoiseSVN::Merge(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("merge"));
}

//******************************************************************************

void CBTortoiseSVN::ConflictEditor(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _("conflicteditor"));
}

//******************************************************************************

void CBTortoiseSVN::Checkout(const IMenuCmd& menu)
{
    CBSvnPluginManager::GetInstance().RunSimpleTortoiseSVNCommand(menu, _(""), _("/command:checkout"));
}

//******************************************************************************

void CBTortoiseSVN::Properties(const IMenuCmd& menu)
{
    wxString filename=menu.GetFilename();

    if (filename!=_(""))
    {
        if (menu.GetProjectBased()||
                menu.GetWorkspaceBased())
            filename=CBTSVN::GetBaseDir(filename);

        SHELLEXECUTEINFO sei;

        ZeroMemory(&sei,sizeof(sei));
        sei.cbSize = sizeof(sei);
        sei.lpFile = filename.c_str();
        sei.lpVerb = _("properties");
        sei.fMask  = SEE_MASK_INVOKEIDLIST;
        ShellExecuteEx(&sei);
    }
}

//******************************************************************************

void CBTortoiseSVN::Explore(const IMenuCmd& menu)
{
    wxString filename=menu.GetFilename();

    if (filename!=_(""))
    {
        if (menu.GetProjectBased()||
                menu.GetWorkspaceBased())
            filename=CBTSVN::GetBaseDir(filename);

        unsigned long exit_code;
        wxString commandline = _("explorer.exe ") + filename;

        Logger::GetInstance().log(_("Executing: ") + commandline);

        Run(false,false,commandline,exit_code);
    }
}

//******************************************************************************

void CBTortoiseSVN::OnSettings(wxCommandEvent &event)
{
    DWORD exit_code;
    wxString commandline = _("\"") + CBSvnPluginManager::GetInstance().GetTortoiseproc() +
                           _("\"") +  + _(" /command:settings");
    Logger::GetInstance().log(_("Executing: ") + commandline);
    if (!Run(false, false, commandline, exit_code))
        wxMessageBox(_("Command \"") + commandline + _("\" failed"), _("Info"),
                     wxOK | wxICON_ERROR);
}

//******************************************************************************

void CBTortoiseSVN::OnMakeReadonly(wxCommandEvent &event)
{
    wxString filename=MAIN_MENU.GetFilename();

    if (filename!=_(""))
        MakeReadonly(filename.c_str());
}

//******************************************************************************

void CBTortoiseSVN::OnMakeReadWrite(wxCommandEvent &event)
{
    wxString filename=MAIN_MENU.GetFilename();

    if (filename!=_(""))
    {
        MakeReadWrite(filename.c_str());
    }
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

    MAIN_MENU.SetFileBased(mbar->IsChecked(idFileBased));
    MAIN_MENU.SetProjectBased(mbar->IsChecked(idProjectBased));
    MAIN_MENU.SetWorkspaceBased(mbar->IsChecked(idWorkspaceBased));

    LogMenu(MAIN_MENU);
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

void CBTortoiseSVN::MakeReadonly(LPCTSTR lpFileName)
{
    DWORD dwFileAttributes = GetFileAttributes(lpFileName);

    long mask = dwFileAttributes;

    if (dwFileAttributes & FILE_ATTRIBUTE_READONLY)
        return;

    mask = dwFileAttributes | FILE_ATTRIBUTE_READONLY;
    SetFileAttributes(lpFileName, mask);
}

//******************************************************************************

void CBTortoiseSVN::MakeReadWrite(LPCTSTR lpFileName)
{
    DWORD dwFileAttributes = GetFileAttributes(lpFileName);

    if (!(dwFileAttributes & FILE_ATTRIBUTE_READONLY))
        return;

    long mask = dwFileAttributes & (~FILE_ATTRIBUTE_READONLY);
    SetFileAttributes(lpFileName, mask);
}

//******************************************************************************
// End of file
