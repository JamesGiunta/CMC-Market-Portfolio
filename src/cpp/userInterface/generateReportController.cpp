#include "generateReportController.h"

void GenerateReportController::setupUI() {
    page1Panel1 = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    page1Panel2 = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    page1Panel1->SetBackgroundColour(wxColor(100, 100, 100));

    wxBoxSizer *page1Sizer = new wxBoxSizer(wxVERTICAL);

    page1Sizer->Add(page1Panel1, 14, wxEXPAND | wxALL, 15);
    page1Sizer->Add(page1Panel2, 8, wxEXPAND | wxALL, 15);

    parent->SetSizer(page1Sizer);
    
    wxStaticText *confrimationsText = new wxStaticText(page1Panel1, wxID_ANY, "Select Confirmations", wxDefaultPosition, wxDefaultSize);
    wxButton *confirmButton = new wxButton(page1Panel1, wxID_ANY, "Add Confirmation", wxDefaultPosition, wxDefaultSize);

    confrimationsText->SetFont(wxFont(wxFontInfo(12).Bold()));

    wxCheckBox *checkBox = new wxCheckBox(page1Panel2, wxID_ANY, "Use Cache", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
    wxButton *generateReportButton = new wxButton(page1Panel2, wxID_ANY, "Generate Report", wxDefaultPosition, wxDefaultSize);

    checkBox->SetValue(true);
    checkBox->SetForegroundColour(wxColour(255, 255, 255));

    wxBoxSizer *panel4ContentSizer = new wxBoxSizer(wxVERTICAL);

    panel4ContentSizer->Add(confrimationsText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel4ContentSizer->AddSpacer(10);
    panel4ContentSizer->Add(confirmButton, wxSizerFlags().Proportion(0).Border(wxALL, 10));

    page1Panel1->SetSizer(panel4ContentSizer);

    wxBoxSizer *panel5ContentSizer = new wxBoxSizer(wxVERTICAL);

    panel5ContentSizer->Add(checkBox, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel5ContentSizer->AddStretchSpacer(1);
    panel5ContentSizer->Add(generateReportButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 30));

    page1Panel2->SetSizer(panel5ContentSizer);
}

GenerateReportController::GenerateReportController(wxPanel *parent, App *app) : wxPanel(parent) {
    this->app = app;
    this->parent = parent;
    setupUI();
}