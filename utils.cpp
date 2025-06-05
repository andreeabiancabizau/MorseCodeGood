//
// Created by Bianca Bizau on 06.06.2025.
//
#include "utils.h"
#include <iostream>
#include <regex>

void clear_screen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

bool is_valid_date(const std::string& date_str) {
    std::regex pattern(R"(^\d{2}\.\d{2}\.\d{4}$)");
    return std::regex_match(date_str, pattern);
}

bool is_valid_time(const std::string& time_str) {
    std::regex pattern(R"(^\d{2}:\d{2}$)");
    return std::regex_match(time_str, pattern);
}