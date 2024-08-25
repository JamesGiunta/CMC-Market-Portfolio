#include "tradeOperations.h"
#include "dataRow.h"
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <cmath>

bool operator==(const liveShares& lhs, const liveShares& rhs) {
    const double epsilon = 1e-6; // Tolerance for floating-point comparison
    return std::abs(lhs.price - rhs.price) < epsilon && std::abs(lhs.profit - rhs.profit) < epsilon && lhs.quantity == rhs.quantity && (lhs.cost - rhs.cost) < epsilon && (lhs.priceBrought - rhs.priceBrought) < epsilon;
}

//TODO offline check
std::map<std::string, liveShares> TradeOperations::createLiveDataVector(std::vector<DataRow>& data){
    std::map<std::string, liveShares> liveSharesMap;
    std::sort(data.begin(), data.end());
    std::string currentASXCode = "";
    for (auto it = data.begin(); it != data.end(); ++it) {
        int currentQuantity = 0;
        currentASXCode = it->ASXCode;
        if (it->orderType == DataRow::BUY) {
            currentQuantity += it->quantity;
        } 
        else {
            currentQuantity -= it->quantity;
        }

        if (liveSharesMap.find(currentASXCode) == liveSharesMap.end()) {
            liveSharesMap[currentASXCode].quantity = currentQuantity;
        } 
        else {
            liveSharesMap[currentASXCode].quantity += currentQuantity;
        }
    }
    for (auto it = liveSharesMap.begin(); it != liveSharesMap.end(); ) {
        if (it->second.quantity == 0) {
            it = liveSharesMap.erase(it);
        }
        else {
            it++;
        }
    }
    return liveSharesMap;
}

void TradeOperations::calculateLiveProfit(std::map<std::string, liveShares>& liveSharesMap, std::vector<DataRow>& data){
    std::sort(data.begin(), data.end(), DataRow::descending);
    for (auto& liveShare: liveSharesMap) {
        double cost = 0;
        double fee = 0;

        int quantity = liveShare.second.quantity;
        for (auto& dataRow: data) {
            if (dataRow.orderType==DataRow::BUY) {
                if (liveShare.first == dataRow.ASXCode) {
                    if (dataRow.quantity <= quantity) {
                        cost += (dataRow.price * dataRow.quantity) + dataRow.fee;
                        quantity = quantity - dataRow.quantity;
                        fee += dataRow.fee;
                    }
                    // If the buy order quantity is greater than the live quantity then calculate the profit based on the percentage of the buy order quantity
                    else {
                        double percentage = quantity / (double)dataRow.quantity;  
                        cost += (dataRow.price * quantity) + (dataRow.fee * percentage);
                        fee += dataRow.fee * percentage;
                        quantity = 0;
                    }
                } 
                if (quantity == 0) {
                    break;
                }
            }      
        }
        liveShare.second.profit = (liveShare.second.price * liveShare.second.quantity) - cost;
        // Rounds to 2 decimal places
        liveShare.second.profit = round(liveShare.second.profit*100)/100;
        liveShare.second.cost = cost;
        liveShare.second.priceBrought = (cost - fee)/ liveShare.second.quantity;
    }
}

void TradeOperations::calculateProfit(std::vector<DataRow>& data){
    std::sort(data.begin(), data.end());
    for (auto& row: data){
        row.tempQuantity = row.quantity;
    }
    for (auto& sellOrder: data) {
        double cost = 0;
        if (sellOrder.orderType == DataRow::SELL) {
            int quantity = sellOrder.quantity;
            for (auto& buyOrder: data) {
                if ((buyOrder.orderType == DataRow::BUY) && (buyOrder.ASXCode == sellOrder.ASXCode)) {
                    if (buyOrder.tempQuantity <= quantity) {
                        cost += (buyOrder.price * buyOrder.tempQuantity) + buyOrder.fee;
                        quantity = quantity - buyOrder.tempQuantity;
                        buyOrder.tempQuantity -= buyOrder.tempQuantity;
                    }
                    // If the buy order quantity is greater than the sell order quantity then calculate the profit based on the percentage of the buy order quantity
                    else {
                        double percentage = quantity / (double)buyOrder.tempQuantity;  
                        cost += (buyOrder.price * quantity) + (buyOrder.fee * percentage);
                        quantity = 0;
                        buyOrder.tempQuantity -= quantity;
                    }
                }
                if (quantity == 0) {
                    break;
                }
            }
            sellOrder.profit = (sellOrder.price * sellOrder.quantity) - cost - sellOrder.fee;
            // Rounds to 2 decimal places
            sellOrder.profit = round(sellOrder.profit*100)/100;
        }
    }
}