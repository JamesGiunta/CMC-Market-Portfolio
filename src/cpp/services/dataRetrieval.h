#pragma once
#include <string>

class DataRetrieval {
public:
    std::string getRequest(std::string ASXCode);
private:
    static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp);
};