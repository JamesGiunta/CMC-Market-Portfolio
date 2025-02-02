#include "dataRow.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const DataRow& row) {
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", std::localtime(&row.tradeDate));
    os << "Share Code:" << row.ASXCode << " Order Type:" << (row.orderType == DataRow::BUY ? "BUY" : "SELL") << " Trade Date:" << buffer << " Price:" << row.price << " Quantity:" << row.quantity << " Fee:" << row.fee << " Profit:" << row.profit << " CGT:" << row.cgt << std::endl;
    return os;
}

bool operator==(const DataRow& lhs, const DataRow& rhs) {
    const double epsilon = 1e-6; // Tolerance for floating-point comparison
    return lhs.ASXCode == rhs.ASXCode &&
            lhs.orderType == rhs.orderType &&
            lhs.tradeDate == rhs.tradeDate &&
            lhs.settlementDate == rhs.settlementDate &&
           std::abs(lhs.price - rhs.price) < epsilon &&
           lhs.quantity == rhs.quantity &&
           std::abs(lhs.fee - rhs.fee) < epsilon && std::abs(lhs.profit - rhs.profit) < epsilon && 
           std::abs(lhs.cgt - rhs.cgt) < epsilon;
}

bool DataRow::operator<(const DataRow& obj) const {
    if (tradeDate == obj.tradeDate) { 
        // If trade dates are the same, compare by sequence number so that the buy order comes before the sell order
        return seq > obj.seq;
    }
    return tradeDate < obj.tradeDate;
}

bool DataRow::descending(const DataRow& obj1, const DataRow& obj2) {
        if (obj1.tradeDate == obj2.tradeDate) {
            // If trade dates are the same, compare by sequence number so that the sell order comes before the buy order
            return obj1.seq < obj2.seq;
        }
        return obj1.tradeDate > obj2.tradeDate;
}

std::string DataRow::orderTypeToString(OrderType type) {
    switch (type) {
        case OrderType::BUY:
            return "BUY";
        case OrderType::SELL:
            return "SELL";
    
    default:
        std::runtime_error("Invalid order type");
        return "";
    }
}

std::string DataRow::dateToString(std::time_t date) {
    char buffer[80];
    std::strftime(buffer, sizeof(buffer), "%d/%m/%Y", std::localtime(&date));
    return buffer;
}