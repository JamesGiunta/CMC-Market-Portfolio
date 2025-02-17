#include "mainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panel3 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    wxPanel *panel4 = new wxPanel(panel2, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    panel->SetBackgroundColour(wxColor(40, 40, 40));
    panel2->SetBackgroundColour(wxColor(40, 40, 40));
    panel3->SetBackgroundColour(wxColor(100, 100, 100));
    panel4->SetBackgroundColour(wxColor(100, 100, 100));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    wxBoxSizer *panel4Sizer = new wxBoxSizer(wxVERTICAL);

    sizer->Add(panel, wxSizerFlags().Proportion(3).Expand().Border(wxALL, 1));
    sizer->Add(panel2, wxSizerFlags().Proportion(5).Expand().Border(wxTOP | wxBOTTOM | wxLEFT, 20));
    sizer->Add(panel3, wxSizerFlags().Proportion(3).Expand().Border(wxTOP | wxRIGHT | wxBOTTOM, 20));

    panel4Sizer->Add(panel4, /*proportion=*/5, wxEXPAND | wxALL, 15);
    panel4Sizer->AddStretchSpacer(5);
    panel2->SetSizer(panel4Sizer);

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

    wxBoxSizer *panel4Sizer2 = new wxBoxSizer(wxVERTICAL);

    panel4Sizer2->Add(confrimationsText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel4Sizer2->AddSpacer(10);
    panel4Sizer2->Add(confirmButton, wxSizerFlags().Proportion(0).Border(wxALL, 10));

    panel4->SetSizer(panel4Sizer2);
}