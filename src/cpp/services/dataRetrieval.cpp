#include "dataRetrieval.h"
#include "customSaxHandler.h"
#include "highPrecisionMoney.h"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <cstring>
#include <nlohmann/json.hpp>
#include <fstream> 
#include <filesystem>

/**
 * Stock Data Retriever
 * 
 * DISCLAIMER: This code makes API calls with a specific referrer setting.
 * See README.md for important usage information and disclaimers.
 * Use at your own risk and responsibility.
 */

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
    CustomSaxHandler handler;
    std::istringstream inputStream(jsonResponse);
    nlohmann::json::sax_parse(inputStream, &handler);
    if (handler.priceStr.empty()) {
        throw std::runtime_error("Unable to extract share price from JSON");
    }
    pair.second.price = HighPrecisionMoney::stringToNumberInHundredsOfCents(handler.priceStr);
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

void DataRetrieval::loadCachedData(std::vector<DataRow>& data, std::map<std::string, liveShares>& liveSharesMap) {
    //Check if the json files exist and create them if they don't
    if (!std::filesystem::exists("../resources/jsons/shareSplitVector.json")) {
        nlohmann::json j;
        std::vector<ShareSplitRow> empty;
        j["shareSplitVector"] = empty;
        std::ofstream file("../resources/jsons/shareSplitVector.json");
        file << j;
        file.close();
    }

    if (!std::filesystem::exists("../resources/jsons/shareNameChangeVector.json")) {
        nlohmann::json j;
        std::vector<NameChangeRow> empty;
        j["shareNameChangeVector"] = empty;
        std::ofstream file("../resources/jsons/shareNameChangeVector.json");
        file << j;
        file.close();
    }

    if (!std::filesystem::exists("../resources/jsons/shareTakeOverVector.json")) {
        nlohmann::json j;
        std::vector<DataRow> empty;
        j["shareTakeOverVector"] = empty;
        std::ofstream file("../resources/jsons/shareTakeOverVector.json");
        file << j;
        file.close();
    }

    nlohmann::json j1;
    std::ifstream file1("../resources/jsons/shareSplitVector.json");
    if (file1.is_open()) {
        file1 >> j1;
        file1.close();
    } 
    else {
        std::cerr << "Failed to open shareSplitVector.json" << std::endl;
    }
    std::vector<ShareSplitRow> shareSplitVector = j1["shareSplitVector"];
    for (ShareSplitRow& row : shareSplitVector) {
        for (DataRow& dataRow : data) {
            if (dataRow.ASXCode == row.ASXCode) {
                dataRow.price /= row.ratio;
                dataRow.quantity *= row.ratio;
            }
        }
    }

    nlohmann::json j2;
    std::ifstream file2("../resources/jsons/shareNameChangeVector.json");
    if (file2.is_open()) {
        file2 >> j2;
        file2.close();
    } 
    else {
        std::cerr << "Failed to open shareNameChangeVector.json" << std::endl;
    }
    std::vector<NameChangeRow> shareNameChangeVector = j2["shareNameChangeVector"];
    for (NameChangeRow& row : shareNameChangeVector) {
        for (DataRow& dataRow : data) {
            if (dataRow.ASXCode == row.ASXCode) {
                dataRow.ASXCode = row.newASXCode;
            }
        }
    }

    nlohmann::json j3;
    std::ifstream file3("../resources/jsons/shareTakeOverVector.json");
    if (file3.is_open()) {
        file3 >> j3;
        file3.close();
    } 
    else {
        std::cerr << "Failed to open shareTakeOverVector.json" << std::endl;
    }
    std::vector<DataRow> shareTakeOverVector = j3["shareTakeOverVector"];

    //update live shares map after share name change and share split first to avoid errors
    liveSharesMap = to.createLiveDataVector(data);
    for (DataRow& row : shareTakeOverVector) {
        if (liveSharesMap.find(row.ASXCode) != liveSharesMap.end()) {
            row.quantity = liveSharesMap[row.ASXCode].quantity;
            row.consideration = (row.price * row.quantity) / 100;
            liveSharesMap.erase(row.ASXCode);
        }
    }
    data.insert(data.end(), shareTakeOverVector.begin(), shareTakeOverVector.end());
}


void DataRetrieval::clearCache() {
    std::filesystem::path path = "../resources/jsons";
    for(const auto& entry : std::filesystem::directory_iterator(path)) {
        std::filesystem::remove_all(entry.path());
    }
}

void DataRetrieval::cacheSpecialCoporateActions(DataRow row) {
    nlohmann::json j;

    std::filesystem::path path = "../resources/jsons/shareTakeOverVector.json";
    if (std::filesystem::exists(path)) {
        std::ifstream file(path);
        if (file.is_open()) {
            file >> j;
            file.close();
        } 
        else {
            std::cerr << "Failed to open shareTakeOverVector.json" << std::endl;
        }
    }
    j["shareTakeOverVector"].push_back(row);

    std::ofstream outputFile(path);
    if (outputFile.is_open()) {
        outputFile << j;
        outputFile.close();
    } 
    else {
        std::cerr << "Failed to open shareTakeOverVector.json" << std::endl;
    }
}

void DataRetrieval::cacheShareConsolidation(ShareSplitRow row) {
    nlohmann::json j;

    std::filesystem::path path = "../resources/jsons/shareSplitVector.json";
    if (std::filesystem::exists(path)) {
        std::ifstream file(path);
        if (file.is_open()) {
            file >> j;
            file.close();
        } 
        else {
            std::cerr << "Failed to open shareSplitVector.json" << std::endl;
        }
    }
    j["shareSplitVector"].push_back(row);

    std::ofstream outputFile(path);
    if (outputFile.is_open()) {
        outputFile << j;
        outputFile.close();
    } 
    else {
        std::cerr << "Failed to open shareSplitVector.json" << std::endl;
    }
}

void DataRetrieval::cacheShareNameChange(NameChangeRow row) {
    nlohmann::json j;

    std::filesystem::path path = "../resources/jsons/shareNameChangeVector.json";
    if (std::filesystem::exists(path)) {
        std::ifstream file(path);
        if (file.is_open()) {
            file >> j;
            file.close();
        } 
        else {
            std::cerr << "Failed to open shareNameChangeVector.json" << std::endl;
        }
    }
    j["shareNameChangeVector"].push_back(row);

    std::ofstream outputFile(path);
    if (outputFile.is_open()) {
        outputFile << j;
        outputFile.close();
    } 
    else {
        std::cerr << "Failed to open shareNameChangeVector.json" << std::endl;
    }
}
