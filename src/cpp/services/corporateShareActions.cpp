#include "corporateShareActions.h"

void CoparateShareActions::getSpecialCoporateActionsCLI(DataRow& dr, DataProcessing& dp){
    std::cout << "Have you incurred any Share Takeovers? (Y/N): ";
    char response;
    std::vector<DataRow> data;
    DataRow row;
    double price;
    int quantity;
    std::cin >> response;
    if (response == 'Y') {
        std::string ASXCode;
        std::string tradeDateString;
        std::time_t tradeDate;
        std::string settlementDateString;
        std::time_t settlementDate;
        bool finished = false;
        while (!finished) {
            std::cout << "What was the share's ASX code: ";
            std::cin >> ASXCode;
            for (std::size_t i = 0; i < ASXCode.length(); i++) {
                ASXCode[i] = toupper(ASXCode[i]);
            }
            std::cout << "What was the trade date (dd/mm/yyyy): ";
            std::cin >> tradeDateString;
            dr.tradeDate = dp.regexDate(tradeDateString);

            std::cout << "What was the settlement date (dd/mm/yyyy): ";
            std::cin >> settlementDateString;
            dr.settlementDate = dp.regexDate(settlementDateString);
            std::cout << "What was the price of the share: ";
            std::cin >> price;
            std::cout << "What was the quantity of the share: ";
            std::cin >> quantity;
            row.ASXCode = ASXCode;
            row.orderType = DataRow::OrderType::SELL;
            row.tradeDate = tradeDate;
            row.settlementDate = settlementDate;
            row.price = price;
            row.quantity = quantity;
            row.fee = 0;
            row.profit = 0;
            row.seq = 0;
            data.push_back(row);
        }

    }

}

void CoparateShareActions::getShareConsolidation(DataRow& dr){
    std::cout << "Have you incurred any share splits (Y/N)";

}

