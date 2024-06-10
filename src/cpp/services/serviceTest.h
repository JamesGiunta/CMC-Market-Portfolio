#pragma once
#include "dataProcessing.h"
#include <vector>

class ServiceTest {
    public:
        std::time_t parseDate(const std::string& dateStr);
        void vectorToCSV(const std::vector<std::vector<std::string>>& data, const std::string& filepath);
        std::vector<DataRow> createTestData();
        void testLoadCSV();
};