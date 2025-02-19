//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//
// copyright            : (C) 2008 by Eran Ifrah
// file name            : workspace_pane.cpp
//
// -------------------------------------------------------------------------
// A
//              _____           _      _     _ _
//             /  __ \         | |    | |   (_) |
//             | /  \/ ___   __| | ___| |    _| |_ ___
//             | |    / _ \ / _  |/ _ \ |   | | __/ _ )
//             | \__/\ (_) | (_| |  __/ |___| | ||  __/
//              \____/\___/ \__,_|\___\_____/_|\__\___|
//
//                                                  F i l e
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
#include "SideBar.hpp"

#include "clWorkspaceView.h"
#include "cl_config.h"
#include "cl_editor.h"
#include "codelite_events.h"
#include "detachedpanesinfo.h"
#include "dockablepane.h"
#include "dockablepanemenumanager.h"
#include "editor_config.h"
#include "event_notifier.h"
#include "file_logger.h"
#include "fileexplorer.h"
#include "fileview.h"
#include "frame.h"
#include "globals.h"
#include "openwindowspanel.h"
#include "pluginmanager.h"
#include "tabgroupspane.h"
#include "workspacetab.h"

#include <wx/app.h>
#include <wx/bitmap.h>
#include <wx/gauge.h>
#include <wx/menu.h>
#include <wx/sizer.h>
#include <wx/wupdlock.h>
#include <wx/xrc/xmlres.h>

#ifdef __WXGTK20__
// We need this ugly hack to workaround a gtk2-wxGTK name-clash
// See http://trac.wxwidgets.org/ticket/10883
#define GSocket GlibGSocket
#include <gtk/gtk.h>
#undef GSocket
#endif

#define VIEW_NAME "Workspace View"
#define SECONDARY_VIEW_NAME "Secondary Sidebar"

namespace
{
const wxString WORKSPACE_LABEL = _("Workspace");
const wxString EXPLORER_LABEL = _("Explorer");
const wxString TABS_LABEL = _("Tabs");
const wxString GROUPS_LABEL = _("Groups");
} // namespace

SideBar::SideBar(wxWindow* parent, const wxString& caption, wxAuiManager* mgr, long style)
    : m_caption(caption)
    , m_mgr(mgr)
{
    if(!wxPanel::Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, style)) {
        return;
    }
    SetBackgroundColour(clSystemSettings::GetDefaultPanelColour());
    CreateGUIControls();
    EventNotifier::Get()->Bind(wxEVT_INIT_DONE, &SideBar::OnInitDone, this);
    EventNotifier::Get()->Bind(wxEVT_EDITOR_CONFIG_CHANGED, &SideBar::OnSettingsChanged, this);
    EventNotifier::Get()->Bind(wxEVT_SYS_COLOURS_CHANGED, [this](clCommandEvent& e) {
        e.Skip();
        SetBackgroundColour(clSystemSettings::GetDefaultPanelColour());
        Refresh();
    });
}

SideBar::~SideBar()
{
    EventNotifier::Get()->Unbind(wxEVT_INIT_DONE, &SideBar::OnInitDone, this);
    EventNotifier::Get()->Unbind(wxEVT_EDITOR_CONFIG_CHANGED, &SideBar::OnSettingsChanged, this);
}

#define IS_DETACHED(name) (detachedPanes.Index(name) != wxNOT_FOUND) ? true : false

void SideBar::CreateGUIControls()
{
    wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
    SetSizer(mainSizer);

    long style = 0;
    if(EditorConfigST::Get()->GetOptions()->GetWorkspaceTabsDirection() == wxRIGHT) {
        style = wxBK_RIGHT;
    }

    m_book = new clSideBarCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(300, -1), style);
    m_book->Bind(wxEVT_SIDEBAR_CONTEXT_MENU, &SideBar::OnContextMenu, this);

    // Calculate the widest tab (the one with the 'Workspace' label)
    int xx, yy;
    wxFont fnt = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    wxWindow::GetTextExtent(WORKSPACE_LABEL, &xx, &yy, NULL, NULL, &fnt);

    mainSizer->Add(m_book, 1, wxEXPAND | wxALL, 0);

    // Add the parsing progress controls
    m_staticText = new wxStaticText(this, wxID_ANY, _("Parsing workspace..."));
    mainSizer->Add(m_staticText, 0, wxEXPAND | wxALL, 2);

    m_parsingProgress =
        new wxGauge(this, wxID_ANY, 100, wxDefaultPosition, wxSize(-1, 15), wxGA_HORIZONTAL | wxGA_SMOOTH);
    mainSizer->Add(m_parsingProgress, 0, wxEXPAND | wxALL, 1);
    m_parsingProgress->Hide();
    m_staticText->Hide();

    // the IManager instance
    IManager* mgr = PluginManager::Get();

    m_workspaceTab = new WorkspaceTab(m_book, WORKSPACE_LABEL);
    m_book->AddPage(m_workspaceTab, WORKSPACE_LABEL, clLoadSidebarBitmap("workspace-button", m_book), true);

    m_tabs.insert(std::make_pair(WORKSPACE_LABEL, Tab(WORKSPACE_LABEL, m_workspaceTab)));
    mgr->AddWorkspaceTab(WORKSPACE_LABEL);

    // Add the explorer tab
    m_explorer = new FileExplorer(m_book, EXPLORER_LABEL);
    m_book->AddPage(m_explorer, EXPLORER_LABEL, clLoadSidebarBitmap("file-explorer-button", m_book), false);

    m_tabs.insert(std::make_pair(EXPLORER_LABEL, Tab(EXPLORER_LABEL, m_explorer)));
    mgr->AddWorkspaceTab(EXPLORER_LABEL);

    // Add the "File Explorer" view to the list of files managed by the workspace-view
    m_workspaceTab->GetView()->AddPage(m_explorer, EXPLORER_LABEL, false);

    // Add the Open Windows Panel (Tabs)
    // #ifndef __WXOSX__
    m_openWindowsPane = new OpenWindowsPanel(m_book, TABS_LABEL);
    m_book->AddPage(m_openWindowsPane, TABS_LABEL, clLoadSidebarBitmap("tabs-button", m_book));

    m_tabs.insert(std::make_pair(TABS_LABEL, Tab(TABS_LABEL, m_openWindowsPane)));
    mgr->AddWorkspaceTab(TABS_LABEL);
    // #endif

    // Add the Tabgroups tab
    m_TabgroupsPane = new TabgroupsPane(m_book, GROUPS_LABEL);
    m_book->AddPage(m_TabgroupsPane, GROUPS_LABEL, clLoadSidebarBitmap("groups-button", m_book));

    m_tabs.insert(std::make_pair(GROUPS_LABEL, Tab(GROUPS_LABEL, m_TabgroupsPane)));
    mgr->AddWorkspaceTab(GROUPS_LABEL);

    if(m_book->GetPageCount() > 0) {
        m_book->SetSelection((size_t)0);
    }

    m_mgr->Update();
}

void SideBar::ClearProgress()
{
    m_parsingProgress->SetValue(0);
    m_parsingProgress->Hide();

    m_staticText->SetLabel(_("Parsing workspace..."));
    m_staticText->Hide();
    Layout();
}

void SideBar::UpdateProgress(int val)
{
    if(m_parsingProgress->IsShown() == false) {
        m_parsingProgress->Show();
        m_staticText->Show();
        Layout();
    }

    m_staticText->SetLabel(wxString::Format(_("Parsing workspace: %d%% completed"), val));
    m_parsingProgress->SetValue(val);
    m_parsingProgress->Update();
}

void SideBar::ApplySavedTabOrder(bool update_ui) const
{
    wxWindowUpdateLocker locker{ m_book };
    wxArrayString tabs;
    int index = -1;
    if(!clConfig::Get().GetWorkspaceTabOrder(tabs, index))
        return;

    for(size_t i = 0; i < tabs.size(); ++i) {
        m_book->MovePageToIndex(tabs[i], i);
    }

    if(update_ui) {
        m_mgr->Update();
    }
}

void SideBar::SaveWorkspaceViewTabOrder() const
{
    wxArrayString panes;
    panes.reserve(m_book->GetPageCount());

    for(size_t i = 0; i < m_book->GetPageCount(); ++i) {
        panes.Add(m_book->GetPageText(i));
    }
    clConfig::Get().SetWorkspaceTabOrder(panes, m_book->GetSelection());
}

wxWindow* SideBar::DoGetControlByName(const wxString& title)
{
    if(title == EXPLORER_LABEL)
        return m_explorer;
    else if(title == WORKSPACE_LABEL)
        return m_workspaceTab;
#ifndef __WXOSX__
    else if(title == TABS_LABEL)
        return m_openWindowsPane;
#endif
    else if(title == GROUPS_LABEL)
        return m_TabgroupsPane;
    return NULL;
}

bool SideBar::IsTabVisible(int flag)
{
    wxWindow* win(NULL);
    wxString title;

    switch(flag) {
    case View_Show_Workspace_Tab:
        title = WORKSPACE_LABEL;
        win = DoGetControlByName(WORKSPACE_LABEL);
        break;
    case View_Show_Explorer_Tab:
        title = EXPLORER_LABEL;
        win = DoGetControlByName(EXPLORER_LABEL);
        break;
#ifndef __WXOSX__
    case View_Show_Tabs_Tab:
        title = TABS_LABEL;
        win = DoGetControlByName(TABS_LABEL);
        break;
#endif
    case View_Show_Tabgroups_Tab:
        title = GROUPS_LABEL;
        win = DoGetControlByName(GROUPS_LABEL);
        break;
    }

    if(!win || title.IsEmpty())
        return false;

    // if the control exists in the notebook, return true
    for(size_t i = 0; i < m_book->GetPageCount(); ++i) {
        if(m_book->GetPageText(i) == title) {
            return true;
        }
    }
    return win && win->IsShown();
}

void SideBar::OnInitDone(wxCommandEvent& event)
{
    event.Skip();
    if(m_book->GetPageCount() == 0) {
        return;
    }

    // Update the bitmaps (bug on Windows where DPI is not detected during the frame startup)
    ::clClearSidebarBitmapCache();

    int where = m_book->GetPageIndex(WORKSPACE_LABEL);
    if(where != wxNOT_FOUND) {
        m_book->SetPageBitmap(where, clLoadSidebarBitmap("workspace-button", m_book));
    }

    where = m_book->GetPageIndex(TABS_LABEL);
    if(where != wxNOT_FOUND) {
        m_book->SetPageBitmap(where, clLoadSidebarBitmap("tabs-button", m_book));
    }

    where = m_book->GetPageIndex(EXPLORER_LABEL);
    if(where != wxNOT_FOUND) {
        m_book->SetPageBitmap(where, clLoadSidebarBitmap("file-explorer-button", m_book));
    }

    where = m_book->GetPageIndex(GROUPS_LABEL);
    if(where != wxNOT_FOUND) {
        m_book->SetPageBitmap(where, clLoadSidebarBitmap("groups-button", m_book));
    }

    // Move tabs to the secondary bar if needed
    MoveToSecondarySideBar();
}

void SideBar::SelectTab(const wxString& tabTitle)
{
    for(size_t i = 0; i < m_book->GetPageCount(); i++) {
        if(m_book->GetPageText(i) == tabTitle) {
            // requested to add a page which already exists
            m_book->SetSelection(i);
        }
    }
}

void SideBar::OnSettingsChanged(wxCommandEvent& event)
{
    event.Skip();

    auto direction = EditorConfigST::Get()->GetOptions()->GetWorkspaceTabsDirection();
    m_book->SetButtonPosition(direction);
}

void SideBar::ShowTab(const wxString& name, bool show)
{
    clCommandEvent show_event(wxEVT_SHOW_WORKSPACE_TAB);
    show_event.SetString(name);
    show_event.SetSelected(show);
    EventNotifier::Get()->ProcessEvent(show_event);
}

void SideBar::OnContextMenu(wxContextMenuEvent& event)
{
    wxMenu menu;
    menu.Append(XRCID("sidebar-detach-tab"), _("Move to secondary sidebar"));

    int pos = event.GetSelection();
    menu.Bind(
        wxEVT_MENU,
        [pos, this](wxCommandEvent& e) {
            wxUnusedVar(e);
            MoveToSecondarySideBar(pos);
        },
        XRCID("sidebar-detach-tab"));
    m_book->PopupMenu(&menu);
}

void SideBar::SetSecondarySideBar(SecondarySideBar* ssb) { m_secondarySideBar = ssb; }

void SideBar::MoveToSecondarySideBar(int pos)
{
    wxString label = m_book->GetPageText(pos);
    wxBitmap bmp = m_book->GetPageBitmap(pos);
    wxWindow* win = m_book->GetPage(pos);

    m_book->RemovePage(pos);
    m_book->GetSizer()->Layout();

    // add it to the right side bar
    m_secondarySideBar->AddPage(win, bmp, label);

    if(m_book->GetPageCount() == 0) {
        // hide the sidebar
        clGetManager()->ShowPane(VIEW_NAME, false);
    }
}

void SideBar::MoveToSecondarySideBar()
{
    auto secondary_tabs = clConfig::Get().Read("secondary_side_bar.tabs", wxArrayString{});
    if(secondary_tabs.empty()) {
        clGetManager()->ShowPane(SECONDARY_VIEW_NAME, false);
        return;
    }

    for(const auto& tab_label : secondary_tabs) {
        int pos = m_book->GetPageIndex(tab_label);
        if(pos == wxNOT_FOUND) {
            continue;
        }
        MoveToSecondarySideBar(pos);
    }
    auto selection = clConfig::Get().Read("secondary_side_bar.selection", 0);
    m_secondarySideBar->SetSelection(selection);
}

void SideBar::AddPage(wxWindow* win, wxBitmap bmp, const wxString& label, bool selected)
{
    m_book->AddPage(win, label, bmp, selected);
    m_book->GetSizer()->Layout();
    clGetManager()->ShowPane(VIEW_NAME, true);
}
