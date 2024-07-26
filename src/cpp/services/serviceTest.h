#pragma once
#include "dataRow.h"
#include "dataRetrieval.h"
#include "tradeOperations.h"
#include "dataProcessing.h"

class ServiceTest {
    public:
        std::time_t parseDate(const std::string& dateStr);
        void vectorToCSV(const std::vector<std::vector<std::string>>& data, const std::string& filepath);
        void createTestData(DataRow& dr);
        std::vector<DataRow> generateTestData(DataRow& dr);
        void testLoadCSV(DataRow& dr, DataProcessing& dp);
        void testDataRowSorting(DataRow& dr);
        void testLiveDataVector(DataRow& dr, TradeOperations& to);
        void testLiveShareValue(TradeOperations& to);
        void testCalculateLiveProfit(DataRow& dr, TradeOperations& to);
        void testCalculateProfit(DataRow& dr, TradeOperations& to);
        void testExcelExport(DataRow& dr, TradeOperations& to);
};