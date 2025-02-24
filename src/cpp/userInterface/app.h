#pragma once
#include <wx/wx.h>
#include "../services/dataRetrieval.h"
#include "../services/dataProcessing.h"
#include <filesystem>

class App : public wxApp {
    public:
        bool OnInit();
        DataRetrieval dataRetrieval;
        DataProcessing dataProcessing;
};