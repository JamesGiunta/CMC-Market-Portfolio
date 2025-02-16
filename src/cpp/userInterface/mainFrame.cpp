#include "mainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    panel->SetBackgroundColour(wxColor(40, 40, 40));
    panel2->SetBackgroundColour(wxColor(40, 40, 40));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);

    sizer->Add(panel, wxSizerFlags().Proportion(1).Expand().Border(wxALL, 1));
    sizer->Add(panel2, wxSizerFlags().Proportion(4).Expand().Border(wxALL, 20));

    this->SetSizerAndFit(sizer);

    wxStaticText *applicationNameText = new wxStaticText(panel, wxID_ANY, "CMC-Market-Report", wxDefaultPosition, wxDefaultSize);
    wxButton *shareSplitButton = new wxButton(panel, wxID_ANY, "Input Share Splits", wxDefaultPosition, wxDefaultSize);
    wxButton *shareNameChangeButton = new wxButton(panel, wxID_ANY, "Input Share Name Changes", wxDefaultPosition, wxDefaultSize);
    wxButton *shareTakeoverButton = new wxButton(panel, wxID_ANY, "Input Share Takeovers", wxDefaultPosition, wxDefaultSize);


    applicationNameText->SetFont(wxFont(wxFontInfo(12).Bold()));
    applicationNameText->SetForegroundColour(wxColour(255, 255, 255));

    wxBoxSizer *panelSizer = new wxBoxSizer(wxVERTICAL);

    panelSizer->AddSpacer(30);
    panelSizer->Add(applicationNameText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
    panelSizer->AddSpacer(30);
    panelSizer->Add(shareSplitButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
    panelSizer->AddSpacer(10);
    panelSizer->Add(shareNameChangeButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));
    panelSizer->AddSpacer(10);
    panelSizer->Add(shareTakeoverButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxLEFT | wxRIGHT | wxBOTTOM, 10));

    panel->SetSizer(panelSizer);
}