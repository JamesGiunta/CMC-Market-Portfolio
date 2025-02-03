#include "dataProcessing.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
// #include <string>
// #include <iostream>


void DataProcessing::discardColumn(std::stringstream& ss){
    std::string discard;
    std::getline(ss, discard, ',');
}

std::time_t DataProcessing::regexDate(std::string& date){
    tm tm = {};
    std::istringstream dateStream(date);
    std::regex datePattern("\\d{1,2}\\/\\d{1,2}\\/\\d{3,4}"); 
    if (std::regex_match (date, datePattern)){
        dateStream >> std::get_time(&tm, "%d/%m/%Y");
    } 
    else {
        dateStream >> std::get_time(&tm, "%Y-%m-%d");
    }
    return std::mktime(&tm);
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
    int seq = 0;
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
        std::time_t date = regexDate(tradeDate);
        row.tradeDate = date;

        std::string settlementDate;
        std::getline(ss, settlementDate, ',');
        date = regexDate(settlementDate);
        row.settlementDate = date;

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
        row.profit = 0;
        row.seq = seq;
        seq++;

        data.push_back(row);
    }

    inputFile.close();
    return data;
}
