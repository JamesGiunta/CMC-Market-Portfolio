#include "dataProcessing.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void DataProcessing::discardColumn(std::stringstream& ss){
    std::string discard;
    std::getline(ss, discard, ',');
}

std::vector<DataRow> DataProcessing::loadCSV(const std::string& filepath){
    DataRow dr;
    std::vector<DataRow> data;
    std::ifstream inputFile;
    inputFile.open(filepath);

    if (!inputFile.is_open()){
        std::cerr << "Unable to open file: " << filepath << std::endl;
        return data;
    }
    
    std::string line;
    std::getline(inputFile, line); // skip header
    
    while (std::getline(inputFile, line)){
        std::stringstream ss(line);
        discardColumn(ss);
        DataRow row;
        std::getline(ss, row.ASXCode, ',');
        discardColumn(ss);
        std::string orderType;
        std::getline(ss, orderType, ',');
        if (orderType == "Buy"){
            row.orderType = dr.OrderType::BUY;
        } 
        else if (orderType == "Sell"){
            row.orderType = dr.OrderType::SELL;
        } 
        else {
            throw std::runtime_error("Invalid order type: " + orderType);
        }
        discardColumn(ss);
        std::string tradeDate;
        std::getline(ss, tradeDate, ',');
        tm tm = {};
        std::istringstream dateStream(tradeDate);
        dateStream >> std::get_time(&tm, "%d/%m/%Y");
        std::time_t date = mktime(&tm);
        row.tradeDate = date;
        discardColumn(ss);
        std::string price;
        std::getline(ss, price, ',');
        row.price = std::stod(price);
        std::string quantity;
        std::getline(ss, quantity, ',');
        row.quantity = std::stoi(quantity);
        std::string brokerage;
        std::getline(ss, brokerage, ',');
        row.fee = std::stod(brokerage);
        std::string gst;
        std::getline(ss, gst, ',');
        row.fee += std::stod(gst);

        data.push_back(row);
    }

    inputFile.close();
    return data;
}
