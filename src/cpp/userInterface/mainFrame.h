#pragma once
#include <wx/wx.h>
#include <wx/simplebook.h>
#include "app.h"
#include "shareSplitController.h"
#include "shareNameChangeController.h"
#include "shareTakeoverController.h"
#include "generateReportController.h"

class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
    private:
        App *app;
        GenerateReportController *generateReportController;
        ShareSplitController *shareSplitController;
        ShareNameChangeController *shareNameChangeController;
        ShareTakeoverController *shareTakeoverController;

        wxPanel *panel1;
        wxPanel *panel2;
        
        wxSimplebook *book;
        wxPanel *page1;
        wxPanel *page2;
        wxPanel *page3;
        wxPanel *page4;

        std::shared_ptr<std::filesystem::path> filePath;
        wxTextCtrl *reportNameText;

        void createPanels();
        void setupPanel1();
        void setupPanel2();
        void onFileSaveLocationButton(wxCommandEvent& event);
        void onClearCacheButton(wxCommandEvent& event);
        void onShareSplitButton(wxCommandEvent& event);
        void onShareNameChangeButton(wxCommandEvent& event);
        void onShareTakeoverButton(wxCommandEvent& event);
        void onGenerateReportButton(wxCommandEvent& event);
};