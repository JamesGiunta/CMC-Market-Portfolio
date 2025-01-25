#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <sstream>

struct DataRow {
    enum OrderType {BUY, SELL};

    std::string ASXCode;
    OrderType orderType;
    std::time_t tradeDate;
    double price;
    int quantity;
    double fee;
    double profit;
    int seq;
    int tempQuantity;
    double tempFee;
    bool twelveMonths = false;
    
    friend std::ostream& operator<<(std::ostream& os, const DataRow& row);
    friend bool operator==(const DataRow& lhs, const DataRow& rhs);
    bool operator<(const DataRow& obj) const;
    static bool descending(const DataRow& obj, const DataRow& obj2);
    static std::string orderTypeToString(OrderType type);
    static std::string dateToString(std::time_t date);
};

