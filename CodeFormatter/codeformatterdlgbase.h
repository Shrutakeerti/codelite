//////////////////////////////////////////////////////////////////////
// This file was auto-generated by codelite's wxCrafter Plugin
// wxCrafter project file: codeformatterdlg.wxcp
// Do not modify this file by hand!
//////////////////////////////////////////////////////////////////////

#ifndef _CODELITE_CODEFORMATTER_CODEFORMATTERDLG_BASE_CLASSES_H
#define _CODELITE_CODEFORMATTER_CODEFORMATTERDLG_BASE_CLASSES_H

// clang-format off
#include <wx/settings.h>
#include <wx/xrc/xmlres.h>
#include <wx/xrc/xh_bmp.h>
#include <wx/dialog.h>
#include <wx/iconbndl.h>
#include <wx/artprov.h>
#include <wx/sizer.h>
#include <wx/notebook.h>
#include <wx/panel.h>
#include <wx/imaglist.h>
#include <wx/checkbox.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/arrstr.h>
#include <wx/splitter.h>
#include <wx/propgrid/manager.h>
#include <wx/propgrid/property.h>
#include <wx/propgrid/advprops.h>
#include <wx/button.h>
#include <wx/stc/stc.h>
#include <wx/textctrl.h>
#include <wx/filepicker.h>
#if wxVERSION_NUMBER >= 2900
#include <wx/persist.h>
#include <wx/persist/toplevel.h>
#include <wx/persist/bookctrl.h>
#include <wx/persist/treebook.h>
#endif

#ifdef WXC_FROM_DIP
#undef WXC_FROM_DIP
#endif
#if wxVERSION_NUMBER >= 3100
#define WXC_FROM_DIP(x) wxWindow::FromDIP(x, NULL)
#else
#define WXC_FROM_DIP(x) x
#endif

#include "formatoptions.h"
#include "PHPFormatterBuffer.h"
// clang-format on

class CodeFormatterBaseDlg : public wxDialog
{
protected:
    wxNotebook* m_notebook;
    wxPanel* m_panelGeneral;
    wxCheckBox* m_checkBoxFormatOnSave;
    wxStaticText* m_staticText115;
    wxChoice* m_choiceCxxEngine;
    wxStaticText* m_staticText198;
    wxChoice* m_choicePhpFormatter;
    wxPanel* m_panelCxx;
    wxNotebook* m_notebookCxx;
    wxPanel* m_panelClangFormat;
    wxSplitterWindow* m_splitter165;
    wxPanel* m_splitterPage169;
    wxPropertyGridManager* m_pgMgrClang;
    wxPGProperty* m_pgPropClangFormat;
    wxPGProperty* m_pgPropClangFormatExePath;
    wxPGProperty* m_pgPropColumnLimit;
    wxPGProperty* m_pgPropClangBraceBreakStyle;
    wxPGProperty* m_pgPropClangBraceWrapAfterCaseLabel;
    wxPGProperty* m_pgPropClangBraceWrapAfterClass;
    wxPGProperty* m_pgPropClangBraceWrapAfterControlStatement;
    wxPGProperty* m_pgPropClangBraceWrapAfterEnum;
    wxPGProperty* m_pgPropClangBraceWrapAfterFunction;
    wxPGProperty* m_pgPropClangBraceWrapAfterObjCDeclaration;
    wxPGProperty* m_pgPropClangBraceWrapAfterStruct;
    wxPGProperty* m_pgPropClangBraceWrapAfterUnion;
    wxPGProperty* m_pgPropClangBraceWrapAfterExternBlock;
    wxPGProperty* m_pgPropClangBraceWrapBeforeCatch;
    wxPGProperty* m_pgPropClangBraceWrapBeforeElse;
    wxPGProperty* m_pgPropClangBraceWrapBeforeLambdaBody;
    wxPGProperty* m_pgPropClangBraceWrapBeforeWhile;
    wxPGProperty* m_pgPropClangBraceWrapIndentBraces;
    wxPGProperty* m_pgPropClangBraceWrapSplitEmptyFunction;
    wxPGProperty* m_pgPropClangBraceWrapSplitEmptyRecord;
    wxPGProperty* m_pgPropClangBraceWrapSplitEmptyNamespace;
    wxPGProperty* m_pgPropClangFormatStyle;
    wxPGProperty* m_pgPropClangUseFile;
    wxPGProperty* m_pgPropClangFormattingOptions;
    wxButton* m_buttonExportClangFormatFile;
    wxPanel* m_splitterPage173;
    wxStyledTextCtrl* m_textCtrlPreview_Clang;
    wxPanel* m_panelAstyle;
    wxSplitterWindow* m_splitter145;
    wxPanel* m_splitterPage149;
    wxPropertyGridManager* m_pgMgrAstyle;
    wxPGProperty* m_pgPropAstyleOptions;
    wxPGProperty* m_pgPropPreDefinedStyles;
    wxPGProperty* m_pgPropBrackets;
    wxPGProperty* m_pgPropIndentation;
    wxPGProperty* m_pgPropFormatting;
    wxStaticText* m_staticText59;
    wxStaticText* m_staticText3;
    wxTextCtrl* m_textCtrlUserFlags;
    wxPanel* m_splitterPage153;
    wxStyledTextCtrl* m_textCtrlPreview;
    wxPanel* m_panelPhp;
    wxNotebook* m_notebookPhp;
    wxPanel* m_panelBuiltIn;
    wxSplitterWindow* m_splitter119;
    wxPanel* m_splitterPage123;
    wxPropertyGridManager* m_pgMgrPhp;
    wxPGProperty* m_pgPropPhpFormatter;
    wxPGProperty* m_pgPropPhpFormatterOptions;
    wxPanel* m_splitterPage127;
    wxStyledTextCtrl* m_stcPhpPreview;
    wxPanel* m_panelPhpCSFixer;
    wxSplitterWindow* m_splitter165318;
    wxPanel* m_splitterPage169419;
    wxPropertyGridManager* m_pgMgrPHPCsFixer;
    wxPGProperty* m_pgPropPhpCSFixer;
    wxPGProperty* m_filePickerPHPCsFixerPhar;
    wxPGProperty* m_pgPropPHPCsFixerOptions;
    wxPGProperty* m_pgPropPHPCsFixerUseFile;
    wxPGProperty* m_pgPropPHPCsFixerStandard;
    wxPGProperty* m_pgPropPHPCsFixerMigration;
    wxPGProperty* m_pgPropPHPCsFixerDoubleArrows;
    wxPGProperty* m_pgPropPHPCsFixerEquals;
    wxPGProperty* m_pgPropPHPCsFixerArrays;
    wxPGProperty* m_pgPropPHPCsFixerEmptyReturn;
    wxPGProperty* m_pgPropPHPCsFixerConcatSpace;
    wxPGProperty* m_pgPropPHPCsFixerRules;
    wxPanel* m_splitterPage1731328;
    wxStyledTextCtrl* m_textCtrlPreview_PhpCSFixer;
    wxPanel* m_panelPhpcbf;
    wxSplitterWindow* m_splitter1653;
    wxPanel* m_splitterPage1694;
    wxPropertyGridManager* m_pgMgrPhpcbf;
    wxPGProperty* m_pgPropPhpcbf;
    wxPGProperty* m_filePickerPhpcbfPhar;
    wxPGProperty* m_pgPropPhpcbfSeverity;
    wxPGProperty* m_pgPropPhpcbfEncoding;
    wxPGProperty* m_pgPropPhpcbfUseFile;
    wxPGProperty* m_pgPropPhpcbfStandard;
    wxPGProperty* m_pgPropPhpcbfOptions;
    wxPanel* m_splitterPage17313;
    wxStyledTextCtrl* m_textCtrlPreview_Phpcbf;
    wxPanel* m_panelRust;
    wxStaticText* m_staticText297;
    wxFilePickerCtrl* m_rustCommand;
    wxStaticText* m_staticText301;
    wxTextCtrl* m_textCtrlRustConfigPath;
    wxStyledTextCtrl* m_stcRustConfig;
    wxStdDialogButtonSizer* m_stdBtnSizer30;
    wxButton* m_buttonOK;
    wxButton* m_buttonApply;
    wxButton* m_buttonCancel;
    wxButton* m_buttonHelp;

protected:
    virtual void UpdatePreviewUI(wxNotebookEvent& event) { event.Skip(); }
    virtual void OnFormatOnSave(wxCommandEvent& event) { event.Skip(); }
    virtual void OnChoicecxxengineChoiceSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnChoicephpformatterChoiceSelected(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPgmgrclangPgChanged(wxPropertyGridEvent& event) { event.Skip(); }
    virtual void OnExportClangFormatFile(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPgmgrastylePgChanged(wxPropertyGridEvent& event) { event.Skip(); }
    virtual void OnCustomAstyleFlags(wxCommandEvent& event) { event.Skip(); }
    virtual void OnPgmgrphpPgChanged(wxPropertyGridEvent& event) { event.Skip(); }
    virtual void OnPgmgrPHPCsFixerPgChanged(wxPropertyGridEvent& event) { event.Skip(); }
    virtual void OnPgmgrPhpcbfPgChanged(wxPropertyGridEvent& event) { event.Skip(); }
    virtual void OnOK(wxCommandEvent& event) { event.Skip(); }
    virtual void OnApplyUI(wxUpdateUIEvent& event) { event.Skip(); }
    virtual void OnApply(wxCommandEvent& event) { event.Skip(); }
    virtual void OnHelp(wxCommandEvent& event) { event.Skip(); }

public:
    wxCheckBox* GetCheckBoxFormatOnSave() { return m_checkBoxFormatOnSave; }
    wxStaticText* GetStaticText115() { return m_staticText115; }
    wxChoice* GetChoiceCxxEngine() { return m_choiceCxxEngine; }
    wxStaticText* GetStaticText198() { return m_staticText198; }
    wxChoice* GetChoicePhpFormatter() { return m_choicePhpFormatter; }
    wxPanel* GetPanelGeneral() { return m_panelGeneral; }
    wxPropertyGridManager* GetPgMgrClang() { return m_pgMgrClang; }
    wxButton* GetButtonExportClangFormatFile() { return m_buttonExportClangFormatFile; }
    wxPanel* GetSplitterPage169() { return m_splitterPage169; }
    wxStyledTextCtrl* GetTextCtrlPreview_Clang() { return m_textCtrlPreview_Clang; }
    wxPanel* GetSplitterPage173() { return m_splitterPage173; }
    wxSplitterWindow* GetSplitter165() { return m_splitter165; }
    wxPanel* GetPanelClangFormat() { return m_panelClangFormat; }
    wxPropertyGridManager* GetPgMgrAstyle() { return m_pgMgrAstyle; }
    wxStaticText* GetStaticText59() { return m_staticText59; }
    wxStaticText* GetStaticText3() { return m_staticText3; }
    wxTextCtrl* GetTextCtrlUserFlags() { return m_textCtrlUserFlags; }
    wxPanel* GetSplitterPage149() { return m_splitterPage149; }
    wxStyledTextCtrl* GetTextCtrlPreview() { return m_textCtrlPreview; }
    wxPanel* GetSplitterPage153() { return m_splitterPage153; }
    wxSplitterWindow* GetSplitter145() { return m_splitter145; }
    wxPanel* GetPanelAstyle() { return m_panelAstyle; }
    wxNotebook* GetNotebookCxx() { return m_notebookCxx; }
    wxPanel* GetPanelCxx() { return m_panelCxx; }
    wxPropertyGridManager* GetPgMgrPhp() { return m_pgMgrPhp; }
    wxPanel* GetSplitterPage123() { return m_splitterPage123; }
    wxStyledTextCtrl* GetStcPhpPreview() { return m_stcPhpPreview; }
    wxPanel* GetSplitterPage127() { return m_splitterPage127; }
    wxSplitterWindow* GetSplitter119() { return m_splitter119; }
    wxPanel* GetPanelBuiltIn() { return m_panelBuiltIn; }
    wxPropertyGridManager* GetPgMgrPHPCsFixer() { return m_pgMgrPHPCsFixer; }
    wxPanel* GetSplitterPage169419() { return m_splitterPage169419; }
    wxStyledTextCtrl* GetTextCtrlPreview_PhpCSFixer() { return m_textCtrlPreview_PhpCSFixer; }
    wxPanel* GetSplitterPage1731328() { return m_splitterPage1731328; }
    wxSplitterWindow* GetSplitter165318() { return m_splitter165318; }
    wxPanel* GetPanelPhpCSFixer() { return m_panelPhpCSFixer; }
    wxPropertyGridManager* GetPgMgrPhpcbf() { return m_pgMgrPhpcbf; }
    wxPanel* GetSplitterPage1694() { return m_splitterPage1694; }
    wxStyledTextCtrl* GetTextCtrlPreview_Phpcbf() { return m_textCtrlPreview_Phpcbf; }
    wxPanel* GetSplitterPage17313() { return m_splitterPage17313; }
    wxSplitterWindow* GetSplitter1653() { return m_splitter1653; }
    wxPanel* GetPanelPhpcbf() { return m_panelPhpcbf; }
    wxNotebook* GetNotebookPhp() { return m_notebookPhp; }
    wxPanel* GetPanelPhp() { return m_panelPhp; }
    wxStaticText* GetStaticText297() { return m_staticText297; }
    wxFilePickerCtrl* GetRustCommand() { return m_rustCommand; }
    wxStaticText* GetStaticText301() { return m_staticText301; }
    wxTextCtrl* GetTextCtrlRustConfigPath() { return m_textCtrlRustConfigPath; }
    wxStyledTextCtrl* GetStcRustConfig() { return m_stcRustConfig; }
    wxPanel* GetPanelRust() { return m_panelRust; }
    wxNotebook* GetNotebook() { return m_notebook; }
    CodeFormatterBaseDlg(wxWindow* parent, wxWindowID id = wxID_ANY,
                         const wxString& title = _("Source Code Formatter Options"),
                         const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(-1, -1),
                         long style = wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER);
    virtual ~CodeFormatterBaseDlg();
};

#endif
