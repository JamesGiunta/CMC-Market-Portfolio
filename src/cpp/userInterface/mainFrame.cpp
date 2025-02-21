#include "mainFrame.h"
#include <wx/wx.h>
#include <wx/simplebook.h>


void MainFrame::CreatePanels() {
    panel1 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    
    book = new wxSimplebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    page1 = new wxPanel(book);
    // page2 = new wxPanel(book);
    // page3 = new wxPanel(book);
    // page4 = new wxPanel(book);
    book->AddPage(page1, "Page 1");
    // book->AddPage(page2, "Page 2");
    // book->AddPage(page3, "Page 3");
    // book->AddPage(page4, "Page 4");

    book->SetSelection(0);

    panel1->SetBackgroundColour(wxColor(40, 40, 40));
    book->SetBackgroundColour(wxColor(40, 40, 40));
    panel2->SetBackgroundColour(wxColor(100, 100, 100));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(panel1, wxSizerFlags().Proportion(3).Expand().Border(wxALL, 1));
    sizer->Add(book, wxSizerFlags().Proportion(5).Expand().Border(wxTOP | wxBOTTOM | wxLEFT, 20));
    sizer->Add(panel2, wxSizerFlags().Proportion(3).Expand().Border(wxTOP | wxRIGHT | wxBOTTOM, 20));

    this->SetSizer(sizer);
}

void MainFrame::setupPanel1() {
    wxStaticText *applicationNameText = new wxStaticText(panel1, wxID_ANY, "CMC-Market-Report", wxDefaultPosition, wxDefaultSize);
    wxButton *generateButton = new wxButton(panel1, wxID_ANY, "Generate Report", wxDefaultPosition, wxDefaultSize);
    wxButton *shareSplitButton = new wxButton(panel1, wxID_ANY, "Input Share Splits", wxDefaultPosition, wxDefaultSize);
    wxButton *shareNameChangeButton = new wxButton(panel1, wxID_ANY, "Input Name Changes", wxDefaultPosition, wxDefaultSize);
    wxButton *shareTakeoverButton = new wxButton(panel1, wxID_ANY, "Input Share Takeovers", wxDefaultPosition, wxDefaultSize);

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

    wxBoxSizer *panel3ContentSizer = new wxBoxSizer(wxVERTICAL);

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

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    CreatePanels();
    setupPanel1();
    setupPanel2();
    setupPage1();
}