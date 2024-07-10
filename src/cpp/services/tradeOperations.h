#pragma once
#include "dataRow.h"
#include <vector>
#include <string>
#include <map>
#include <sstream>

class TradeOperations {
public:
    std::map<std::string, int> createLiveDataVector(std::vector<DataRow>& data);
};