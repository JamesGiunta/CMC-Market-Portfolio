#pragma once
#include <vector>
#include <string>
#include <ctime>
#include <sstream>


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
    void discardColumn(std::stringstream& ss);
    std::vector<DataRow> loadCSV(const std::string& filepath);
};