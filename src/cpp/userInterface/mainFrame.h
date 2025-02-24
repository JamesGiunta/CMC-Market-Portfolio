#pragma once
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <filesystem>
#include "../services/dataRetrieval.h"
#include "../services/dataProcessing.h"

class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
    private:
        DataRetrieval dataRetrieval;
        DataProcessing dataProcessing;
        wxPanel *panel1;
        wxPanel *panel2;
        wxPanel *page1Panel1;
        wxPanel *page1Panel2;
        wxPanel *page2Panel1; 
        wxSimplebook *book;
        wxPanel *page1;
        wxPanel *page2;
        wxPanel *page3;
        wxPanel *page4;
        std::filesystem::path filePath;
        wxTextCtrl *splitASXCodeInput;
        wxTextCtrl *splitRatioInput;
        wxTextCtrl *splitDateInput;
        wxTextCtrl *oldASXCodeInput;
        wxTextCtrl *newASXCodeInput;
        wxTextCtrl *nameChangeDateInput;
        wxTextCtrl *takeoverASXCodeInput;
        wxTextCtrl *takeoverPriceInput;
        wxTextCtrl *takeoverDateInput;

        void createPanels();
        void setupPanel1();
        void setupPanel2();
        void setupPage1();
        void setupPage2();
        void setupPage3();
        void setupPage4();
        void onFileSaveLocationButton(wxCommandEvent& event);
        void onClearCacheButton(wxCommandEvent& event);
        void onShareSplitButton(wxCommandEvent& event);
        void onShareNameChangeButton(wxCommandEvent& event);
        void onShareTakeoverButton(wxCommandEvent& event);
        void onGenerateReportButton(wxCommandEvent& event);
        void addCacheShareSplitRow(wxCommandEvent& event);
        void addCacheShareNameChangeRow(wxCommandEvent& event);
        void addCacheShareTakeoverRow(wxCommandEvent& event);
};