#include <iostream>
#include "dataRow.h"
#include "dataProcessing.h"
class CoparateShareActions {
public:
    std::vector<DataRow> getSpecialCoporateActionsCLI(DataRow& dr, DataProcessing& dp);
    std::vector<DataRow> getShareConsolidation(DataRow& dr, DataProcessing& dp, std::vector<DataRow>& data);
};