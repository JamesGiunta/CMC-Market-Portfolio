#include "mainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    wxPanel *panel4 = new wxPanel(panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panel5 = new wxPanel(panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    panel->SetBackgroundColour(wxColor(40, 40, 40));
    panel2->SetBackgroundColour(wxColor(40, 40, 40));
    panel3->SetBackgroundColour(wxColor(100, 100, 100));
    panel4->SetBackgroundColour(wxColor(100, 100, 100));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *panel2Sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(panel, wxSizerFlags().Proportion(3).Expand().Border(wxALL, 1));
    sizer->Add(panel2, wxSizerFlags().Proportion(5).Expand().Border(wxTOP | wxBOTTOM | wxLEFT, 20));
    sizer->Add(panel3, wxSizerFlags().Proportion(3).Expand().Border(wxTOP | wxRIGHT | wxBOTTOM, 20));

    panel2Sizer->Add(panel4, 14, wxEXPAND | wxALL, 15);
    panel2Sizer->Add(panel5, 8, wxEXPAND | wxALL, 15);

    panel2->SetSizer(panel2Sizer);

    this->SetSizer(sizer);

    wxStaticText *applicationNameText = new wxStaticText(panel, wxID_ANY, "CMC-Market-Report", wxDefaultPosition, wxDefaultSize);
    wxButton *generateButton = new wxButton(panel, wxID_ANY, "Generate Report", wxDefaultPosition, wxDefaultSize);
    wxButton *shareSplitButton = new wxButton(panel, wxID_ANY, "Input Share Splits", wxDefaultPosition, wxDefaultSize);
    wxButton *shareNameChangeButton = new wxButton(panel, wxID_ANY, "Input Name Changes", wxDefaultPosition, wxDefaultSize);
    wxButton *shareTakeoverButton = new wxButton(panel, wxID_ANY, "Input Share Takeovers", wxDefaultPosition, wxDefaultSize);

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

    panel->SetSizer(panelSizer);

    wxStaticText *confrimationsText = new wxStaticText(panel4, wxID_ANY, "Select Confirmations", wxDefaultPosition, wxDefaultSize);
    wxButton *confirmButton = new wxButton(panel4, wxID_ANY, "Add Confirmation", wxDefaultPosition, wxDefaultSize);
    confrimationsText->SetFont(wxFont(wxFontInfo(12).Bold()));

    wxBoxSizer *panel4ContentSizer = new wxBoxSizer(wxVERTICAL);

    wxCheckBox *checkBox = new wxCheckBox(panel5, wxID_ANY, "Use Cache", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
    wxButton *generateReportButton = new wxButton(panel5, wxID_ANY, "Generate Report", wxDefaultPosition, wxDefaultSize);

    checkBox->SetValue(true);

    panel4ContentSizer->Add(confrimationsText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel4ContentSizer->AddSpacer(10);
    panel4ContentSizer->Add(confirmButton, wxSizerFlags().Proportion(0).Border(wxALL, 10));

    panel4->SetSizer(panel4ContentSizer);

    wxBoxSizer *panel5ContentSizer = new wxBoxSizer(wxVERTICAL);

    panel5ContentSizer->Add(checkBox, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel5ContentSizer->AddStretchSpacer(1);
    panel5ContentSizer->Add(generateReportButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 30));

    panel5->SetSizer(panel5ContentSizer);

    wxStaticText *fileSaveLocation = new wxStaticText(panel3, wxID_ANY, "File Save Location", wxDefaultPosition, wxDefaultSize);
    wxButton *browseButton = new wxButton(panel3, wxID_ANY, "Browse", wxDefaultPosition, wxDefaultSize);
    wxButton *clearCacheButton = new wxButton(panel3, wxID_ANY, "Clear Cache", wxDefaultPosition, wxDefaultSize);
    wxStaticText *reportNameTextStatic = new wxStaticText(panel3, wxID_ANY, "Generated File Name:", wxDefaultPosition, wxDefaultSize);
    wxTextCtrl *reportNameText = new wxTextCtrl(panel3, wxID_ANY, "Report", wxDefaultPosition, wxDefaultSize);

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

    panel3->SetSizer(panel3ContentSizer);

}