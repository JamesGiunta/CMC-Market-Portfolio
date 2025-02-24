#pragma once
#include <iostream>
#include <map>
#include "dataRow.h"
#include "dataProcessing.h"
#include "tradeOperations.h"
#include "dataRetrieval.h"

class CorporateShareActions {
public:
    CorporateShareActions(DataRow& dr, DataRetrieval& drr, DataProcessing& dp, std::vector<DataRow>& data, std::map<std::string, liveShares>& liveSharesMap) :
        dr(dr),
        drr(drr),
        dp(dp),
        data(data),
        liveSharesMap(liveSharesMap) {}
    std::vector<DataRow> getSpecialCoporateActionsCLI();
    std::vector<ShareSplitRow> getShareConsolidationCLI();
    std::vector<NameChangeRow> getShareNameChangeCLI();
    void saveSpecialCoporateActions(const std::string &ASXCode, const double price, const std::time_t &date);
    void saveShareConsolidation(const std::string &ASXCode, const double ratio, const std::time_t &date);
    void saveShareNameChange(const std::string &oldASXCode, const std::string &newASXCode, const std::time_t &date);
private:
    DataRow& dr;
    DataRetrieval drr;
    DataProcessing& dp;
    std::vector<DataRow>& data;
    std::map<std::string, liveShares>& liveSharesMap;
};