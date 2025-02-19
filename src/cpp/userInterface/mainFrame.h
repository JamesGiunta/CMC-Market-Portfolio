#pragma once
#include <wx/wx.h>

class MainFrame : public wxFrame {
    public:
        MainFrame(const wxString& title);
    private:
        wxPanel *panel;
        wxPanel *panel2;
        wxPanel *panel3;
        wxPanel *panel4;
        wxPanel *panel5;

        void CreatePanels();
        void setupPanel1();
        void setupPanel2();
        void setupPanel3();
};