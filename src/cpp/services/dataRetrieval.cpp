#include "dataRetrieval.h"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <cstring>
#include <nlohmann/json.hpp>
#include <fstream> 

size_t DataRetrieval::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string DataRetrieval::getRequest(std::string ASXCode) {
    for (char& c : ASXCode) {
        c = std::tolower(c);
    }
    std::string url = "https://quoteapi.com/api/v5/symbols/" + ASXCode + ".asx?appID=4ec85c869fdae450&averages=1&liveness=delayed";
    CURL *curl = curl_easy_init();
    if (!curl) {
        throw std::runtime_error("Failed to initialise curl");
    }
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

//TODO: Internet check before calling getRequest
void DataRetrieval::getLivePrices(std::pair<const std::string, liveShares>& pair) {
    std::string jsonResponse = getRequest(pair.first);
    nlohmann::json j = nlohmann::json::parse(jsonResponse);
    double price = j["quote"]["price"];
    pair.second.price = price;
}

void DataRetrieval::cacheSpecialCorporateActions(std::vector<ShareSplitRow>& shareSplitVector, std::vector<NameChangeRow>& shareNameChangeVector, std::vector<DataRow>& shareTakeOverVector){
    nlohmann::json j1;
    j1["shareSplitVector"] = shareSplitVector;
    std::ofstream file1("resources/jsons/shareSplitVector.json");
    file1 << j1;
    file1.close();

    nlohmann::json j2;
    j2["shareNameChangeVector"] = shareNameChangeVector;
    std::ofstream file2("resources/jsons/shareNameChangeVector.json");
    file2 << j2;
    file2.close();

    nlohmann::json j3;
    j3["shareTakeOverVector"] = shareTakeOverVector;
    std::ofstream file3("resources/jsons/shareTakeOverVector.json");
    file3 << j3;
    file3.close();
}

void DataRetrieval::loadCachedData(std::vector<DataRow>& data) {
    //Check if the json files exist and create them if they don't
    if (!std::filesystem::exists("resources/jsons/shareSplitVector.json")){
        nlohmann::json j;
        std::vector<ShareSplitRow> empty;
        j["shareSplitVector"] = empty;
        std::ofstream file("resources/jsons/shareSplitVector.json");
        file << j;
    }
    if (!std::filesystem::exists("resources/jsons/shareNameChangeVector.json")){
        nlohmann::json j;
        std::vector<NameChangeRow> empty;
        j["shareNameChangeVector"] = empty;
        std::ofstream file("resources/jsons/shareNameChangeVector.json");
        file << j;
    }
    if (!std::filesystem::exists("resources/jsons/shareTakeOverVector.json")){
        nlohmann::json j;
        std::vector<DataRow> empty;
        j["shareTakeOverVector"] = empty;
        std::ofstream file("resources/jsons/shareTakeOverVector.json");
        file << j;
    }

    nlohmann::json j1;
    std::ifstream file1("resources/jsons/shareSplitVector.json");
    file1 >> j1;
    std::vector<ShareSplitRow> shareSplitVector = j1["shareSplitVector"];
    file1.close();
    for (ShareSplitRow& row : shareSplitVector) {
        for (DataRow& dataRow : data) {
            if (dataRow.ASXCode == row.ASXCode) {
                dataRow.price /= row.ratio;
                dataRow.quantity *= row.ratio;
            }
        }
    }

    nlohmann::json j2;
    std::ifstream file2("resources/jsons/shareNameChangeVector.json");
    file2 >> j2;
    std::vector<NameChangeRow> shareNameChangeVector = j2["shareNameChangeVector"];
    file2.close();
    for (NameChangeRow& row : shareNameChangeVector) {
        for (DataRow& dataRow : data) {
            if (dataRow.ASXCode == row.ASXCode) {
                dataRow.ASXCode = row.newASXCode;
            }
        }
    }

    nlohmann::json j3;
    std::ifstream file3("resources/jsons/shareTakeOverVector.json");
    file3 >> j3;
    std::vector<DataRow> shareTakeOverVector = j3["shareTakeOverVector"];
    file3.close();
    data.insert(data.end(), shareTakeOverVector.begin(), shareTakeOverVector.end());
}
