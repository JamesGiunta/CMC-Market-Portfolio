#pragma once
#include <wx/wx.h>
#include "app.h"

class GenerateReportController {
    public:
    GenerateReportController(wxPanel *parent, App *app, wxTextCtrl *reportNameText, std::shared_ptr<std::filesystem::path> filePath);
    private:
        App *app;
        wxPanel *parent;
        wxTextCtrl *reportNameText;
        std::shared_ptr<std::filesystem::path> filePath;
        wxPanel *page1Panel1;
        wxPanel *page1Panel2;
        wxListBox *confirmationsList;
        std::vector<wxString> confirmationPaths;
        wxCheckBox *cacheCheckBox;
        void setupUI();
        void selectConfirmation(wxCommandEvent &event);
        void onListBoxDoubleClick(wxCommandEvent& event);
        void generateReport(wxCommandEvent &event);
};