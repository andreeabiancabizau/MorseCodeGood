#include "Date.h"
#include <sstream>
#include <iomanip>
#include <regex>
#include <ctime>
#include <stdexcept>

Date::Date() : day(1), month(1), year(1970) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date::Date(const std::string& date_str) {
    std::regex pattern(R"(^\d{2}\.\d{2}\.\d{4}$)");
    if (!std::regex_match(date_str, pattern)) {
        throw std::invalid_argument("Invalid date format. Use dd.mm.yyyy");
    }

    std::stringstream ss(date_str);
    char dot;
    ss >> day >> dot >> month >> dot >> year;

    if (day < 1 || day > 31 || month < 1 || month > 12 || year < 1900) {
        throw std::invalid_argument("Invalid date values.");
    }
}

Date Date::from_string(const std::string& str) {
    return Date(str);  // use the validated constructor
}

Date Date::today() {
    time_t t = time(nullptr);
    tm* now = localtime(&t);
    return Date(now->tm_mday, now->tm_mon + 1, now->tm_year + 1900);
}

std::string Date::to_string() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << "."
        << std::setw(2) << std::setfill('0') << month << "."
        << year;
    return oss.str();
}