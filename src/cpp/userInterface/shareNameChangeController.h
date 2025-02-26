#pragma once
#include <wx/wx.h>
#include "app.h"

class ShareNameChangeController {
    public:
        ShareNameChangeController(wxPanel *parent, App *app);
    private:
        App *app;
        wxPanel *parent;
        wxTextCtrl *oldASXCodeInput;
        wxTextCtrl *newASXCodeInput;
        wxTextCtrl *nameChangeDateInput;
        void setupUI();
        void addCacheShareNameChangeRow(wxCommandEvent& event);
};