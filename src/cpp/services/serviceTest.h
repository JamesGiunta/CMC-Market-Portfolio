#pragma once
#include "dataRow.h"
#include "dataRetrieval.h"
#include "tradeOperations.h"

class ServiceTest {
    public:
        std::time_t parseDate(const std::string& dateStr);
        void vectorToCSV(const std::vector<std::vector<std::string>>& data, const std::string& filepath);
        void createTestData();
        std::vector<DataRow> testLoadCSV();
        void getLivePrices(std::pair<const std::string, liveShares>& pair);
};