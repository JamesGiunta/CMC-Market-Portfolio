#pragma once
#include <string>

class HighPrecisionMoney {
public:
    static long long stringToNumberInCents(std::string& str);
    static long long stringToNumberInHundredsOfCents(std::string& str);
    static std::string centsToString(long long& cents);
    static std::string hundredsOfCentsToString(long long& hundredsOfCents);

private:
};