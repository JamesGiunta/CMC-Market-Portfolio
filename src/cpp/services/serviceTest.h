#pragma once
#include "dataRow.h"
#include "dataRetrieval.h"
#include "tradeOperations.h"
#include "dataProcessing.h"
#include "excelWriter.h"
#include "corporateShareActions.h"

class ServiceTest {
    public:
        static void testLoadCSV(DataRow& dr, DataProcessing& dp);
        static void testDataRowSorting(DataRow& dr);
        static void testLiveDataVector(DataRow& dr, TradeOperations& to);
        static void testLiveShareValue(TradeOperations& to);
        static void testCalculateLiveProfit(DataRow& dr, TradeOperations& to);
        static void testCalculateProfit(DataRow& dr, TradeOperations& to);
        static void testcalculateCGTPercentage(DataRow& dr, TradeOperations& to);
        static void testExcelExport(DataRow& dr, TradeOperations& to, ExcelWriter& ew);
        static void createDirectory();

    private:
        static std::time_t parseDate(const std::string& dateStr);
        static void vectorToCSV(const std::vector<std::vector<std::string>>& data, const std::string& filepath);
        static void createTestData(DataRow& dr);
        static std::vector<DataRow> generateTestData(DataRow& dr);
};