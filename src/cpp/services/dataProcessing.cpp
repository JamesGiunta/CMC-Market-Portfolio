#include "dataProcessing.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::vector<DataRow> DataProcessing::loadCSV(const std::string& filepath){
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
        DataRow row;
        std::getline(ss, row.ASXCode, ',');
        std::string orderType;
        std::getline(ss, orderType, ',');
        if (orderType == "Buy"){
            row.orderType = OrderType::BUY;
        } else if (orderType == "Sell"){
            row.orderType = OrderType::SELL;
        } else {
            std::cerr << "Invalid order type: " << orderType << std::endl;
            continue;
        }
        std::string tradeDate;
        std::getline(ss, tradeDate, ',');
        std::tm date;
        std::istringstream dateStream(tradeDate);
        dateStream >> std::get_time(&date, "%d/%m/%Y");
        row.TradeDate = date;
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
