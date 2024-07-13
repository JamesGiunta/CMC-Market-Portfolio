#include "serviceTest.h"
#include "dataRow.h"
#include "dataProcessing.h"
#include "tradeOperations.h"
#include "dataRetrieval.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <algorithm>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <chrono>
#include <thread>
#include <vector>

std::time_t ServiceTest::parseDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream dateStream(dateStr);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    std::time_t date = mktime(&tm);
    return date;
}

void ServiceTest::vectorToCSV(const std::vector<std::vector<std::string>>& data, const std::string& filepath) {
    std::ofstream outputFile(filepath);

    if (!outputFile.is_open()){
        throw std::runtime_error("Unable to open file: " + filepath);
    }

    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outputFile << row[i];
            if (i != row.size() - 1) {
                outputFile << ",";
            }
        }
        outputFile << "\n";
    }

    outputFile.close();
}

void ServiceTest::createTestData() {
    std::vector<std::string> header = {"Account","ASXCode", "Confirmations", "OrderType", "As at Date", "TradeDate", "Settlement Date", "Price", "Quantity", "Brokerage", "GST"};
    std::vector<std::string> row1 = {"", "CBA", "", "Buy", "", "2024-03-19-", "", "115.78", "100", "19.95", "1.17"};
    std::vector<std::string> row2 = {"", "360", "", "Sell", "", "2024-03-01", "", "11.30", "300", "11", "0.73"};
    std::vector<std::string> row3 = {"", "360", "", "Buy", "", "2023-12-04", "", "7.78", "300", "10", "0.59"};

    std::vector<std::vector<std::string>> testData1 = {header, row1, row2, row3};
    vectorToCSV(testData1, "resources/testData.csv");
}

std::vector<DataRow> ServiceTest::testLoadCSV() {
    DataRow dr;
    DataRow expectedRow1 = {"CBA", dr.OrderType::BUY, parseDate("2024-03-19"), double(115.78), 100, double(21.12)};
    DataRow expectedRow2 = {"360", dr.OrderType::SELL, parseDate("2024-03-01"), double(11.30), 300, double(11.73)};
    DataRow expectedRow3 = {"360", dr.OrderType::BUY, parseDate("2023-12-04"), double(7.78), 300, double(10.59)};

    std::vector<DataRow> expectedData = {expectedRow1, expectedRow2, expectedRow3};
    
    return expectedData;
    
}

void ServiceTest::getLivePrices(std::pair<const std::string, liveShares>& pair) {
    DataRetrieval dr;
    std::string jsonResponse = dr.getRequest(pair.first);
    nlohmann::json j = nlohmann::json::parse(jsonResponse);
    double price = j["quote"]["price"];
    std::cout << "Price: " << price << std::endl;
    pair.second.price = price;
}

int main() {
    ServiceTest st;
    st.createTestData();
    std::vector<DataRow> expectedData = st.testLoadCSV();
    DataProcessing dp;
    std::vector<DataRow> data = dp.loadCSV("resources/testData.csv");
    std::cout << "Actual data:" << std::endl;
    for (const auto& row : data) {
        std::cout << row;
    }
    std::cout << std::endl;
    
    std::cout << "Expected data:" << std::endl;
    for (const auto& row : expectedData) {
        std::cout << row;
    }
    std::cout << std::endl;

    if (data == expectedData) {
        std::cout << "Data loaded correctly." << std::endl;
    } 
    else {
        std::cout << "Data did not match expected values." << std::endl;  
    }
    
    TradeOperations to;
    std::map<std::string, liveShares> liveSharesMap = to.createLiveDataVector(data);
    for (const auto& pair : liveSharesMap) {
        std::cout << pair.first << ": " << pair.second.quantity << std::endl;
    }
    
    DataRetrieval dr;
    auto start = std::chrono::high_resolution_clock::now();

    curl_global_init(CURL_GLOBAL_ALL);

    std::cout << dr.getRequest("CBA") << std::endl;

    std::vector<std::thread> threads(liveSharesMap.size());
    int i = 0;
    for (std::pair<const std::string, liveShares>& pair: liveSharesMap) {
        threads[i] = std::thread(std::bind(&ServiceTest::getLivePrices, &st, std::ref(pair)));
        i++;
    }
    for (std::thread& thread : threads) {
        if (thread.joinable()){
            thread.join();
        } 
    }
    curl_global_cleanup();
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;

    return 0;
}