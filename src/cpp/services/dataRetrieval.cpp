#include "dataRetrieval.h"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <cstring>
#include <nlohmann/json.hpp>
#include <fstream> 

size_t DataRetrieval::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string DataRetrieval::getRequest(std::string ASXCode) {
    for (char& c : ASXCode) {
        c = std::tolower(c);
    }
    std::string url = "https://quoteapi.com/api/v5/symbols/" + ASXCode + ".asx?appID=4ec85c869fdae450&averages=1&liveness=delayed";
    CURL *curl = curl_easy_init();
    CURLcode res;
    std::string jsonResponse;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_REFERER, "https://www.fool.com.au/");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &jsonResponse);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }
        long httpCode = 0;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        if (httpCode != 200){
            std::cerr << "httpCode: " << httpCode << std::endl;
        }
    curl_easy_cleanup(curl);
    }
    return jsonResponse;
}

void DataRetrieval::getLivePrices(std::pair<const std::string, liveShares>& pair) {
    std::string jsonResponse = getRequest(pair.first);
    nlohmann::json j = nlohmann::json::parse(jsonResponse);
    double price = j["quote"]["price"];
    std::cout << "Price: " << price << std::endl;
    pair.second.price = price;
}
