#include "generateReportController.h"

void GenerateReportController::selectConfirmation(wxCommandEvent &event) {
    wxFileDialog openFileDialog(parent, "Select Confirmation", "", "", "CSV files (*.csv)|*.csv", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

    if (openFileDialog.ShowModal() == wxID_OK) {
        std::filesystem::path path = openFileDialog.GetPath().ToStdString();
        wxString fileName = path.filename().string();
        wxString pathString = path.string();
        confirmationPaths.push_back(pathString);
        confirmationsList->Append(fileName);
    }
}

void GenerateReportController::onListBoxDoubleClick(wxCommandEvent& event) {
    int selection = confirmationsList->GetSelection();
    if (selection != wxNOT_FOUND) {
        confirmationsList->Delete(selection);
        confirmationPaths.erase(confirmationPaths.begin() + selection);
    }
}

void GenerateReportController::generateReport(wxCommandEvent &event) {
    bool useCache = cacheCheckBox->IsChecked();

    std::cout << useCache << std::endl;

    if (confirmationPaths.size() == 0) {
        wxMessageBox("Please select at least one confirmation", "Error", wxICON_ERROR);
        return;
    }
}

void GenerateReportController::setupUI() {
    page1Panel1 = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);
    page1Panel2 = new wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    page1Panel1->SetBackgroundColour(wxColor(100, 100, 100));

    wxBoxSizer *page1Sizer = new wxBoxSizer(wxVERTICAL);

    page1Sizer->Add(page1Panel1, 14, wxEXPAND | wxALL, 15);
    page1Sizer->Add(page1Panel2, 8, wxEXPAND | wxALL, 15);

    parent->SetSizer(page1Sizer);
    
    wxStaticText *confrimationsText = new wxStaticText(page1Panel1, wxID_ANY, "Select Confirmations", wxDefaultPosition, wxDefaultSize);
    wxButton *confirmButton = new wxButton(page1Panel1, wxID_ANY, "Add Confirmation", wxDefaultPosition, wxDefaultSize);
    confirmationsList = new wxListBox(page1Panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize);

    confrimationsText->SetFont(wxFont(wxFontInfo(12).Bold()));

    confirmationsList->SetBackgroundColour(wxColor(100, 100, 100));
    confirmationsList->SetForegroundColour(wxColor(255, 255, 255));

    confirmButton->Bind(wxEVT_BUTTON, &GenerateReportController::selectConfirmation, this);
    confirmationsList->Bind(wxEVT_LISTBOX_DCLICK, &GenerateReportController::onListBoxDoubleClick, this);


    cacheCheckBox = new wxCheckBox(page1Panel2, 1, "Use Cache", wxDefaultPosition, wxDefaultSize, wxCHK_2STATE);
    wxButton *generateReportButton = new wxButton(page1Panel2, wxID_ANY, "Generate Report", wxDefaultPosition, wxDefaultSize);

    cacheCheckBox->SetValue(true);
    cacheCheckBox->SetForegroundColour(wxColour(255, 255, 255));

    generateReportButton->Bind(wxEVT_BUTTON, &GenerateReportController::generateReport, this);

    wxBoxSizer *panel4ContentSizer = new wxBoxSizer(wxVERTICAL);

    panel4ContentSizer->Add(confrimationsText, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel4ContentSizer->AddSpacer(10);
    panel4ContentSizer->Add(confirmButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel4ContentSizer->AddSpacer(20);
    panel4ContentSizer->Add(confirmationsList, wxSizerFlags().Proportion(1).Expand().Border(wxLEFT | wxRIGHT, 50)); 
    panel4ContentSizer->AddSpacer(10);   
    page1Panel1->SetSizer(panel4ContentSizer);

    wxBoxSizer *panel5ContentSizer = new wxBoxSizer(wxVERTICAL);

    panel5ContentSizer->Add(cacheCheckBox, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 10));
    panel5ContentSizer->AddStretchSpacer(1);
    panel5ContentSizer->Add(generateReportButton, wxSizerFlags().Proportion(0).CenterHorizontal().Border(wxALL, 30));

    page1Panel2->SetSizer(panel5ContentSizer);
}

GenerateReportController::GenerateReportController(wxPanel *parent, App *app) {
    this->app = app;
    this->parent = parent;
    setupUI();
}