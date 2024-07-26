#pragma once
#include "dataRow.h"
#include "tradeOperations.h"

class ExcelWriter {
public:
    void generateExcelFile(const std::vector<DataRow>& data, std::map<std::string, liveShares>& liveSharesMap);
};