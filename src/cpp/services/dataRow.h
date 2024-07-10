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
    int seq;

    friend bool operator==(const DataRow& lhs, const DataRow& rhs);
    friend std::ostream& operator<<(std::ostream& os, const DataRow& row);
    bool operator<(const DataRow& obj) const { 
        if (tradeDate == obj.tradeDate) {
            return seq > obj.seq;
        }
        return tradeDate < obj.tradeDate; 
    } 
};