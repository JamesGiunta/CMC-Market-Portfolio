#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <sstream>
#include <nlohmann/json.hpp>

struct DataRow {
    enum OrderType {BUY, SELL};

    std::string ASXCode;
    OrderType orderType;
    std::time_t tradeDate;
    std::time_t settlementDate;
    double price;
    int quantity;
    double fee;
    double profit;
    int seq;
    int tempQuantity;
    double tempFee;
    double cgt;
    long long consideration;
    bool twelveMonths = false;
    
    friend std::ostream& operator<<(std::ostream& os, const DataRow& row);
    friend bool operator==(const DataRow& lhs, const DataRow& rhs);
    bool operator<(const DataRow& obj) const;
    static bool descending(const DataRow& obj, const DataRow& obj2);
    static std::string orderTypeToString(OrderType type);
    static std::string dateToString(std::time_t date);

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(DataRow, ASXCode, orderType, tradeDate, settlementDate, price, quantity, fee, profit, seq, tempQuantity, tempFee, cgt, consideration, twelveMonths)
};

struct ShareSplitRow {
    std::string ASXCode;
    double ratio;
    std::time_t date;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ShareSplitRow, ASXCode, ratio, date)
};

struct NameChangeRow {
    std::string ASXCode;
    std::string newASXCode;
    std::time_t date;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(NameChangeRow, ASXCode, newASXCode, date)
};