#pragma once
#include <wx/wx.h>
#include <wx/simplebook.h>

class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
    private:
        wxPanel *panel1;
        wxPanel *panel2;
        wxPanel *page1Panel1;
        wxPanel *page1Panel2;
        wxSimplebook *book;
        wxPanel *page1;
        // wxPanel *page2;
        // wxPanel *page3;
        // wxPanel *page4;

        void CreatePanels();
        void setupPanel1();
        void setupPanel2();
        void setupPage1();
};