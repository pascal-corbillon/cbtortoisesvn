//******************************************************************************
//* Name:      utils.h
//* Purpose:   CBTortoiseSVN  utilities
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#ifndef _UTILS_H
#define _UTILS_H

//******************************************************************************

#include <wx/string.h>

//******************************************************************************

namespace CBSVN
{
    class Noncopyable
    {
            Noncopyable(const Noncopyable&);
            Noncopyable& operator=(const Noncopyable&);
        protected:
            Noncopyable()
            {}
            ~Noncopyable()
            {}
    };

    // generic os
    bool Run(bool blocked, bool hidden, const wxString& command, unsigned long& exit_code );

    // generic wxWidgets
    wxString GetBaseDir(const wxString& filename);

    // generic codeblocks
    void GetFolders(const wxString& plugin_name);
    wxString GetWorkspaceBaseDir();
    wxString GetWorkspaceFilename();
    wxString GetProjectBaseDir();
    wxString GetProjectFilename();

    // global settings
    wxString GetGlobalIniFile(const wxString& plugin_name);
    bool ReadStringFromGlobalInifile(const wxString& plugin_name, const wxString& key, wxString& value);
    bool WriteStringToGlobalInifile(const wxString& plugin_name, const wxString& key, const wxString& value);

    // project related settings
    wxString GetProjectIniFile(const wxString& plugin_name);
    bool ReadStringFromProjectInifile(const wxString& plugin_name, const wxString& key, wxString& value);
    bool WriteStringToProjectInifile(const wxString& plugin_name, const wxString& key, const wxString& value);

    // general
    bool ReadStringFromInifile(const wxString& plugin_name, const wxString& inifile, const wxString& key, wxString& value);
    bool WriteStringToInifile(const wxString& plugin_name, const wxString& inifile, const wxString& key, const wxString& value);
};

//******************************************************************************
#endif // _UTILS_H
