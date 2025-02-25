#pragma once
#include <wx/wx.h>
#include "app.h"

class GenerateReportController : public wxPanel {
    public:
    GenerateReportController(wxPanel *parent, App *app);
    private:
        App *app;
        wxPanel *parent;
        wxPanel *page1Panel1;
        wxPanel *page1Panel2;
        wxListBox *confirmationsList;
        std::vector<wxString> confirmationPaths;
        void setupUI();
        void selectConfirmation(wxCommandEvent &event);
};