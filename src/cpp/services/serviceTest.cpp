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

void ServiceTest::createTestData(DataRow& dr) {
    std::vector<std::string> header = {"Account","ASXCode", "Confirmations", "OrderType", "As at Date", "TradeDate", "Settlement Date", "Price", "Quantity", "Brokerage", "GST"};
    std::vector<std::string> row1 = {"", "CBA", "", "Buy", "", "2024-03-19-", "", "115.78", "100", "19.95", "1.17"};
    std::vector<std::string> row2 = {"", "360", "", "Sell", "", "2024-03-01", "", "11.30", "300", "11", "0.73"};
    std::vector<std::string> row3 = {"", "360", "", "Buy", "", "2023-12-04", "", "7.78", "300", "10", "0.59"};
    std::vector<std::string> row4 = {"", "ANZ", "", "Sell", "", "2023-11-06", "", "22.78", "30", "10", "0.21"};
    std::vector<std::string> row5 = {"", "ANZ", "", "Buy", "", "2023-11-06", "", "22.33", "30", "10", "0.19"};

    std::vector<std::vector<std::string>> testData1 = {header, row1, row2, row3, row4, row5};
    vectorToCSV(testData1, "resources/testData.csv");
}

void ServiceTest::testLoadCSV(DataRow& dr, DataProcessing& dp) {
    createTestData(dr);
    DataRow expectedRow1 = {"CBA", dr.OrderType::BUY, parseDate("2024-03-19"), double(115.78), 100, double(21.12)};
    DataRow expectedRow2 = {"360", dr.OrderType::SELL, parseDate("2024-03-01"), double(11.30), 300, double(11.73)};
    DataRow expectedRow3 = {"360", dr.OrderType::BUY, parseDate("2023-12-04"), double(7.78), 300, double(10.59)};
    DataRow expectedRow4 = {"ANZ", dr.OrderType::SELL, parseDate("2023-11-06"), double(22.78), 30, double(10.21)};
    DataRow expectedRow5 = {"ANZ", dr.OrderType::BUY, parseDate("2023-11-06"), double(22.33), 30, double(10.19)};

    std::vector<DataRow> expectedData = {expectedRow1, expectedRow2, expectedRow3, expectedRow4, expectedRow5};

    std::vector<DataRow> data = dp.loadCSV("resources/testData.csv");
    std::cout << "function: testLoadCSV" << std::endl;
    if (data == expectedData) {
        std::cout << "Data loaded correctly. ✅" << std::endl;
    } 
    else {
        std::cout << "Data did not load correctly. ❌" << std::endl;  
    }    
}


void ServiceTest::testDataRowSorting(DataRow& dr, DataProcessing& dp) {
    DataRow expectedRow1 = {"ANZ", dr.OrderType::BUY, parseDate("2023-11-06"), double(22.33), 30, double(10.19)};
    DataRow expectedRow2 = {"ANZ", dr.OrderType::SELL, parseDate("2023-11-06"), double(22.78), 30, double(10.21)};
    DataRow expectedRow3 = {"360", dr.OrderType::BUY, parseDate("2023-12-04"), double(7.78), 300, double(10.59)};
    DataRow expectedRow4 = {"360", dr.OrderType::SELL, parseDate("2024-03-01"), double(11.30), 300, double(11.73)};
    DataRow expectedRow5 = {"CBA", dr.OrderType::BUY, parseDate("2024-03-19"), double(115.78), 100, double(21.12)};

    std::vector<DataRow> expectedData = {expectedRow1, expectedRow2, expectedRow3, expectedRow4, expectedRow5};
    std::vector<DataRow> data = dp.loadCSV("resources/testData.csv");
    std::sort(data.begin(), data.end());
    std::cout << "function: testLoadCSV" << std::endl;
    if (data == expectedData) {
        std::cout << "Data loaded correctly. ✅" << std::endl;
    } 
    else {
        std::cout << "Data did not load correctly. ❌" << std::endl;  
    } 
}



int main() {
    ServiceTest st;
    DataRow dr;
    DataProcessing dp;
    // TradeOperations to;
    st.testLoadCSV(dr, dp);
    st.testDataRowSorting(dr, dp);
    
    // std::map<std::string, liveShares> liveSharesMap = to.createLiveDataVector(data);
    // for (const auto& pair : liveSharesMap) {
    //     std::cout << pair.first << ": " << pair.second.quantity << std::endl;
    // }

    // curl_global_init(CURL_GLOBAL_ALL);
    // DataRetrieval dr;

    // std::vector<std::thread> threads(liveSharesMap.size());
    // int i = 0;
    // for (std::pair<const std::string, liveShares>& pair: liveSharesMap) {
    //     threads[i] = std::thread(std::bind(&DataRetrieval::getLivePrices, &dr, std::ref(pair)));
    //     i++;
    // }
    // for (std::thread& thread : threads) {
    //     if (thread.joinable()){
    //         thread.join();
    //     } 
    // }
    // curl_global_cleanup();

    // to.calculateLiveProfit(liveSharesMap, data);

    return 0;
}