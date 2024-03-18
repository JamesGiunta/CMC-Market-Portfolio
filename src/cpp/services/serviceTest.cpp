#include "dataProcessing.h"
#include <iostream>
#include <iomanip>

int main() {
    DataProcessing dp;
    std::vector<DataRow> data = dp.loadCSV("../../../resources/Confirmation2.csv");

    for (const DataRow& row : data) {
        std::cout << "ASXCode: " << row.ASXCode << ", "
                  << "OrderType: " << (row.orderType == BUY ? "BUY" : "SELL") << ", "
                  << "Price: " << row.price << ", "
                  << "Fee: " << row.fee << std::endl
                  << "TradeDate: " << std::put_time(&row.TradeDate, "%d/%m/%Y") << std::endl;
    }

    return 0;
}