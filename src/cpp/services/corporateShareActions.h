#include <iostream>
#include "dataRow.h"
#include "dataProcessing.h"
#include "tradeOperations.h"
#
class CoparateShareActions {
public:
    CoparateShareActions(DataRow& dr, DataProcessing& dp, std::vector<DataRow>& data) :
        dr(dr),
        dp(dp),
        data(data) {}
    std::vector<DataRow> getSpecialCoporateActionsCLI();
    std::vector<ShareSplitRow> getShareConsolidationCLI();
    std::vector<NameChangeRow> getShareNameChange();
private:
    DataRow& dr;
    DataProcessing& dp;
    std::vector<DataRow>& data;
};