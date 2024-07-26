#include "excelWriter.h"
#include <iostream>
#include <xlsxwriter.h>
#include <list>

void ExcelWriter::generateExcelFile(const std::vector<DataRow>& data, std::map<std::string, liveShares>& liveSharesMap) {
    double liveProfit = 0;
    for (auto liveShare : liveSharesMap) {
        liveProfit += liveShare.second.profit;
    }
    double profit = 0;
    for (auto row : data) {
        profit += row.profit;
    }
    double totalProfit = profit + liveProfit;

    lxw_workbook *workbook  = workbook_new("Report.xlsx");
    lxw_worksheet *worksheet1 = workbook_add_worksheet(workbook, NULL);
    worksheet_set_column(worksheet1, 0, 2, 10, NULL);
    worksheet_set_column(worksheet1, 5, 8, 12, NULL);
    worksheet_set_column(worksheet1, 9, 9, 15, NULL);
    worksheet_set_column(worksheet1, 10, 10, 12, NULL);
    worksheet_set_column(worksheet1, 11, 11, 15, NULL);
    worksheet_set_column(worksheet1, 12, 13, 12, NULL);
    worksheet_set_column(worksheet1, 15, 15, 15, NULL);
    worksheet_set_column(worksheet1, 17, 19, 10, NULL);
    worksheet_set_zoom(worksheet1, 88);

    int row = 0;
    int col = 0;

    std::list<std::string> headers = {"Total Profit", "Sold Profit", "Live Profit", "", "Share", "Current Price", "Price Brought", "Change", "Change %", "Quantity", "Cost", "Market Value", "Profit", "Profit %", "", "Date", "Type", "Share", "Price", "Quantity"};
    for (const auto& header : headers) {
        worksheet_write_string(worksheet1, row, col, header.c_str(), NULL);
        col++;
    }

    col = 0;
    row = 1;
    worksheet_write_string(worksheet1, row, col, std::to_string(totalProfit).c_str(), NULL);
    row = 2;
    
    std::cout<<liveProfit<<std::endl;
    std::cout<<profit<<std::endl;
    workbook_close(workbook);
}