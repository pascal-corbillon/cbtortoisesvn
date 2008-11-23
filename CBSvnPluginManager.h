//******************************************************************************
//* Name:      CBSvnPluginManager.h
//* Purpose:   CBSvnPluginManager
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#ifndef _CBSVNPLUGINMANAGER_H
#define _CBSVNPLUGINMANAGER_H

//******************************************************************************

#include <memory>
#include <wx/string.h>
#include "utils.h"
#include "logdialog.h"

//******************************************************************************

namespace CBSVN
{
    class CBSvnPluginManager :
                private Noncopyable
    {
    public:
        static CBSvnPluginManager& GetInstance();

        // project related
        wxString GetCurrentWorkspaceBaseDir();
        wxString GetCurrentWorkspaceFilename();
        wxString GetCurrentProjectBaseDir();
        wxString GetCurrentProjectFilename();


        bool GetCurrentFilename(wxString& filename);

        // location svn.exe
        wxString GetSvn() const;
        void SetSvn(const wxString& svn);

        // location GetTortoiseproc.exe
        wxString GetTortoiseproc() const;
        void SetTortoiseproc(const wxString& svn);

        // FileProjectWorkspaceBased
        bool GetFileBased() const;
        void SetFileBased(bool FileBased);
        bool GetProjectBased() const;
        void SetProjectBased(bool ProjectBased);
        bool GetWorkspaceBased() const;
        void SetWorkspaceBased(bool ProjectBased);

        // logging
        void log(const wxString& s);
        void ShowLogWindow(bool visible);

        // lifecycle
        void Initialise();
        void Shutdown();

        // misc.
        bool FileUnderVersionControl(const wxString& filename);
        void RunSimpleTortoiseSVNCommand(const wxString& command);

    private:
        CBSvnPluginManager();
        ~CBSvnPluginManager(){};

        bool    m_file_based;
        bool    m_project_based;
        bool    m_workspace_based;
        wxString    m_svn;
        wxString    m_tortoisesvnpath;
        std::auto_ptr<LogDialog> m_plogdialog;
    };
};

//******************************************************************************
#endif // _CBSVNPLUGINMANAGER_H
