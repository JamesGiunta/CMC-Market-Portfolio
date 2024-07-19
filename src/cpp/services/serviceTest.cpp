#include "serviceTest.h"
#include "dataRow.h"
#include "dataProcessing.h"
#include "tradeOperations.h"
#include "dataRetrieval.h"
#include "xlsxwriter.h"
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
    std::vector<std::string> row4 = {"", "ANZ", "", "Sell", "", "2023-11-06", "", "22.78", "10", "10", "0.21"};
    std::vector<std::string> row5 = {"", "ANZ", "", "Buy", "", "2023-11-06", "", "22.33", "30", "10", "0.19"};

    std::vector<std::vector<std::string>> testData1 = {header, row1, row2, row3, row4, row5};
    vectorToCSV(testData1, "resources/testData.csv");
}

std::vector<DataRow> ServiceTest::generateTestData(DataRow& dr) {
    DataRow row1 = {"CBA", dr.OrderType::BUY, parseDate("2024-03-19"), double(115.78), 100, double(21.12), 0, 0};
    DataRow row2 = {"360", dr.OrderType::SELL, parseDate("2024-03-01"), double(11.30), 300, double(11.73), 0, 1};
    DataRow row3 = {"360", dr.OrderType::BUY, parseDate("2023-12-04"), double(7.78), 300, double(10.59), 0, 2};
    DataRow row4 = {"ANZ", dr.OrderType::SELL, parseDate("2023-11-06"), double(22.78), 10, double(10.21), 0, 3};
    DataRow row5 = {"ANZ", dr.OrderType::BUY, parseDate("2023-11-06"), double(22.33), 30, double(10.19), 0, 4};

    std::vector<DataRow> testData = {row1, row2, row3, row4, row5};
    return testData;
}

void ServiceTest::testLoadCSV(DataRow& dr, DataProcessing& dp) {
    createTestData(dr);
    DataRow expectedRow1 = {"CBA", dr.OrderType::BUY, parseDate("2024-03-19"), double(115.78), 100, double(21.12)};
    DataRow expectedRow2 = {"360", dr.OrderType::SELL, parseDate("2024-03-01"), double(11.30), 300, double(11.73)};
    DataRow expectedRow3 = {"360", dr.OrderType::BUY, parseDate("2023-12-04"), double(7.78), 300, double(10.59)};
    DataRow expectedRow4 = {"ANZ", dr.OrderType::SELL, parseDate("2023-11-06"), double(22.78), 10, double(10.21)};
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

void ServiceTest::testDataRowSorting(DataRow& dr) {
    bool ascending = false;
    bool descending = false;
    DataRow expectedRow1 = {"ANZ", dr.OrderType::BUY, parseDate("2023-11-06"), double(22.33), 30, double(10.19)};
    DataRow expectedRow2 = {"ANZ", dr.OrderType::SELL, parseDate("2023-11-06"), double(22.78), 10, double(10.21)};
    DataRow expectedRow3 = {"360", dr.OrderType::BUY, parseDate("2023-12-04"), double(7.78), 300, double(10.59)};
    DataRow expectedRow4 = {"360", dr.OrderType::SELL, parseDate("2024-03-01"), double(11.30), 300, double(11.73)};
    DataRow expectedRow5 = {"CBA", dr.OrderType::BUY, parseDate("2024-03-19"), double(115.78), 100, double(21.12)};

    std::vector<DataRow> expectedData = {expectedRow1, expectedRow2, expectedRow3, expectedRow4, expectedRow5};
    std::vector<DataRow> expectedData2 = {expectedRow5, expectedRow4, expectedRow3, expectedRow2, expectedRow1};

    std::vector<DataRow> testData = generateTestData(dr);
    std::sort(testData.begin(), testData.end());
    ascending = (testData == expectedData);
    std::sort(testData.begin(), testData.end(), DataRow::descending);
    descending = (testData == expectedData2);
    std::cout << "function: testDataRowSorting" << std::endl;
    if (ascending && descending) {
        std::cout << "Both ascending and descending sort are correct. ✅" << std::endl;
    } 
    else if (!ascending && descending) {
        std::cout << "Ascending sort is incorrect. ❌" << std::endl;
    }
    else if (ascending && !descending) {
        std::cout << "Descending sort is incorrect. ❌" << std::endl;
    }
    else {
        std::cout << "Both ascending and descending sort is incorrect. ❌" << std::endl;  
    }
}

void ServiceTest::testLiveDataVector(DataRow& dr, TradeOperations& to) {
    liveShares expectedLiveShare1 = {20};
    liveShares expectedLiveShare2 = {100};

    std::map<std::string, liveShares> expectedLiveShares;
    expectedLiveShares["ANZ"] = expectedLiveShare1;
    expectedLiveShares["CBA"] = expectedLiveShare2;

    std::vector<DataRow> testData = generateTestData(dr);
    std::map<std::string, liveShares> liveSharesMap = to.createLiveDataVector(testData);
    std::cout << "function: testLiveDataVector" << std::endl;
    if (liveSharesMap == expectedLiveShares) {
        std::cout << "Live data vector created correctly. ✅" << std::endl;
    } 
    else {
        std::cout << "Live data vector did not create correctly. ❌" << std::endl;  
    }

}

void ServiceTest::testLiveShareValue(TradeOperations& to) {
    bool flag = false;
    liveShares LiveShare1 = {20};
    liveShares LiveShare2 = {100};
    DataRetrieval dr;

    std::map<std::string, liveShares> liveSharesMap;
    liveSharesMap["ANZ"] = LiveShare1;
    liveSharesMap["CBA"] = LiveShare2;

    curl_global_init(CURL_GLOBAL_ALL);

    std::vector<std::thread> threads(liveSharesMap.size());
    int i = 0;
    for (std::pair<const std::string, liveShares>& pair: liveSharesMap) {
        threads[i] = std::thread(std::bind(&DataRetrieval::getLivePrices, &dr, std::ref(pair)));
        i++;
    }
    for (std::thread& thread : threads) {
        if (thread.joinable()){
            thread.join();
        } 
    }
    curl_global_cleanup();
    if (liveSharesMap["ANZ"].price != 0 && liveSharesMap["ANZ"].price != 0) {
        flag = true;
    }

    std::cout << "function: testLiveShareValue" << std::endl;
    if (flag) {
        std::cout << "Live share values retrieved correctly. ✅" << std::endl;
    } 
    else {
        std::cout << "Live share values did not retrieve correctly. ❌" << std::endl;  
    }
}

void ServiceTest::testCalculateLiveProfit(DataRow& dr, TradeOperations& to) {
    liveShares expectedLiveShare1 = {20, 24.31, 32.81};
    liveShares expectedLiveShare2 = {100, 110.12, -587.12};

    std::map<std::string, liveShares> expectedLiveShares;
    expectedLiveShares["ANZ"] = expectedLiveShare1;
    expectedLiveShares["CBA"] = expectedLiveShare2;

    liveShares liveShare1 = {20, 24.31};
    liveShares liveShare2 = {100, 110.12};

    std::map<std::string, liveShares> liveSharesMap;
    liveSharesMap["ANZ"] = liveShare1;
    liveSharesMap["CBA"] = liveShare2;

    std::vector<DataRow> testData = generateTestData(dr);
    to.calculateLiveProfit(liveSharesMap, testData);
    std::cout << "function: testLiveDataVector" << std::endl;
    if (liveSharesMap == expectedLiveShares) {
        std::cout << "Live data vector created correctly. ✅" << std::endl;
    } 
    else {
        std::cout << "Live data vector did not create correctly. ❌" << std::endl;  
    }
}

void ServiceTest::testCalculateProfit(DataRow& dr, TradeOperations& to) {
    DataRow expectedRow1 = {"ANZ", dr.OrderType::BUY, parseDate("2023-11-06"), double(22.33), 30, double(10.19), 0};
    DataRow expectedRow2 = {"ANZ", dr.OrderType::SELL, parseDate("2023-11-06"), double(22.78), 10, double(10.21), -9.11};
    DataRow expectedRow3 = {"360", dr.OrderType::BUY, parseDate("2023-12-04"), double(7.78), 300, double(10.59), 0};
    DataRow expectedRow4 = {"360", dr.OrderType::SELL, parseDate("2024-03-01"), double(11.30), 300, double(11.73), 1033.68};
    DataRow expectedRow5 = {"CBA", dr.OrderType::BUY, parseDate("2024-03-19"), double(115.78), 100, double(21.12), 0};

    std::vector<DataRow> expectedData = {expectedRow5, expectedRow4, expectedRow3, expectedRow2, expectedRow1};

    std::vector<DataRow> testData = generateTestData(dr);
    to.calculateProfit(testData);
    std::cout << "function: testCalculateProfit" << std::endl;
    if (testData == expectedData) {
        std::cout << " Data profit calculated correctly. ✅" << std::endl;
    } 
    else {
        std::cout << "Data profit was not calculated correctly. ❌" << std::endl;  
    }
}


int main() {
    ServiceTest st;
    DataRow dr;
    DataProcessing dp;
    TradeOperations to;
    st.testLoadCSV(dr, dp);
    st.testDataRowSorting(dr);
    st.testLiveDataVector(dr, to);
    st.testLiveShareValue(to);
    st.testCalculateLiveProfit(dr, to);
    st.testCalculateProfit(dr, to);

    lxw_workbook  *workbook  = workbook_new("Report.xlsx");
    lxw_worksheet *worksheet1 = workbook_add_worksheet(workbook, NULL);
    worksheet_set_column(worksheet1, 0, 2, 10, NULL);
    worksheet_set_column(worksheet1, 5, 8, 12, NULL);
    worksheet_set_column(worksheet1, 9, 9, 15, NULL);
    worksheet_set_column(worksheet1, 10, 10, 12, NULL);
    worksheet_set_column(worksheet1, 11, 11, 15, NULL);
    worksheet_set_column(worksheet1, 12, 13, 12, NULL);
    worksheet_set_column(worksheet1, 15, 15, 15, NULL);
    worksheet_set_column(worksheet1, 17, 19, 10, NULL);
    worksheet_set_zoom(worksheet1, 88);

    int row = 0;
    int col = 0;
 
    worksheet_write_string(worksheet1, row, col, "Hello me!", NULL);
 
    return workbook_close(workbook);

    return 0;
}