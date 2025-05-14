#pragma once
#include <wx/wx.h>
#include "../services/dataRetrieval.h"
#include "../services/dataProcessing.h"
#include "../services/tradeOperations.h"
#include "../services/dataRow.h"
#include "../services/excelWriter.h"
#include "../services/highPrecisionMoney.h"
#include <filesystem>

class App : public wxApp {
    public:
        bool OnInit();
        DataRow dataRow;
        DataProcessing dataProcessing;
        TradeOperations tradeOperations;
        DataRetrieval dataRetrieval = DataRetrieval(tradeOperations);
};