#pragma once
#include <wx/wx.h>
#include "app.h"

class ShareSplitController : public wxPanel {
    public:
        ShareSplitController(wxPanel *parent, App *app);
    private:
        App *app;
        wxPanel *parent;
        wxTextCtrl *splitASXCodeInput;
        wxTextCtrl *splitRatioInput;
        wxTextCtrl *splitDateInput;
        void setupUI();
        void addCacheShareSplitRow(wxCommandEvent& event);
};