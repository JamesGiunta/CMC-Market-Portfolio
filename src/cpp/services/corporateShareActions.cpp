#include "corporateShareActions.h"

std::vector<DataRow> CoparateShareActions::getSpecialCoporateActionsCLI(DataRow& dr, DataProcessing& dp){
    char response;
    std::vector<DataRow> data;
    DataRow row;
    double price;
    int quantity;
    std::cout << "Have you incurred any Share Takeovers? (Y/N): ";
    std::cin >> response;
    if (response == 'Y' || response == 'y') {
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
            tradeDate = dp.regexDate(tradeDateString);
            std::cout << "What was the settlement date (dd/mm/yyyy): ";
            std::cin >> settlementDateString;
            settlementDate = dp.regexDate(settlementDateString);
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
            row.cgt = 0;
            data.push_back(row);
            std::cout << "Do you have another share takeover to enter? (Y/N): ";
            std::cin >> response;
            if (response == 'N' || response == 'n') {
                finished = true;
            }  
        }
    }
    return data;
}

std::vector<DataRow> CoparateShareActions::getShareConsolidation(DataRow& dr, DataProcessing& dp, std::vector<DataRow>& data){
    char response;
    std::vector<ShareSplit> shareSplit;
    ShareSplit row;
    std::cout << "Have you incurred any share splits (Y/N)";
    std::cin >> response;
    int ratio;
    std::string dateString;
    std::time_t date;
    if (response == 'Y' || response == 'y') {
        std::string ASXCode;
        bool finished = false;
        while (!finished) {
            std::cout << "What was the share's ASX code: ";
            std::cin >> ASXCode;
            for (std::size_t i = 0; i < ASXCode.length(); i++) {
                ASXCode[i] = toupper(ASXCode[i]);
            }
            std::cout << "What was the ratio of the share split (1:10) converts 10 shares to 100 (1:x): ";
            std::cin >> ratio;
            std::cout << "When did the share split occur (dd/mm/yyyy): ";
            std::cin >> dateString;
            date = dp.regexDate(dateString);
            row.ASXCode = ASXCode;
            row.ratio = ratio;
            row.tradeDate = date;
            shareSplit.push_back(row);
            std::cout << "Do you have another share split to enter? (Y/N): ";
            std::cin >> response;
            if (response == 'N' || response == 'n') {
                finished = true;
            }  
        }
    }
    // TODO updates qualtity of shares in data vector and test
    return data;

}

