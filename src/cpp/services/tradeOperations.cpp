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

void TradeOperations::calculateCGT(DataRow& buyOrder, DataRow& sellOrder, long long& cost, int quantityUsed) {
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

    long long total = ((sellOrder.consideration * quantityUsed) + (sellOrder.quantity/2))/sellOrder.quantity;
    long long profit = total - cost;

    if (buyDate <= sellDatePreviousYearDay && profit > 0) {
        sellOrder.cgt += (profit + 1) / 2;
    } 
    else {
        sellOrder.cgt += profit;
    }
    sellOrder.profit += profit;
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
        long long cost = 0;
        long long sharePrice = 0;

        int quantity = liveShare.second.quantity;
        for (auto& dataRow: data) {
            if (dataRow.orderType==DataRow::BUY) {
                if (liveShare.first == dataRow.ASXCode) {
                    if (dataRow.quantity <= quantity) {
                        cost += (((dataRow.price * dataRow.quantity)+50)/100)+ dataRow.fee;
                        quantity = quantity - dataRow.quantity;
                        sharePrice += dataRow.price * dataRow.quantity;
                    }
                    // If the buy order quantity is greater than the live quantity then calculate the profit based on the percentage of the buy order quantity
                    else {
                        cost += (((dataRow.price * dataRow.quantity)+50)/100) + ((dataRow.fee * quantity + dataRow.quantity / 2)) / dataRow.quantity;
                        sharePrice += dataRow.price * quantity;
                        quantity = 0;
                    }
                } 
                if (quantity == 0) {
                    break;
                }
            }      
        }
        liveShare.second.profit = (liveShare.second.price * liveShare.second.quantity + 50)/100 - cost;
        liveShare.second.cost = cost;
        liveShare.second.priceBrought = (sharePrice + (liveShare.second.quantity / 2)) / liveShare.second.quantity;
    }
}

void TradeOperations::calculateProfit(std::vector<DataRow>& data){
    std::sort(data.begin(), data.end());
    for (auto& row: data){
        row.tempQuantity = row.quantity;
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
                            long long tempCost = ((buyOrder.consideration * buyOrder.tempQuantity) + (buyOrder.quantity/2))/buyOrder.quantity;
                            calculateCGT(buyOrder, sellOrder, tempCost, buyOrder.tempQuantity);
                            cost += tempCost;
                        }
                        quantity -= buyOrder.tempQuantity;
                        buyOrder.tempQuantity = 0;
                    }
                    // If the buy order quantity is greater than the sell order quantity then calculate the profit based on the percentage of the buy order quantity
                    else {
                        long long tempCost = ((buyOrder.consideration * quantity) + (buyOrder.quantity/2))/buyOrder.quantity;
                        calculateCGT(buyOrder, sellOrder, cost, quantity);
                        cost += tempCost;
                        buyOrder.tempQuantity -= quantity;
                        quantity = 0;
                    }
                }
                if (quantity == 0) {
                    break;
                }
            }
            sellOrder.profit = sellOrder.consideration - cost;
        }
    }
}