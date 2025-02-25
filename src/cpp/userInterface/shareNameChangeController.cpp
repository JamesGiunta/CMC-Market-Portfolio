#include "shareNameChangeController.h"

void ShareNameChangeController::addCacheShareNameChangeRow(wxCommandEvent& event) {
    if (!app) {
        return;
    }
    NameChangeRow row;
    std::string oldASXCode = oldASXCodeInput->GetValue().ToStdString();
    for (std::size_t i = 0; i < oldASXCode.length(); i++) {
        oldASXCode[i] = toupper(oldASXCode[i]);
    }
    row.ASXCode = oldASXCode;
    std::string newASXCode = newASXCodeInput->GetValue().ToStdString();
    for (std::size_t i = 0; i < newASXCode.length(); i++) {
        newASXCode[i] = toupper(newASXCode[i]);
    }
    row.newASXCode = newASXCode;
    std::string date = nameChangeDateInput->GetValue().ToStdString();
    row.date = app->dataProcessing.regexDate(date);

    app->dataRetrieval.cacheShareNameChange(row);
    oldASXCodeInput->Clear();
    newASXCodeInput->Clear();
    nameChangeDateInput->Clear();
}

void ShareNameChangeController::setupUI() {
    wxStaticText *shareNameChangeText = new wxStaticText(parent, wxID_ANY, "Share Name Change", wxDefaultPosition, wxDefaultSize);
    wxStaticText *oldASXCode = new wxStaticText(parent, wxID_ANY, "What is the share's old ASX Code?", wxDefaultPosition, wxDefaultSize);
    oldASXCodeInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *newASXCode = new wxStaticText(parent, wxID_ANY, "What is the share's new ASX Code?", wxDefaultPosition, wxDefaultSize);        
    newASXCodeInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *date = new wxStaticText(parent, wxID_ANY, "When did the share name change occur (dd/mm/yyyy)?", wxDefaultPosition, wxDefaultSize);
    nameChangeDateInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxButton *addButton = new wxButton(parent, wxID_ANY, "Add", wxDefaultPosition, wxDefaultSize);

    shareNameChangeText->SetFont(wxFont(wxFontInfo(12).Bold()));
    shareNameChangeText->SetForegroundColour(wxColour(255, 255, 255));
    oldASXCode->SetForegroundColour(wxColour(255, 255, 255));
    newASXCode->SetForegroundColour(wxColour(255, 255, 255));
    date->SetForegroundColour(wxColour(255, 255, 255));

    addButton->Bind(wxEVT_BUTTON, &ShareNameChangeController::addCacheShareNameChangeRow, this);

    wxBoxSizer *page3Panel1ContentSizer = new wxBoxSizer(wxVERTICAL);

    page3Panel1ContentSizer->AddSpacer(10);
    page3Panel1ContentSizer->Add(shareNameChangeText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page3Panel1ContentSizer->AddSpacer(10);
    page3Panel1ContentSizer->Add(oldASXCode, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page3Panel1ContentSizer->AddSpacer(5);
    page3Panel1ContentSizer->Add(oldASXCodeInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page3Panel1ContentSizer->AddSpacer(5);
    page3Panel1ContentSizer->Add(newASXCode, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page3Panel1ContentSizer->AddSpacer(5);
    page3Panel1ContentSizer->Add(newASXCodeInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page3Panel1ContentSizer->AddSpacer(5);
    page3Panel1ContentSizer->Add(date, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page3Panel1ContentSizer->AddSpacer(5);
    page3Panel1ContentSizer->Add(nameChangeDateInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page3Panel1ContentSizer->AddSpacer(25);
    page3Panel1ContentSizer->Add(addButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));

    parent->SetSizer(page3Panel1ContentSizer);
}

ShareNameChangeController::ShareNameChangeController(wxPanel *parent, App *app) : wxPanel(parent) {
    this->app = app;
    this->parent = parent;
    setupUI();
}