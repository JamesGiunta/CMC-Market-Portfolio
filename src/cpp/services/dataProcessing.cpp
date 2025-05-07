#include "dataProcessing.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <regex>
#include <nlohmann/json.hpp>



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
        discardColumn(ss);
        discardColumn(ss);
        discardColumn(ss);
        discardColumn(ss);
        discardColumn(ss);
        std::string consideration;
        std::getline(ss, consideration, ',');
        bool round = false;
        size_t dotPos = consideration.find('.');
        if (dotPos == std::string::npos) {
            // Convert to cents
            consideration = consideration + "00";
        }
        else {
            int pos = consideration.find(".");
            // If there is no digit after the decimal point, add two zeros
            if (consideration.length() - pos == 1) {             
                consideration = consideration + "00";
            }
            // If there is one digit after the decimal point, add one zero
            else if (consideration.length() - pos == 2) {
                consideration = consideration + "0";
            }
            
            // If there is three or more digits after the decimal point and the third digit is greater than 5, round up
            else if (consideration.length() - pos > 3) {
                char thirdCharAfterPos = consideration[pos + 3];
                if (thirdCharAfterPos >= '5') {
                    round = true;
                }
                consideration = consideration.substr(0, pos + 3);
            }
            // Remove the decimal point
            consideration.erase(pos, 1);
        }
        try {
            long long considerationValue = std::stoll(consideration);
            if (round) {
                considerationValue += 1;
            }
            row.consideration = considerationValue;
        }
        catch (const std::invalid_argument& e) {
            std::cerr << "Invalid consideration value: " << consideration << std::endl;
            break;
        }
        catch (const std::out_of_range& e) {
            std::cerr << "Consideration value out of range: " << consideration << std::endl;
            break;
        }    
        row.seq = seq;
        seq++;
        row.cgt = 0;

        data.push_back(row);
    }

    inputFile.close();
    return data;
}
