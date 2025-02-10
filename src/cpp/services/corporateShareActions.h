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
    void getSpecialCoporateActionsCLI();
    void getShareConsolidationCLI();
    void getShareNameChange();
private:
    DataRow& dr;
    DataProcessing& dp;
    std::vector<DataRow>& data;
};