#include "customSaxHandler.h"

bool CustomSaxHandler::key(string_t& val) {
    if (val == "quote") {
        inQuote = true;
    }
    else if (val == "price") {
        inPrice = true;
    }
    return true;
}

bool CustomSaxHandler::number_float(number_float_t val, const string_t& s) {
    if (inPrice) {
        priceStr = s;
        inPrice = false;
        // Stop parsing after getting the price
        return false;
    }
    return true;
}