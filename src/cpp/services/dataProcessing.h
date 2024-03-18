#pragma once
#include <vector>
#include <string>
#include <ctime>


enum OrderType {BUY, SELL};

struct DataRow {
    std::string ASXCode;
    OrderType orderType;
    std::tm TradeDate;
    double price;
    int quantity;
    double fee;
};


class DataProcessing {
public:
    std::vector<DataRow> loadCSV(const std::string& filepath);
};