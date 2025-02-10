#include "corporateShareActions.h"

void CoparateShareActions::getSpecialCoporateActionsCLI(){
    char response;
    std::vector<DataRow> userEnteredData;
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
            userEnteredData.push_back(row);
            std::cout << "Do you have another share takeover to enter? (Y/N): ";
            std::cin >> response;
            if (response == 'N' || response == 'n') {
                finished = true;
            }  
        }
    }
    data.insert(data.end(), userEnteredData.begin(), userEnteredData.end());
}

void CoparateShareActions::getShareConsolidationCLI(){
    char response;
    std::cout << "Have you incurred any share splits (Y/N): ";
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
            for (DataRow& row : data) {
                if (row.ASXCode == ASXCode && row.tradeDate < date) {
                    row.quantity *= ratio;
                    row.price /= ratio;
                }
            }
            std::cout << "Do you have another share split to enter? (Y/N): ";
            std::cin >> response;
            if (response == 'N' || response == 'n') {
                finished = true;
            }  
        }
    }
}

void CoparateShareActions::getShareNameChange(){
    char response;
    std::cout << "Have you incurred any share name changes (Y/N): ";
    std::cin >> response;
    std::string ASXCode;
    std::string newASXCode;
    std::string dateString;
    std::time_t date;
    if (response == 'Y' || response == 'y') {
        bool finished = false;
        while (!finished) {
            std::cout << "What was the share's ASX code: ";
            std::cin >> ASXCode;
            for (std::size_t i = 0; i < ASXCode.length(); i++) {
                ASXCode[i] = toupper(ASXCode[i]);
            }
            std::cout << "What is the new ASX code: ";
            std::cin >> newASXCode;
            for (std::size_t i = 0; i < newASXCode.length(); i++) {
                newASXCode[i] = toupper(newASXCode[i]);
            }
            std::cout << "When did the share name change occur (dd/mm/yyyy): ";
            std::cin >> dateString;
            date = dp.regexDate(dateString);
            for (DataRow& row : data) {
                if (row.ASXCode == ASXCode && row.tradeDate < date) {
                    row.ASXCode = newASXCode;
                }
            }
            std::cout << "Do you have another share name change to enter? (Y/N): ";
            std::cin >> response;
            if (response == 'N' || response == 'n') {
                finished = true;
            }  
        }
    }
}

