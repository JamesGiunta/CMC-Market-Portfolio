#pragma once
#include <wx/wx.h>
#include "../services/dataRetrieval.h"
#include "../services/dataProcessing.h"
#include "../services/tradeOperations.h"
#include "../services/dataRow.h"
#include "../services/excelWriter.h"
#include "../services/threadPool.h"
#include <filesystem>

class App : public wxApp {
    public:
        bool OnInit();
        int OnExit();
        DataRow dataRow;
        DataProcessing dataProcessing;
        TradeOperations tradeOperations;
        DataRetrieval dataRetrieval = DataRetrieval(tradeOperations);
};