#include "dataRetrieval.h"
#include <curl/curl.h>
#include <iostream>
#include <string>
#include <cstring>

size_t DataRetrieval::WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string DataRetrieval::getRequest(std::string ASXCode) {
    std::string url = "https://au.finance.yahoo.com/quote/" + ASXCode + ".AX/";
    CURL *curl = curl_easy_init();
    std::string html;
    std::string result;
    CURLcode res;
    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/114.0.0.0 Safari/537.36 Edg/114.0.1823.51");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &html);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);

    }
    return html;
}
