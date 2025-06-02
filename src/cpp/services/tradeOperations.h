#pragma once
#include "dataRow.h"
#include <vector>
#include <string>
#include <map>
#include <sstream>

struct liveShares {
    int quantity;
    long long price;
    long long profit;
    long long cost;
    long long priceBrought;

    friend bool operator==(const liveShares& lhs, const liveShares& rhs);
};

class TradeOperations {
public:
    std::map<std::string, liveShares> createLiveDataVector(std::vector<DataRow>& data);
    void calculateLiveProfit(std::map<std::string, liveShares>& liveSharesMap, std::vector<DataRow>& data);
    void calculateProfit(std::vector<DataRow>& data);
    void calculateCGTPercentage(DataRow& buyOrder, DataRow& sellOrder, long long& cost, int quantityUsed);
};