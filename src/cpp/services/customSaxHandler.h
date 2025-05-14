#pragma once
#include <nlohmann/json.hpp>

class CustomSaxHandler : public nlohmann::json::json_sax_t {
    public:
        bool inQuote = false;
        bool inPrice = false;
        std::string priceStr;
        bool null() override {
            return true;
        }
        bool boolean(bool val) override {
            return true;
        }
        bool number_integer(number_integer_t val) override {
            return true;
        }
        bool number_unsigned(number_unsigned_t val) override {
            return true;
        }
        bool number_float(number_float_t, const string_t& s) override;
        bool string(string_t& val) override {
            return true;
        };
        bool binary(binary_t& val) override {
            return true;
        };
        bool start_object(std::size_t elements) override {
            return true;
        }
        bool end_object() override {
            return !inPrice;
        }
        bool start_array(std::size_t elements) override {
            return true;
        }
        bool end_array() override {
            return true;
        }
        bool key(string_t& val) override;
        bool parse_error(std::size_t position, const std::string& last_token, const nlohmann::json::exception& ex) override {
            return true;
        }
};