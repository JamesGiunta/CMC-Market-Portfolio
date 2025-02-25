#include "shareSplitController.h"

void ShareSplitController::addCacheShareSplitRow(wxCommandEvent& event) {
    if (!app) {
        return;
    }
    ShareSplitRow row;
    row.ASXCode = splitASXCodeInput->GetValue().ToStdString();
    row.ratio = std::stod(splitRatioInput->GetValue().ToStdString());
    std::string date = splitDateInput->GetValue().ToStdString();
    row.date = app->dataProcessing.regexDate(date);

    app->dataRetrieval.cacheShareConsolidation(row);
    splitASXCodeInput->Clear();
    splitRatioInput->Clear();
    splitDateInput->Clear();
}


void ShareSplitController::setupUI() {
    wxStaticText *shareSplitsText = new wxStaticText(parent, wxID_ANY, "Share Split", wxDefaultPosition, wxDefaultSize);
    wxStaticText *ASXCode = new wxStaticText(parent, wxID_ANY, "What is the shares ASX Code?", wxDefaultPosition, wxDefaultSize);
    splitASXCodeInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *ratio = new wxStaticText(parent, wxID_ANY, "Share Split Ratio (1:10) converts 1 share to 10 (1:x)?", wxDefaultPosition, wxDefaultSize);       
    splitRatioInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *date = new wxStaticText(parent, wxID_ANY, "When did the share split occur (dd/mm/yyyy)?", wxDefaultPosition, wxDefaultSize);
    splitDateInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxButton *addButton = new wxButton(parent, wxID_ANY, "Add", wxDefaultPosition, wxDefaultSize);

    shareSplitsText->SetFont(wxFont(wxFontInfo(12).Bold()));
    shareSplitsText->SetForegroundColour(wxColour(255, 255, 255));
    ASXCode->SetForegroundColour(wxColour(255, 255, 255));
    ratio->SetForegroundColour(wxColour(255, 255, 255));
    date->SetForegroundColour(wxColour(255, 255, 255));

    addButton->Bind(wxEVT_BUTTON, &ShareSplitController::addCacheShareSplitRow, this);

    wxBoxSizer *page2Panel1ContentSizer = new wxBoxSizer(wxVERTICAL);

    page2Panel1ContentSizer->AddSpacer(10);
    page2Panel1ContentSizer->Add(shareSplitsText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page2Panel1ContentSizer->AddSpacer(10);
    page2Panel1ContentSizer->Add(ASXCode, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page2Panel1ContentSizer->AddSpacer(5);
    page2Panel1ContentSizer->Add(splitASXCodeInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page2Panel1ContentSizer->AddSpacer(5);
    page2Panel1ContentSizer->Add(ratio, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page2Panel1ContentSizer->AddSpacer(5);
    page2Panel1ContentSizer->Add(splitRatioInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page2Panel1ContentSizer->AddSpacer(5);
    page2Panel1ContentSizer->Add(date, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page2Panel1ContentSizer->AddSpacer(5);
    page2Panel1ContentSizer->Add(splitDateInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page2Panel1ContentSizer->AddSpacer(25);
    page2Panel1ContentSizer->Add(addButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));

    parent->SetSizer(page2Panel1ContentSizer);
}

ShareSplitController::ShareSplitController(wxPanel *parent, App *app): wxPanel(parent, wxID_ANY) {
    this->app = app;
    this->parent = parent;
    setupUI();
}