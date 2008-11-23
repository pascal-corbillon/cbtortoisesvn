//******************************************************************************
//* Name:      utils.cpp
//* Purpose:   CBTortoiseSVN  utilities
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#include "pch.h"
#include "utils.h"

//******************************************************************************
using namespace CBSVN;
//******************************************************************************

wxString CBSVN::GetBaseDir(const wxString& filename)
{
    wxFileName base(filename);
    return base.GetPath(wxPATH_GET_VOLUME);
}

//******************************************************************************

void CBSVN::GetFolders(const wxString& plugin_name)
{
    wxMessageBox(ConfigManager::GetDataFolder()
                 , _("GetDataFolder..."),
                 wxOK | wxICON_INFORMATION);

    wxMessageBox(ConfigManager::GetConfigFolder()
                 , _("GetConfigFolder..."),
                 wxOK | wxICON_INFORMATION);

    wxMessageBox(ConfigManager::GetDataFolder()
                 , _("GetDataFolder..."),
                 wxOK | wxICON_INFORMATION);

    wxMessageBox(GetGlobalIniFile(plugin_name)
                 , _("GetGlobalIniFile..."),
                 wxOK | wxICON_INFORMATION);
}

//******************************************************************************

bool CBSVN::Run(bool blocked, bool hidden, const wxString& command, unsigned long& exit_code )
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

wxString CBSVN::GetGlobalIniFile(const wxString& plugin_name)
{
    return ConfigManager::GetConfigFolder() + _("\\") + plugin_name + _(".ini");
}

//******************************************************************************

bool CBSVN::ReadStringFromGlobalInifile(const wxString& plugin_name, const wxString& key, wxString& value)
{
    return ReadStringFromInifile(plugin_name, GetGlobalIniFile(plugin_name), key,value);
}

//******************************************************************************

bool CBSVN::WriteStringToGlobalInifile(const wxString& plugin_name,const wxString& key, const wxString& value)
{
    return WriteStringToInifile(plugin_name, GetGlobalIniFile(plugin_name), key, value);
}

//******************************************************************************

wxString CBSVN::GetWorkspaceBaseDir()
{
    return GetBaseDir(GetWorkspaceFilename());
}

//******************************************************************************

wxString CBSVN::GetWorkspaceFilename()
{
    cbWorkspace* workspace = Manager::Get()->GetProjectManager()->GetWorkspace();
    if (!workspace)
        return _("");

    return workspace->GetFilename();
}

//******************************************************************************

wxString CBSVN::GetProjectBaseDir()
{
    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
    if (!project)
        return _("");

    return project->GetBasePath();
}
//******************************************************************************

wxString CBSVN::GetProjectFilename()
{
    cbProject* project = Manager::Get()->GetProjectManager()->GetActiveProject();
    if (!project)
        return _("");

    return project->GetFilename();
}

//******************************************************************************

wxString CBSVN::GetProjectIniFile(const wxString& plugin_name)
{
    return GetProjectBaseDir() + plugin_name + _(".ini");
}

//******************************************************************************

bool CBSVN::ReadStringFromProjectInifile(const wxString& plugin_name, const wxString& key, wxString& value)
{
    return ReadStringFromInifile(plugin_name, GetProjectIniFile(plugin_name), key,value);
}

//******************************************************************************

bool CBSVN::ReadStringFromInifile(const wxString& plugin_name, const wxString& inifile, const wxString& key, wxString& value)
{
    wxFileConfig configFile(plugin_name, wxT("Code::Blocks"), inifile);
    return configFile.Read(key,&value);
}

//******************************************************************************

bool CBSVN::WriteStringToProjectInifile(const wxString& plugin_name, const wxString& key, const wxString& value)
{
    return WriteStringToInifile(plugin_name, GetProjectIniFile(plugin_name), key, value);
}

//******************************************************************************

bool CBSVN::WriteStringToInifile(const wxString& plugin_name, const wxString& inifile, const wxString& key, const wxString& value)
{
    wxFileConfig configFile(plugin_name, wxT("Code::Blocks"), inifile);
    return configFile.Write(key, value);
}

//******************************************************************************
// End of file
