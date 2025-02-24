#include "mainFrame.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <filesystem>

void MainFrame::onFileSaveLocationButton(wxCommandEvent& event) {
    wxDirDialog dialog(this, "Choose a directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dialog.ShowModal() == wxID_OK) {
        filePath = std::filesystem::path(dialog.GetPath().ToStdString());
    }
}

void MainFrame::onClearCacheButton(wxCommandEvent& event) {
    if (!app) {
        return;
    }
    app->dataRetrieval.clearCache();
}

void  MainFrame::onGenerateReportButton(wxCommandEvent& event) {
    book->SetSelection(0);
}

void MainFrame::onShareSplitButton(wxCommandEvent& event) {
    book->SetSelection(1);
}

void MainFrame::onShareNameChangeButton(wxCommandEvent& event) {
    book->SetSelection(2);
}

void MainFrame::onShareTakeoverButton(wxCommandEvent& event) {
    book->SetSelection(3);
}

void MainFrame::addCacheShareSplitRow(wxCommandEvent& event) {
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

void MainFrame::addCacheShareNameChangeRow(wxCommandEvent& event) {
    if (!app) {
        return;
    }
    NameChangeRow row;
    row.ASXCode = oldASXCodeInput->GetValue().ToStdString();
    row.newASXCode = newASXCodeInput->GetValue().ToStdString();
    std::string date = nameChangeDateInput->GetValue().ToStdString();
    row.date = app->dataProcessing.regexDate(date);

    app->dataRetrieval.cacheShareNameChange(row);
    oldASXCodeInput->Clear();
    newASXCodeInput->Clear();
    nameChangeDateInput->Clear();
}

void MainFrame::addCacheShareTakeoverRow(wxCommandEvent& event) {
    if (!app) {
        return;
    }
    DataRow row;
    row.ASXCode = takeoverASXCodeInput->GetValue().ToStdString();
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

void MainFrame::createPanels() {
    panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    
    book = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    page1 = new wxPanel(book, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    page2 = new wxPanel(book, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    page3 = new wxPanel(book, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    page4 = new wxPanel(book, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    book->AddPage(page1, "Page 1");
    book->AddPage(page2, "Page 2");
    book->AddPage(page3, "Page 3");
    book->AddPage(page4, "Page 4");

    panel1->SetBackgroundColour(wxColor(40, 40, 40));
    book->SetBackgroundColour(wxColor(40, 40, 40));
    panel2->SetBackgroundColour(wxColor(40, 40, 40));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(panel1, wxSizerFlags().Proportion(6).Expand().Border(wxALL, 1));
    sizer->Add(book, wxSizerFlags().Proportion(13).Expand().Border(wxTOP | wxBOTTOM | wxLEFT, 20));
    sizer->Add(panel2, wxSizerFlags().Proportion(5).Expand().Border(wxTOP | wxRIGHT | wxBOTTOM, 20));

    this->SetSizer(sizer);
}

void MainFrame::setupPanel1() {
    wxStaticText *applicationNameText = new wxStaticText(panel1, wxID_ANY, "CMC-Market-Report", wxDefaultPosition, wxDefaultSize);
    wxButton *generateButton = new wxButton(panel1, wxID_ANY, "Generate Report", wxDefaultPosition, wxDefaultSize);
    wxButton *shareSplitButton = new wxButton(panel1, wxID_ANY, "Input Share Splits", wxDefaultPosition, wxDefaultSize);
    wxButton *shareNameChangeButton = new wxButton(panel1, wxID_ANY, "Input Name Changes", wxDefaultPosition, wxDefaultSize);
    wxButton *shareTakeoverButton = new wxButton(panel1, wxID_ANY, "Input Share Takeovers", wxDefaultPosition, wxDefaultSize);

    generateButton->Bind(wxEVT_BUTTON, &MainFrame::onGenerateReportButton, this);
    shareSplitButton->Bind(wxEVT_BUTTON, &MainFrame::onShareSplitButton, this);
    shareNameChangeButton->Bind(wxEVT_BUTTON, &MainFrame::onShareNameChangeButton, this);
    shareTakeoverButton->Bind(wxEVT_BUTTON, &MainFrame::onShareTakeoverButton, this);

    applicationNameText->SetFont(wxFont(wxFontInfo(12).Bold()));
    applicationNameText->SetForegroundColour(wxColour(255, 255, 255));

    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    panelSizer->AddSpacer(30);
    panelSizer->Add(applicationNameText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
    panelSizer->AddSpacer(30);
    panelSizer->Add(generateButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
    panelSizer->AddSpacer(10);
    panelSizer->Add(shareSplitButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
    panelSizer->AddSpacer(10);
    panelSizer->Add(shareNameChangeButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
    panelSizer->AddSpacer(10);
    panelSizer->Add(shareTakeoverButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));

    panel1->SetSizer(panelSizer);
}

void MainFrame::setupPanel2() {
    wxStaticText *fileSaveLocation = new wxStaticText(panel2, wxID_ANY, "File Save Location", wxDefaultPosition, wxDefaultSize);
    wxButton *browseButton = new wxButton(panel2, wxID_ANY, "Browse", wxDefaultPosition, wxDefaultSize);
    wxButton *clearCacheButton = new wxButton(panel2, wxID_ANY, "Clear Cache", wxDefaultPosition, wxDefaultSize);
    wxStaticText *reportNameTextStatic = new wxStaticText(panel2, wxID_ANY, "Generated File Name:", wxDefaultPosition, wxDefaultSize);
    wxTextCtrl *reportNameText = new wxTextCtrl(panel2, wxID_ANY, "Report", wxDefaultPosition, wxDefaultSize);

    fileSaveLocation->SetFont(wxFont(wxFontInfo(12).Bold()));
    fileSaveLocation->SetForegroundColour(wxColour(255, 255, 255));
    reportNameTextStatic->SetForegroundColour(wxColour(255, 255, 255));

    browseButton->Bind(wxEVT_BUTTON, &MainFrame::onFileSaveLocationButton, this);
    clearCacheButton->Bind(wxEVT_BUTTON, &MainFrame::onClearCacheButton, this);

    wxBoxSizer *panel3ContentSizer = new wxBoxSizer(wxVERTICAL);

    panel3ContentSizer->AddSpacer(10);
    panel3ContentSizer->Add(fileSaveLocation, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel3ContentSizer->AddSpacer(10);
    panel3ContentSizer->Add(browseButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel3ContentSizer->AddSpacer(80);
    panel3ContentSizer->Add(clearCacheButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel3ContentSizer->AddStretchSpacer(1);
    panel3ContentSizer->Add(reportNameTextStatic, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 15));
    panel3ContentSizer->Add(reportNameText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxBOTTOM | wxLEFT | wxRIGHT, 45));

    panel2->SetSizer(panel3ContentSizer);
}

void MainFrame::setupPage1() {
    page1Panel1 = new wxPanel(page1, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    page1Panel2 = new wxPanel(page1, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    page1Panel1->SetBackgroundColour(wxColor(100, 100, 100));

    wxBoxSizer *page1Sizer = new wxBoxSizer(wxVERTICAL);

    page1Sizer->Add(page1Panel1, 14, wxEXPAND | wxALL, 15);
    page1Sizer->Add(page1Panel2, 8, wxEXPAND | wxALL, 15);

    page1->SetSizer(page1Sizer);
    
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

void MainFrame::setupPage2() {
    wxStaticText *shareSplitsText = new wxStaticText(page2, wxID_ANY, "Share Split", wxDefaultPosition, wxDefaultSize);
    wxStaticText *ASXCode = new wxStaticText(page2, wxID_ANY, "What is the shares ASX Code?", wxDefaultPosition, wxDefaultSize);
    splitASXCodeInput = new wxTextCtrl(page2, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *ratio = new wxStaticText(page2, wxID_ANY, "Share Split Ratio (1:10) converts 1 share to 10 (1:x)?", wxDefaultPosition, wxDefaultSize);       
    splitRatioInput = new wxTextCtrl(page2, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *date = new wxStaticText(page2, wxID_ANY, "When did the share split occur (dd/mm/yyyy)?", wxDefaultPosition, wxDefaultSize);
    splitDateInput = new wxTextCtrl(page2, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxButton *addButton = new wxButton(page2, wxID_ANY, "Add", wxDefaultPosition, wxDefaultSize);

    shareSplitsText->SetFont(wxFont(wxFontInfo(12).Bold()));
    shareSplitsText->SetForegroundColour(wxColour(255, 255, 255));
    ASXCode->SetForegroundColour(wxColour(255, 255, 255));
    ratio->SetForegroundColour(wxColour(255, 255, 255));
    date->SetForegroundColour(wxColour(255, 255, 255));

    addButton->Bind(wxEVT_BUTTON, &MainFrame::addCacheShareSplitRow, this);

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

    page2->SetSizer(page2Panel1ContentSizer);
}

void MainFrame::setupPage3() {
    wxStaticText *shareNameChangeText = new wxStaticText(page3, wxID_ANY, "Share Name Change", wxDefaultPosition, wxDefaultSize);
    wxStaticText *oldASXCode = new wxStaticText(page3, wxID_ANY, "What is the share's old ASX Code?", wxDefaultPosition, wxDefaultSize);
    oldASXCodeInput = new wxTextCtrl(page3, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *newASXCode = new wxStaticText(page3, wxID_ANY, "What is the share's new ASX Code?", wxDefaultPosition, wxDefaultSize);        
    newASXCodeInput = new wxTextCtrl(page3, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *date = new wxStaticText(page3, wxID_ANY, "When did the share name change occur (dd/mm/yyyy)?", wxDefaultPosition, wxDefaultSize);
    nameChangeDateInput = new wxTextCtrl(page3, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxButton *addButton = new wxButton(page3, wxID_ANY, "Add", wxDefaultPosition, wxDefaultSize);

    shareNameChangeText->SetFont(wxFont(wxFontInfo(12).Bold()));
    shareNameChangeText->SetForegroundColour(wxColour(255, 255, 255));
    oldASXCode->SetForegroundColour(wxColour(255, 255, 255));
    newASXCode->SetForegroundColour(wxColour(255, 255, 255));
    date->SetForegroundColour(wxColour(255, 255, 255));

    addButton->Bind(wxEVT_BUTTON, &MainFrame::addCacheShareNameChangeRow, this);

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

    page3->SetSizer(page3Panel1ContentSizer);
}

void MainFrame::setupPage4() {
    wxStaticText *shareTakeoverText = new wxStaticText(page4, wxID_ANY, "Share Takeover", wxDefaultPosition, wxDefaultSize);
    wxStaticText *ASXCode = new wxStaticText(page4, wxID_ANY, "What is the share's ASX Code?", wxDefaultPosition, wxDefaultSize);
    takeoverASXCodeInput = new wxTextCtrl(page4, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *takeoverPrice = new wxStaticText(page4, wxID_ANY, "What was the share's takeover price?", wxDefaultPosition, wxDefaultSize);        
    takeoverPriceInput = new wxTextCtrl(page4, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxStaticText *date = new wxStaticText(page4, wxID_ANY, "When did the share takeover occur (dd/mm/yyyy)?", wxDefaultPosition, wxDefaultSize);
    takeoverDateInput = new wxTextCtrl(page4, wxID_ANY, "", wxDefaultPosition, wxDefaultSize);
    wxButton *addButton = new wxButton(page4, wxID_ANY, "Add", wxDefaultPosition, wxDefaultSize);

    shareTakeoverText->SetFont(wxFont(wxFontInfo(12).Bold()));
    shareTakeoverText->SetForegroundColour(wxColour(255, 255, 255));
    ASXCode->SetForegroundColour(wxColour(255, 255, 255));
    takeoverPrice->SetForegroundColour(wxColour(255, 255, 255));
    date->SetForegroundColour(wxColour(255, 255, 255));

    addButton->Bind(wxEVT_BUTTON, &MainFrame::addCacheShareTakeoverRow, this);

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

    page4->SetSizer(page4Panel1ContentSizer);

}
    
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    app = dynamic_cast<App*>(wxTheApp);
    if (!app) {
        wxMessageBox("Failed to initialize application", "Error", wxOK | wxICON_ERROR);
        return;
    }
    createPanels();
    setupPanel1();
    setupPanel2();
    setupPage1();
    setupPage2();
    setupPage3();
    setupPage4();
    book->SetSelection(0);
}