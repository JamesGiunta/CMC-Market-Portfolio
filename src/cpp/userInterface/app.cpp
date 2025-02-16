#include "app.h"
#include "mainFrame.h"
#include <wx/wx.h>

wxIMPLEMENT_APP(App);

bool App::OnInit() {
    MainFrame* mainFrame = new MainFrame("CMC-Market-Report");
    mainFrame->SetClientSize(850, 570);
    mainFrame->SetBackgroundColour(wxColor(20, 20, 20));
    mainFrame->Show();
    return true;
}