#pragma once
#include <string>
#include "tradeOperations.h"

class DataRetrieval {
public:
    std::string getRequest(std::string ASXCode);
    void getLivePrices(std::pair<const std::string, liveShares>& pair);
private:
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};