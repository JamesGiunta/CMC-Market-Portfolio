#pragma once
#include "dataRow.h"
#include <vector>
#include <string>
#include <map>
#include <sstream>

struct liveShares {
    int quantity;
    double price;
};

class TradeOperations {
public:
    std::map<std::string, liveShares> createLiveDataVector(std::vector<DataRow>& data);
};