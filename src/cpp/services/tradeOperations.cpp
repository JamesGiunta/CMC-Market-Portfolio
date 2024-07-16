#include "tradeOperations.h"
#include "dataRow.h"
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>
#include <cmath>

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

        int quantity = liveShare.second.quantity;
        for (auto& dataRow: data) {
            if (dataRow.orderType==DataRow::BUY) {
                if (liveShare.first == dataRow.ASXCode) {
                    std::cout<<dataRow.quantity<<std::endl;
                    if (dataRow.quantity <= quantity) {
                        cost += (dataRow.price * dataRow.quantity) + dataRow.fee;
                        quantity = quantity - dataRow.quantity;
                    }
                    // If the buy order quantity is greater than the live quantity then calculate the profit based on the percentage of the buy order quantity
                    else {
                        double percentage = quantity / (double)dataRow.quantity;  
                        cost += (dataRow.price * quantity) + (dataRow.fee * percentage);
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
    }
}

bool operator==(const liveShares& lhs, const liveShares& rhs) {
    const double epsilon = 1e-6; // Tolerance for floating-point comparison
    return std::abs(lhs.price - rhs.price) < epsilon && std::abs(lhs.profit - rhs.profit) < epsilon && lhs.quantity == rhs.quantity;
}