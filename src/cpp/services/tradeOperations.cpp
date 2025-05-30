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

void TradeOperations::calculateCGTPercentage(DataRow& buyOrder, DataRow& sellOrder) {
    //Takes way a day and 12 months and sets hour,min,sec same for buy and sell order
    std::tm tmSellDate = *std::localtime(&sellOrder.settlementDate);
    tmSellDate.tm_year -= 1;
    tmSellDate.tm_hour = 0;
    tmSellDate.tm_min = 0;
    tmSellDate.tm_sec = 0;
    std::time_t sellDatePreviousYearDay = std::mktime(&tmSellDate);

    std::tm tmBuyDate = *std::localtime(&buyOrder.settlementDate);
    tmBuyDate.tm_mday += 1;
    tmBuyDate.tm_hour = 0;
    tmBuyDate.tm_min = 0;
    tmBuyDate.tm_sec = 0;
                        
    std::time_t buyDate = std::mktime(&tmBuyDate);

    if (buyDate <= sellDatePreviousYearDay) {
        sellOrder.twelveMonths = true;
    }
}

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
        row.tempFee = row.fee;
    }
    for (auto& sellOrder: data) {
        long long cost = 0;
        if (sellOrder.orderType == DataRow::SELL) {
            int quantity = sellOrder.quantity;
            for (auto& buyOrder: data) {
                if ((buyOrder.orderType == DataRow::BUY) && (buyOrder.ASXCode == sellOrder.ASXCode)) {
                    if (buyOrder.tempQuantity <= quantity) {
                        if (buyOrder.tempQuantity != 0) {
                            // Calculate profit, while rounding to the nearest cent
                            cost += ((buyOrder.consideration * buyOrder.tempQuantity) + (buyOrder.quantity/2))/buyOrder.quantity;
                            calculateCGTPercentage(buyOrder, sellOrder);
                        }
                    
                        quantity -= buyOrder.tempQuantity;
                        buyOrder.tempQuantity = 0;
                    }
                    // If the buy order quantity is greater than the sell order quantity then calculate the profit based on the percentage of the buy order quantity
                    else {
                        double percentage = quantity / (double)buyOrder.tempQuantity;  
                        calculateCGTPercentage(buyOrder, sellOrder);
                        double fee = buyOrder.tempFee * percentage;
                        cost += ((buyOrder.consideration * quantity) + (buyOrder.quantity/2))/buyOrder.quantity;
                        buyOrder.tempQuantity -= quantity;
                        buyOrder.tempFee -= fee;
                        quantity = 0;
                    }
                }
                if (quantity == 0) {
                    break;
                }
            }
            sellOrder.profit = (sellOrder.consideration - cost)/100.00;
            if (sellOrder.twelveMonths && sellOrder.profit > 0) {
                sellOrder.cgt = sellOrder.profit * 0.5;
            }
            else {
                sellOrder.cgt = sellOrder.profit;
            }
        }
    }
}