#include "tradeOperations.h"
#include "dataRow.h"
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

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