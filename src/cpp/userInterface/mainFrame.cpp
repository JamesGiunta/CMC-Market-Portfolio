#include "mainFrame.h"
#include <wx/wx.h>
#include <wx/simplebook.h>
#include <filesystem>

void MainFrame::onFileSaveLocationButton(wxCommandEvent& event) {
    wxDirDialog dialog(this, "Choose a directory", "", wxDD_DEFAULT_STYLE | wxDD_DIR_MUST_EXIST);
    if (dialog.ShowModal() == wxID_OK) {
        *filePath = std::filesystem::path(dialog.GetPath().ToStdString());
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
    reportNameText = new wxTextCtrl(panel2, wxID_ANY, "Report", wxDefaultPosition, wxDefaultSize);

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
    
MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    app = dynamic_cast<App*>(wxTheApp);
    if (!app) {
        wxMessageBox("Failed to initialize application", "Error", wxOK | wxICON_ERROR);
        return;
    }
    createPanels();
    setupPanel1();
    setupPanel2();

    std::filesystem::path filePathLocation= std::filesystem::current_path().parent_path() / "reports";

    filePath = std::make_shared<std::filesystem::path>(filePathLocation);
    if (!std::filesystem::exists(filePathLocation)) {
        std::filesystem::create_directories(filePathLocation);
    }
    generateReportController = new GenerateReportController(page1, app, reportNameText, filePath);
    shareSplitController = new ShareSplitController(page2, app);
    shareNameChangeController = new ShareNameChangeController(page3, app);
    shareTakeoverController = new ShareTakeoverController(page4, app);
    book->SetSelection(0);
}