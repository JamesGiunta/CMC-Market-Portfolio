#pragma once
#include <string>
#include "tradeOperations.h"

class DataRetrieval {
public:
    std::string getRequest(std::string ASXCode);
    void getLivePrices(std::pair<const std::string, liveShares>& pair);
    void cacheSpecialCorporateActions(std::vector<ShareSplitRow>& shareSplitVector, std::vector<NameChangeRow>& shareNameChangeVector, std::vector<DataRow>& shareTakeOverVector);
    void loadCachedData(std::vector<DataRow>& data);
    void clearCache();
private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
};