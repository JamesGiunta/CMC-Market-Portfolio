#include "app.h"
#include "mainFrame.h"
#include <wx/wx.h>
#include <curl/curl.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    curl_global_init(CURL_GLOBAL_ALL);
    MainFrame* mainFrame = new MainFrame("CMC-Market-Report");
    mainFrame->SetClientSize(850, 480);
    mainFrame->SetBackgroundColour(wxColor(20, 20, 20));
    mainFrame->Show();
    return true;
}

int App::OnExit() {
    curl_global_cleanup();
    return wxApp::OnExit();
}