#pragma once
#include <iostream>
#include "dataRow.h"
#include "dataProcessing.h"
#include "tradeOperations.h"

class CorporateShareActions {
public:
    CorporateShareActions(DataRow& dr, DataProcessing& dp, std::vector<DataRow>& data) :
        dr(dr),
        dp(dp),
        data(data) {}
    std::vector<DataRow> getSpecialCoporateActionsCLI(std::map<std::string, liveShares>& liveSharesMap);
    std::vector<ShareSplitRow> getShareConsolidationCLI();
    std::vector<NameChangeRow> getShareNameChange();
private:
    DataRow& dr;
    DataProcessing& dp;
    std::vector<DataRow>& data;
};