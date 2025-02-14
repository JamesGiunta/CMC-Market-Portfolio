#include "excelWriter.h"
#include <iostream>
#include <xlsxwriter.h>
#include <list>

void ExcelWriter::setupOverviewSheet(lxw_worksheet* worksheet1){
    worksheet_set_column(worksheet1, 0, 2, 10, NULL);
    worksheet_set_column(worksheet1, 5, 8, 12, NULL);
    worksheet_set_column(worksheet1, 9, 9, 15, NULL);
    worksheet_set_column(worksheet1, 10, 10, 12, NULL);
    worksheet_set_column(worksheet1, 11, 11, 15, NULL);
    worksheet_set_column(worksheet1, 12, 13, 12, NULL);
    worksheet_set_column(worksheet1, 15, 15, 15, NULL);
    worksheet_set_column(worksheet1, 17, 19, 10, NULL);
    worksheet_set_zoom(worksheet1, 110);
}

void ExcelWriter::setFinancialSheet(lxw_worksheet* worksheet1){
    worksheet_set_column(worksheet1, 0, 1, 18, NULL);
    worksheet_set_column(worksheet1, 4, 5, 12, NULL);
    worksheet_set_column(worksheet1, 6, 6, 20, NULL);
    worksheet_set_column(worksheet1, 7, 7, 24, NULL);
    worksheet_set_column(worksheet1, 9, 9, 15, NULL);
    worksheet_set_column(worksheet1, 10, 10, 12, NULL);
    worksheet_set_column(worksheet1, 11, 11, 15, NULL);
    worksheet_set_column(worksheet1, 12, 13, 12, NULL);
    worksheet_set_column(worksheet1, 15, 15, 15, NULL);
    worksheet_set_column(worksheet1, 17, 19, 10, NULL);
    worksheet_set_zoom(worksheet1, 110);
}

void ExcelWriter::setUpHeader(lxw_worksheet* worksheet, std::list<std::string> headers) {
    for (const auto& header : headers) {
        worksheet_write_string(worksheet, row, col, header.c_str(), cellFormat);
        col++;
    }
}

void ExcelWriter::writeProfitData(lxw_worksheet* worksheet, std::list<double> profits) {
    for (const auto& profit : profits) {
        worksheet_write_string(worksheet, row, col, std::to_string(profit).c_str(), NULL);
        col++;
    }
}

void ExcelWriter::showLiveShares(lxw_worksheet* worksheet) {
    for (auto liveShare : liveSharesMap) {
        worksheet_write_string(worksheet, row, col, liveShare.first.c_str(), NULL);
        worksheet_write_number(worksheet, row, col + 1, liveShare.second.price, NULL);
        worksheet_write_number(worksheet, row, col + 2, liveShare.second.priceBrought, NULL);
        worksheet_write_number(worksheet, row, col + 3, liveShare.second.price - liveShare.second.priceBrought, NULL);
        worksheet_write_number(worksheet, row, col + 4, ((liveShare.second.price/liveShare.second.priceBrought)-1)*100, NULL);
        worksheet_write_number(worksheet, row, col + 5, liveShare.second.quantity, NULL);
        worksheet_write_number(worksheet, row, col + 6, liveShare.second.cost, NULL);
        worksheet_write_number(worksheet, row, col + 7, liveShare.second.price * liveShare.second.quantity, NULL);
        worksheet_write_number(worksheet, row, col + 8, liveShare.second.profit, NULL);
        worksheet_write_number(worksheet, row, col + 9, (liveShare.second.profit / liveShare.second.cost)*100, NULL);
        row++;
    }
}

void ExcelWriter::writeTransactionData(lxw_worksheet* worksheet) {
    for (auto share : data) {
        worksheet_write_string(worksheet, row, col, dr.dateToString(share.tradeDate).c_str(), NULL);
        worksheet_write_string(worksheet, row, col + 1, dr.orderTypeToString(share.orderType).c_str(), NULL);
        worksheet_write_string(worksheet, row, col + 2, share.ASXCode.c_str(), NULL);
        worksheet_write_number(worksheet, row, col + 3, share.price, NULL);
        worksheet_write_number(worksheet, row, col + 4, share.quantity, NULL);
        row++;
    }
}

void ExcelWriter::writeTransactionDataWithRange(lxw_worksheet* worksheet, std::time_t previousFinancialYearEnd, std::time_t currentFinancialYearEnd) {
    for (auto share : data) {
        if (previousFinancialYearEnd < share.tradeDate && share.tradeDate < currentFinancialYearEnd) {
            worksheet_write_string(worksheet, row, col, dr.dateToString(share.tradeDate).c_str(), NULL);
            worksheet_write_string(worksheet, row, col + 1, dr.orderTypeToString(share.orderType).c_str(), NULL);
            worksheet_write_string(worksheet, row, col + 2, share.ASXCode.c_str(), NULL);
            worksheet_write_number(worksheet, row, col + 3, share.price, NULL);
            worksheet_write_number(worksheet, row, col + 4, share.quantity, NULL);
            row++;
        }
    }
}

std::time_t ExcelWriter::caculateFinanicalYearEndDate(std::tm* date) {
    std::time_t currentMonth = date->tm_mon + 1;
    if (currentMonth >= 1 and currentMonth <= 6) {
        date->tm_mon = 5;
        date->tm_mday = 30;
        date->tm_hour = 23;
        date->tm_min = 59;
        date->tm_sec = 59;
    }
    else {
        date->tm_year = date->tm_year + 1;
        date->tm_mon = 6;
        date->tm_mday = 30;
        date->tm_hour = 23;
        date->tm_min = 59;
        date->tm_sec = 59;
    }
    return std::mktime(date);
}

void ExcelWriter::writeSoldFinancialYearShares(lxw_worksheet* worksheet, std::time_t previousFinancialYearEnd, std::time_t currentFinancialYearEnd, double& financialYearProfit, double& capitalGainsTax) {
    for (auto share : data) {
        if (share.orderType == DataRow::OrderType::SELL && previousFinancialYearEnd < share.tradeDate && share.tradeDate < currentFinancialYearEnd) {
            worksheet_write_string(worksheet, row, col, share.ASXCode.c_str(), NULL);
            worksheet_write_string(worksheet, row, col + 1, std::to_string(share.profit).c_str(), NULL);
            worksheet_write_string(worksheet, row, col + 2, dr.dateToString(share.tradeDate).c_str(), NULL);
            if (share.twelveMonths) {
                worksheet_write_string(worksheet, row, col + 3, "Yes", NULL);
            }
            else {
                worksheet_write_string(worksheet, row, col + 3, "No", NULL);
            }
            worksheet_write_string(worksheet, row, col + 4, std::to_string(share.cgt).c_str(), NULL);
            financialYearProfit += share.profit;
            capitalGainsTax += share.cgt;
            row++;
        }        
    }
}

void ExcelWriter::generateExcelFile() {
    double liveProfit = 0;
    for (auto liveShare : liveSharesMap) {
        liveProfit += liveShare.second.profit;
    }
    double profit = 0;
    for (auto row : data) {
        profit += row.profit;
    }
    double totalProfit = profit + liveProfit;

    lxw_worksheet *worksheet1 = workbook_add_worksheet(workbook, "Overview");
    setupOverviewSheet(worksheet1);

    row = 0;
    col = 0;

    std::list<std::string> headers = {"Total Profit", "Sold Profit", "Live Profit", "", "Share", "Current Price", "Price Brought", "Change", "Change %", "Quantity", "Cost", "Market Value", "Profit", "Profit %", "", "Date", "Type", "Share", "Price", "Quantity"};
    setUpHeader(worksheet1, headers);

    std::list<double> profits = {totalProfit, profit, liveProfit};
    col = 0;
    row++;
    writeProfitData(worksheet1, profits);

    col = 4;
    showLiveShares(worksheet1);

    col = 15;
    row = 1;
    writeTransactionData(worksheet1);

    
    time_t earliestTime = data.back().tradeDate;

    std::time_t t = std::time(0);
    std::tm dateCopy = *std::localtime(&t);
    std::time_t currentFinancialYearEnd = caculateFinanicalYearEndDate(&dateCopy); 

    while (currentFinancialYearEnd > earliestTime) {
        // Calculate the previous financial year
        std::tm tm_current = *std::localtime(&currentFinancialYearEnd);
        tm_current.tm_year -= 1;
        std::time_t previousYearDate = std::mktime(&tm_current);
        std::tm tm_previous = *std::localtime(&previousYearDate);
        std::time_t previousFinancialYearEnd = caculateFinanicalYearEndDate(&tm_previous);
        
        std::tm* tm_year = std::localtime(&currentFinancialYearEnd);
        int year = tm_year->tm_year + 1900;
        int year2 = tm_previous.tm_year + 1900;

        std::string sheetName = std::to_string(year) + "-" + std::to_string(year2) + " Financial Year";
        lxw_worksheet *worksheet2 = workbook_add_worksheet(workbook, sheetName.c_str());
        setFinancialSheet(worksheet2);

        row = 0;
        col = 0;
        std::list<std::string> headers = {"Financial Year Profit", "Capital Gains Tax", "", "Share", "Profit", "Date", "Held For 12 Months", "Capital Gains Tax On Share", "", "Date", "Type", "Share", "Price", "Quantity"};
        setUpHeader(worksheet2, headers);

        row++;
        double financialYearProfit = 0;
        double capitalGainsTax = 0;
        col = 3;
        writeSoldFinancialYearShares(worksheet2, previousFinancialYearEnd, currentFinancialYearEnd, financialYearProfit, capitalGainsTax);

        col = 0;
        row = 1;
        std::list<double> profits = {financialYearProfit, capitalGainsTax};
        writeProfitData(worksheet2, profits);


        col = 9;
        row = 1;
        writeTransactionDataWithRange(worksheet2, previousFinancialYearEnd, currentFinancialYearEnd);

        currentFinancialYearEnd = previousFinancialYearEnd;
    }
}
