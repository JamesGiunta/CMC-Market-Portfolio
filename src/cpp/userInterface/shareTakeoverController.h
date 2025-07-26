#pragma once
#include <wx/wx.h>
#include "app.h"

class ShareTakeoverController {
public:
    ShareTakeoverController(wxPanel *parent, App *app);
private:
    App *app;
    wxPanel *parent;
    wxTextCtrl *takeoverASXCodeInput;
    wxTextCtrl *takeoverPriceInput;
    wxTextCtrl *takeoverDateInput;
    void setupUI();
    void addCacheShareTakeoverRow(wxCommandEvent& event);
};