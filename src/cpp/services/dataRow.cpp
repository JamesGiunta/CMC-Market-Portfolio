#include "dataRow.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const DataRow& row) {
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d-%m-%Y", std::localtime(&row.tradeDate));
    os << "Share Code:" << row.ASXCode << " Order Type:" << (row.orderType == DataRow::BUY ? "BUY" : "SELL") << " Trade Date:" << buffer << " Price:" << row.price << " Quantity:" << row.quantity << " Fee:" << row.fee << std::endl;
    return os;
}

bool operator==(const DataRow& lhs, const DataRow& rhs) {
    return lhs.ASXCode == rhs.ASXCode && lhs.orderType == rhs.orderType && lhs.tradeDate == rhs.tradeDate && lhs.price == rhs.price && lhs.quantity == rhs.quantity && lhs.fee == rhs.fee;
}