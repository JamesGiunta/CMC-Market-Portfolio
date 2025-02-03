#pragma once
#include "dataRow.h"
#include "tradeOperations.h"
#include <xlsxwriter.h>
#include <list>


class ExcelWriter {
public:
    void generateExcelFile(const std::vector<DataRow>& data, std::map<std::string, liveShares>& liveSharesMap, DataRow& dr);
private:
    void setupOverviewSheet(lxw_worksheet* worksheet1);
    void setFinancialSheet(lxw_worksheet* worksheet1);
    void setUpHeader(lxw_worksheet* worksheet, std::list<std::string> headers, int& row, int& col, lxw_format* cellFormat);
    void writeProfitData(lxw_worksheet* worksheet, std::list<double> profits, int& row, int& col);
    void showLiveShares(lxw_worksheet* worksheet, std::map<std::string, liveShares>& liveSharesMap, int& row, int& col);
    void writeTransactionData(lxw_worksheet* worksheet, const std::vector<DataRow>& data, int& row, int& col, DataRow& dr);
    void writeTransactionDataWithRange(lxw_worksheet* worksheet, const std::vector<DataRow>& data, int& row, int& col, DataRow& dr, std::time_t previousFinancialYearEnd, std::time_t currentFinancialYearEnd);
    std::time_t caculateFinanicalYearEndDate(std::tm* date);
    void writeSoldFinancialYearShares(lxw_worksheet* worksheet, const std::vector<DataRow>& data, int& row, int& col, std::time_t previousFinancialYearEnd, std::time_t currentFinancialYearEnd, DataRow& dr, double& financialYearProfit, double& capitialGainsTax);
};