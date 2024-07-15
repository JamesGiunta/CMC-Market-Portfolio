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
        void testLoadCSV(DataRow& dr, DataProcessing& dp);
        void testDataRowSorting(DataRow& dr, DataProcessing& dp);
};