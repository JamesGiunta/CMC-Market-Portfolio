#pragma once
#include <wx/wx.h>
#include <wx/simplebook.h>

class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
    private:
        wxPanel *panel;
        wxPanel *panel3;
        wxPanel *panel4;
        wxPanel *panel5;
        wxSimplebook *book;
        wxPanel *page1;
        // wxPanel *page2;
        // wxPanel *page3;
        // wxPanel *page4;

        void CreatePanels();
        void setupPanel1();
        void setupPanel2();
        void setupPanel3();
};