#pragma once
#include <curl/curl.h>
#include <stdexcept>

class CurlHandle {
    public:
        CurlHandle() {
            curl = curl_easy_init();
            if (!curl) {
                throw std::runtime_error("Failed to initalise curl");
            }
            curl_easy_setopt(curl, CURLOPT_REFERER, "https://www.fool.com.au/");
            curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);

        }
        ~CurlHandle() {
            if (curl) {
                curl_easy_cleanup(curl);
            }
        }
        CURL* getCurl() const {
            return curl;
        }

    private:
        CURL* curl;
};

static thread_local CurlHandle threadCurl;