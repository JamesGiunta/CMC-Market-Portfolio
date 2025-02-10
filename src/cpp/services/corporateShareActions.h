#include <iostream>
#include "dataRow.h"
#include "dataProcessing.h"
class CoparateShareActions {
public:
    CoparateShareActions(DataRow& dr, DataProcessing& dp, std::vector<DataRow>& data) :
        dr(dr),
        dp(dp),
        data(data) {}
    void getSpecialCoporateActionsCLI();
    std::vector<DataRow> getShareConsolidationCLI();
private:
    DataRow& dr;
    DataProcessing& dp;
    std::vector<DataRow>& data;
};