#include "highPrecisionMoney.h"
#include <stdexcept>
#include <iostream>

long long HighPrecisionMoney::stringToNumberInCents(std::string& str) {
    bool round = false;
    size_t dotPos = str.find('.');
    if (dotPos == std::string::npos) {
        // Convert to cents
        str = str + "00";
    }
    else {
        int pos = str.find(".");
        // If there is no digit after the decimal point, add two zeros
        if (str.length() - pos == 1) {             
            str = str + "00";
        }
        // If there is one digit after the decimal point, add one zero
        else if (str.length() - pos == 2) {
            str = str + "0";
        }
        
        // If there is three or more digits after the decimal point and the third digit is greater than 5, round up
        else if (str.length() - pos > 3) {
            char thirdCharAfterPos = str[pos + 3];
            if (thirdCharAfterPos >= '5') {
                round = true;
            }
            str = str.substr(0, pos + 3);
        }
        // Remove the decimal point
        str.erase(pos, 1);
    }
    try {
        long long numberValue = std::stoll(str);
        if (round) {
            numberValue += 1;
        }
        return numberValue;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid consideration value: " << str << std::endl;
        return -1;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Consideration value out of range: " << str << std::endl;
        return -1;
    }
}   

long long HighPrecisionMoney::stringToNumberInHundredsOfCents(std::string& str) {
    bool round = false;
    size_t dotPos = str.find('.');
    if (dotPos == std::string::npos) {
        // Convert to hundreds of cents
        str = str + "0000";
    }
    else {
    size_t pos = str.find('.');
        // If there is no digit after the decimal point, add four zeros
        if (str.length() - pos == 1) {             
            str = str + "0000";
        }
        // If there is one digit after the decimal point, add three zero
        else if (str.length() - pos == 2) {
            str = str + "000";
        }

        // If there is two digit after the decimal point, add two zero
        else if (str.length() - pos == 3) {
            str = str + "00";
        }

        // If there is three digit after the decimal point, add one zero
        else if (str.length() - pos == 4) {
            str = str + "0";
        }
        
        // If there is five or more digits after the decimal point and the fifth digit is greater than 5, round up
        else if (str.length() - pos > 5) {
            char thirdCharAfterPos = str[pos + 5];
            if (thirdCharAfterPos >= '5') {
                round = true;
            }
            str = str.substr(0, pos + 5);
        }
        // Remove the decimal point
        str.erase(pos, 1);
    }
    try {
        long long numberValue = std::stoll(str);
        if (round) {
            numberValue += 1;
        }
        return numberValue;
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Invalid consideration value: " << str << std::endl;
        return -1;
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Consideration value out of range: " << str << std::endl;
        return -1;
    }
}   

std::string HighPrecisionMoney::centsToString(const long long& cents) {
    bool isNegative = false;
    if (cents < 0) {
        isNegative = true;
    }
    std::string str = std::to_string(abs(cents));
    int zerosNeeded = 3 - str.length();
    if (zerosNeeded > 0) {
        str = std::string(zerosNeeded, '0') + str;
    }
    str.insert(str.length() - 2, ".");
    if (isNegative) {
        str.insert(0, "-");
    }
    return str;
}

std::string HighPrecisionMoney::hundredsOfCentsToString(const long long& hundredsOfCents) {
    std::cout << "hundredofcents " << hundredsOfCents << std::endl;
    bool isNegative = false;
    if (hundredsOfCents < 0) {
        isNegative = true;
    }
    std::string str = std::to_string(abs(hundredsOfCents));
    int zerosNeeded = 5 - str.length();
    if (zerosNeeded > 0) {
        str = std::string(zerosNeeded, '0') + str;
    }
    str.insert(str.length() - 4, ".");
    if (isNegative) {
        str.insert(0, "-");
    }
    std::cout << "str " << str << std::endl;
    return str;
}