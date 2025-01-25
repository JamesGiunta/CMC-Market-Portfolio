#include "excelWriter.h"
#include <iostream>
#include <xlsxwriter.h>
#include <list>

void ExcelWriter::generateExcelFile(const std::vector<DataRow>& data, std::map<std::string, liveShares>& liveSharesMap, DataRow& dr) {
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
    lxw_worksheet *worksheet1 = workbook_add_worksheet(workbook, "Overview");
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
    std::list<double> profits = {totalProfit, profit, liveProfit};
    row++;
    col = 0;
    for (const auto& profit : profits) {
        worksheet_write_string(worksheet1, row, col, std::to_string(profit).c_str(), NULL);
        col++;
    }
    col = 4;
    for (auto liveShare : liveSharesMap) {
        worksheet_write_string(worksheet1, row, col, liveShare.first.c_str(), NULL);
        worksheet_write_number(worksheet1, row, col + 1, liveShare.second.price, NULL);
        worksheet_write_number(worksheet1, row, col + 2, liveShare.second.priceBrought, NULL);
        worksheet_write_number(worksheet1, row, col + 3, liveShare.second.price - liveShare.second.priceBrought, NULL);
        worksheet_write_number(worksheet1, row, col + 4, ((liveShare.second.price/liveShare.second.priceBrought)-1)*100, NULL);
        worksheet_write_number(worksheet1, row, col + 5, liveShare.second.quantity, NULL);
        worksheet_write_number(worksheet1, row, col + 6, liveShare.second.cost, NULL);
        worksheet_write_number(worksheet1, row, col + 7, liveShare.second.price * liveShare.second.quantity, NULL);
        worksheet_write_number(worksheet1, row, col + 8, liveShare.second.profit, NULL);
        worksheet_write_number(worksheet1, row, col + 9, (liveShare.second.profit / liveShare.second.cost)*100, NULL);
        row++;
    }
    col = 15;
    row = 1;
    for (auto share : data) {
        worksheet_write_string(worksheet1, row, col, dr.dateToString(share.tradeDate).c_str(), NULL);
        worksheet_write_string(worksheet1, row, col + 1, dr.orderTypeToString(share.orderType).c_str(), NULL);
        worksheet_write_string(worksheet1, row, col + 2, share.ASXCode.c_str(), NULL);
        worksheet_write_number(worksheet1, row, col + 3, share.price, NULL);
        worksheet_write_number(worksheet1, row, col + 4, share.quantity, NULL);
        row++;
    }
    // time_t earliestTime = data.back().tradeDate;

    // std::time_t t = std::time(0);
    // std::tm* date = std::localtime(&t);
    // std::time_t currentMonth = date->tm_mon + 1;
    // if (currentMonth >= 1 and currentMonth <= 6) {
    //     date->tm_mon = 5;
    //     date->tm_mday = 30;
    //     date->tm_hour = 23;
    //     date->tm_min = 59;
    //     date->tm_sec = 59;
    // }
    // else {
    //     date->tm_year = date->tm_year + 1;
    //     date->tm_mon = 6;
    //     date->tm_mday = 30;
    //     date->tm_hour = 23;
    //     date->tm_min = 59;
    //     date->tm_sec = 59;
    // }
    // std::time_t currentTime = std::mktime(date);
    // std::cout << std::asctime(date) << std::endl;

    // while (currentTime > earliestTime) {

    // }


    workbook_close(workbook);
}