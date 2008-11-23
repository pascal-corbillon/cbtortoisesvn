//******************************************************************************
//* Name:      CBSvnPluginManager.cpp
//* Purpose:   CBSvnPluginManager
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#include "pch.h"
#include "CBSvnPluginManager.h"

using namespace CBSVN;

//******************************************************************************

const wxString plugin_name     = L"CBTortoiseSVN";
const wxString svnpath         = L"SVNPATH";
const wxString tortoisesvnpath = L"TORTOISESVNPATH";

//******************************************************************************

CBSvnPluginManager::CBSvnPluginManager() :
        m_file_based(false),
        m_project_based(false),
        m_workspace_based(false),
        m_plogdialog(NULL)
{
    wxString value;
    m_svn=_("svn.exe");
    m_tortoisesvnpath=_("tortoiseproc.exe");
    if (ReadStringFromGlobalInifile(plugin_name,svnpath,value))
        m_svn=value;

    if (ReadStringFromGlobalInifile(plugin_name, tortoisesvnpath,value))
        m_tortoisesvnpath=value;
}

//******************************************************************************

wxString CBSvnPluginManager::GetCurrentProjectBaseDir()
{
    return GetProjectBaseDir();
}
//******************************************************************************

wxString CBSvnPluginManager::GetCurrentProjectFilename()
{
    return GetProjectFilename();
}

//******************************************************************************

wxString CBSvnPluginManager::GetCurrentWorkspaceBaseDir()
{
    return GetWorkspaceBaseDir();
}

//******************************************************************************

wxString CBSvnPluginManager::GetCurrentWorkspaceFilename()
{
    return GetWorkspaceFilename();
}

//******************************************************************************

CBSvnPluginManager& CBSvnPluginManager::GetInstance()
{
    static CBSvnPluginManager the_plugin;
    return the_plugin;
}

//******************************************************************************

wxString CBSvnPluginManager::GetSvn() const
{
    return m_svn;
}

//******************************************************************************

void CBSvnPluginManager::SetSvn(const wxString& svn)
{
    if (WriteStringToGlobalInifile(plugin_name, svnpath,svn))
        m_svn=svn;
}

//******************************************************************************

wxString CBSvnPluginManager::GetTortoiseproc() const
{
    return m_tortoisesvnpath;
}

//******************************************************************************

bool CBSvnPluginManager::GetFileBased() const
{
    return m_file_based;
}

//******************************************************************************

void CBSvnPluginManager::SetFileBased(bool FileBased)
{
    m_file_based=FileBased;
}

//******************************************************************************

bool CBSvnPluginManager::GetProjectBased() const
{
    return m_project_based;
}

//******************************************************************************

void CBSvnPluginManager::SetProjectBased(bool project_based)
{
    m_project_based=project_based;
}

//******************************************************************************

bool CBSvnPluginManager::GetWorkspaceBased() const
{
    return m_workspace_based;
}

//******************************************************************************

void CBSvnPluginManager::SetWorkspaceBased(bool WorkspaceBased)
{
    m_workspace_based=WorkspaceBased;
}

//******************************************************************************

void CBSvnPluginManager::SetTortoiseproc(const wxString& tortoiseproc)
{
    if (WriteStringToGlobalInifile(plugin_name,tortoisesvnpath,tortoiseproc))
        m_tortoisesvnpath=tortoiseproc;
}

//******************************************************************************

void CBSvnPluginManager::log(const wxString& s)
{
    if (m_plogdialog.get())
        m_plogdialog.get()->Log(s);
}

//******************************************************************************

void CBSvnPluginManager::ShowLogWindow(bool visible)
{
    if (visible)
    {
        if (!m_plogdialog.get())
            m_plogdialog.reset(new LogDialog(NULL));

        if (!m_plogdialog.get())
            return;

        m_plogdialog.get()->Show();
    }
    else
        m_plogdialog.reset();
}

//******************************************************************************

bool CBSvnPluginManager::GetCurrentFilename(wxString& filename)
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

bool CBSvnPluginManager::FileUnderVersionControl(const wxString& filename)
{
    DWORD exit_code;
    wxString commandline = _("\"") +  GetSvn() + _("\"")
                           + _(" status \"")
                           + filename + _("\"");

    log(_("Executing: ") + commandline);

    if (Run(true, true, commandline, exit_code))
        return (exit_code==0);
    else
        return false;
}

//******************************************************************************

void CBSvnPluginManager::RunSimpleTortoiseSVNCommand(const wxString& command)
{
    wxString filename;
    if (GetProjectBased())
        filename = GetCurrentProjectBaseDir();
    else
        if (GetWorkspaceBased())
            filename = GetCurrentWorkspaceBaseDir();
        else
        {
            if (!GetCurrentFilename(filename))
                return;

            if (!FileUnderVersionControl(filename))
            {
                wxMessageBox(_("File is not a working copy or svn.exe not found."), _("Info"),
                             wxOK | wxICON_INFORMATION);
                return;
            }
        }

    wxString commandline = _("\"") +  GetTortoiseproc() + _("\"")
                           + _(" /command:")
                           + command
                           + _(" /path:\"")
                           + filename
                           +_("\" /notempfile");

    log(_("Executing: ") + commandline);

    DWORD exit_code;
    if (!Run(false, false, commandline, exit_code))
    {
        wxString msg = _("Command \"") + commandline + _("\" failed") + _("\r\n\r\nTry reconfiguring this plugin.");
        wxMessageBox(msg,_("Info"),
                     wxOK | wxICON_ERROR);
    }
}

//******************************************************************************

void CBSvnPluginManager::Initialise()
{
}

//******************************************************************************

void CBSvnPluginManager::Shutdown()
{
    ShowLogWindow(false);
}

//******************************************************************************
// End of file
