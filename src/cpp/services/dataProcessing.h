#pragma once
#include "dataRow.h"
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

class DataProcessing {
public:
    void discardColumn(std::stringstream& ss);
    std::vector<DataRow> loadCSV(const std::string& filepath);
    std::time_t regexDate(std::string& date);
};