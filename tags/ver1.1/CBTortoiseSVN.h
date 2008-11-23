//******************************************************************************
//* Name:      CBTortoiseSVN.h
//* Purpose:   Code::Blocks plugin using TortoiseSVN commandline interface
//* Author:    Jan van den Borst
//* Copyright: (c) Jan van den Borst
//* License:   GPL
//******************************************************************************

#ifndef _CBTORTOISESVN_H
#define _CBTORTOISESVN_H

// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <cbplugin.h> // the base class we 're inheriting
#include <settings.h> // needed to use the Code::Blocks SDK

//******************************************************************************

class CBTortoiseSVN : public cbPlugin
{
    public:
        void BuildMenu(wxMenuBar *menuBar);
        void RemoveMenu(wxMenuBar *menuBar);
        void OnAttach(); // fires when the plugin is attached to the application
        void OnRelease(bool appShutDown); // fires when the plugin is released from the application

        // events
        void OnUpdateUI(wxUpdateUIEvent &event);

        void OnAdd(wxCommandEvent &event);
        void OnCommit(wxCommandEvent &event);
        void OnDiffWithBase(wxCommandEvent &event);
        void OnLog(wxCommandEvent &event);
        void OnRepobrowser(wxCommandEvent &event);
        void OnRevert(wxCommandEvent &event);
        void OnRevisiongraph(wxCommandEvent &event);
        void OnLock(wxCommandEvent &event);
        void OnUnLock(wxCommandEvent &event);
        void OnProperties(wxCommandEvent &event);
        void OnSettings(wxCommandEvent &event);
        void OnCheckForModifications(wxCommandEvent &event);
        void OnUpdate(wxCommandEvent &event);
        void OnFileProjectWorkspaceBased(wxCommandEvent &event);
        void OnBlame(wxCommandEvent &event);
        void OnMakeReadonly(wxCommandEvent &event);
        void OnMakeReadWrite(wxCommandEvent &event);
        void OnExplore(wxCommandEvent &event);
        void OnConfiguration(wxCommandEvent &event);
        void OnAbout(wxCommandEvent &event);
        void MakeReadonly( LPCTSTR lpFileName);
        void MakeReadWrite( LPCTSTR lpFileName);
    private:
        void BuildModuleMenu(const ModuleType type, wxMenu *menu, const FileTreeData* data = 0) {}
        bool BuildToolBar(wxToolBar *toolBar) { return false; }
        void RemoveToolBar(wxToolBar *toolBar) {}
        DECLARE_EVENT_TABLE();
};

#endif // _CBTORTOISESVN_H

