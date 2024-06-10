#include "dataProcessing.h"
#include "serviceTest.h"
#include "dataRow.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>


std::time_t ServiceTest::parseDate(const std::string& dateStr) {
    std::tm tm = {};
    std::istringstream dateStream(dateStr);
    dateStream >> std::get_time(&tm, "%d/%m/%Y");
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

std::vector<DataRow> ServiceTest::createTestData() {
    DataRow dr;
    std::vector<std::string> header = {"Account","ASXCode", "Confirmations", "OrderType", "As at Date", "TradeDate", "Settlement Date", "Price", "Quantity", "Brokerage", "GST"};
    std::vector<std::string> row1 = {"", "CBA", "", "Buy", "", "19/03/2024", "", "115.78", "100", "19.95", "1.17"};
    std::vector<std::string> row2 = {"", "360", "", "Sell", "", "01/03/2024", "", "11.30", "300", "11", "0.73"};
    std::vector<std::string> row3 = {"", "360", "", "Buy", "", "04/12/2023", "", "7.78", "300", "10", "0.59"};

    std::vector<std::vector<std::string>> testData1 = {header, row1, row2, row3};
    vectorToCSV(testData1, "testData.csv");

    DataRow expectedRow1 = {"CBA", dr.OrderType::BUY, parseDate("19/03/2024"), double(115.78), 100, double(21.12)};
    DataRow expectedRow2 = {"360", dr.OrderType::SELL, parseDate("01/03/2024"), double(11.30), 300, double(11.73)};
    DataRow expectedRow3 = {"360", dr.OrderType::BUY, parseDate("04/12/2023"), double(7.78), 300, double(10.59)};

    std::vector<DataRow> expectedData = {expectedRow1, expectedRow2, expectedRow3};
    
    return expectedData;
}

void ServiceTest::testLoadCSV() {
    
}

int main() {
    ServiceTest st;
    std::vector<DataRow> expectedData = st.createTestData();
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

    return 0;
}