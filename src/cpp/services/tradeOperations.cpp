#include "tradeOperations.h"
#include "dataRow.h"
#include <vector>
#include <algorithm>
#include <map>
#include <iostream>

std::map<std::string, int> TradeOperations::createLiveDataVector(std::vector<DataRow>& data){
    std::map<std::string, int> liveSharesMap;
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
            liveSharesMap[currentASXCode] = currentQuantity;
        } 
        else {
            liveSharesMap[currentASXCode] += currentQuantity;
        }
    }
    for (auto it = liveSharesMap.begin(); it != liveSharesMap.end(); ) {
        if (it->second == 0) {
            it = liveSharesMap.erase(it);
        }
        else {
            it++;
        }
    }
    return liveSharesMap;
}

