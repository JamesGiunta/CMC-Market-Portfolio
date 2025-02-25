#include "shareTakeoverController.h"

void ShareTakeoverController::addCacheShareTakeoverRow(wxCommandEvent& event) {
    if (!app) {
        return;
    }
    DataRow row;
    std::string ASXCode = takeoverASXCodeInput->GetValue().ToStdString();
    for (std::size_t i = 0; i < ASXCode.length(); i++) {
        ASXCode[i] = toupper(ASXCode[i]);
    }
    row.ASXCode = ASXCode;
    row.price = std::stod(takeoverPriceInput->GetValue().ToStdString());
    std::string date = takeoverDateInput->GetValue().ToStdString();
    row.tradeDate = app->dataProcessing.regexDate(date);
    row.settlementDate = app->dataProcessing.regexDate(date);
    row.fee = 0;
    row.profit = 0;
    row.seq = 0;
    row.cgt = 0;
    row.quantity = 0;
    row.tempFee = 0;
    row.tempQuantity = 0;
    //Add this on generate runtime
    // if (liveSharesMap.find(takeoverASXCodeInput) != liveSharesMap.end()) {
    //     row.quantity = liveSharesMap[takeoverASXCodeInput].quantity;
    //     liveSharesMap.erase(takeoverASXCodeInput);
    // }

    app->dataRetrieval.cacheSpecialCoporateActions(row);
    takeoverASXCodeInput->Clear();
    takeoverPriceInput->Clear();
    takeoverDateInput->Clear();
}

void ShareTakeoverController::setupUI() {
    wxStaticText *shareTakeoverText = new wxStaticText(parent, wxID_ANY, "Share Takeover", wxDefaultPosition, wxDefaultSize);
    wxStaticText *ASXCode = new wxStaticText(parent, wxID_ANY, "What is the share's ASX Code?", wxDefaultPosition, wxDefaultSize);
    takeoverASXCodeInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *takeoverPrice = new wxStaticText(parent, wxID_ANY, "What was the share's takeover price?", wxDefaultPosition, wxDefaultSize);        
    takeoverPriceInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *date = new wxStaticText(parent, wxID_ANY, "When did the share takeover occur (dd/mm/yyyy)?", wxDefaultPosition, wxDefaultSize);
    takeoverDateInput = new wxTextCtrl(parent, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxButton *addButton = new wxButton(parent, wxID_ANY, "Add", wxDefaultPosition, wxDefaultSize);

    shareTakeoverText->SetFont(wxFont(wxFontInfo(12).Bold()));
    shareTakeoverText->SetForegroundColour(wxColour(255, 255, 255));
    ASXCode->SetForegroundColour(wxColour(255, 255, 255));
    takeoverPrice->SetForegroundColour(wxColour(255, 255, 255));
    date->SetForegroundColour(wxColour(255, 255, 255));

    addButton->Bind(wxEVT_BUTTON, &ShareTakeoverController::addCacheShareTakeoverRow, this);

    wxBoxSizer *page4Panel1ContentSizer = new wxBoxSizer(wxVERTICAL);

    page4Panel1ContentSizer->AddSpacer(10);
    page4Panel1ContentSizer->Add(shareTakeoverText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page4Panel1ContentSizer->AddSpacer(10);
    page4Panel1ContentSizer->Add(ASXCode, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page4Panel1ContentSizer->AddSpacer(5);
    page4Panel1ContentSizer->Add(takeoverASXCodeInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page4Panel1ContentSizer->AddSpacer(5);
    page4Panel1ContentSizer->Add(takeoverPrice, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page4Panel1ContentSizer->AddSpacer(5);
    page4Panel1ContentSizer->Add(takeoverPriceInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page4Panel1ContentSizer->AddSpacer(5);
    page4Panel1ContentSizer->Add(date, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    page4Panel1ContentSizer->AddSpacer(5);
    page4Panel1ContentSizer->Add(takeoverDateInput, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 5));
    page4Panel1ContentSizer->AddSpacer(25);
    page4Panel1ContentSizer->Add(addButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));

    parent->SetSizer(page4Panel1ContentSizer);
}

ShareTakeoverController::ShareTakeoverController(wxPanel *parent, App *app) : wxPanel(parent) {
    this->app = app;
    this->parent = parent;
    setupUI();
}