#pragma once
#include "dataRow.h"
#include "tradeOperations.h"
#include <xlsxwriter.h>
#include <list>


class ExcelWriter {
public:
    ExcelWriter(DataRow& dr, const std::string& fullPath, const std::vector<DataRow>& data, std::map<std::string, liveShares>& liveSharesMap) :
        dr(dr),
        fullPath(fullPath),
        data(data),
        liveSharesMap(liveSharesMap) {
        workbook = workbook_new(fullPath.c_str());
        cellFormat = workbook_add_format(workbook);
        format_set_bold(cellFormat);
    }

    ~ExcelWriter() {
        if (workbook){
            workbook_close(workbook);
        }
    }
    void generateExcelFile();

private:
    DataRow& dr;
    const std::string fullPath;
    lxw_workbook* workbook;
    lxw_format* cellFormat;
    const std::vector<DataRow>& data;
    std::map<std::string, liveShares>& liveSharesMap;
    std::stringstream ss;
    int col; 
    int row;

    void setupOverviewSheet(lxw_worksheet* worksheet1);
    void setFinancialSheet(lxw_worksheet* worksheet1);
    void setUpHeader(lxw_worksheet* worksheet, std::list<std::string> headers);
    void writeProfitData(lxw_worksheet* worksheet, std::list<std::string> profits);
    void showLiveShares(lxw_worksheet* worksheet);
    void writeTransactionData(lxw_worksheet* worksheet);
    void writeTransactionDataWithRange(lxw_worksheet* worksheet, std::time_t previousFinancialYearEnd, std::time_t currentFinancialYearEnd);
    std::time_t caculateFinanicalYearEndDate(std::tm* date);
    void writeSoldFinancialYearShares(lxw_worksheet* worksheet, std::time_t previousFinancialYearEnd, std::time_t currentFinancialYearEnd, long long& financialYearProfit, long long& capitialGainsTax);
};