#include "mainFrame.h"
#include <wx/wx.h>

MainFrame::MainFrame(const wxString& title): wxFrame(nullptr, wxID_ANY, title) {
    wxPanel *panel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    wxPanel *panel2 = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    panel->SetBackgroundColour(wxColor(40, 40, 40));
    panel2->SetBackgroundColour(wxColor(40, 40, 40));

    wxBoxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    sizer->Add(panel, 1, wxEXPAND | wxALL, 1);
    sizer->Add(panel2, 4, wxEXPAND | wxALL, 25);

    this->SetSizerAndFit(sizer);

}