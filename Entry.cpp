#include "Entry.h"
#include "MorseConverter.h"
#include <sstream>
#include <stdexcept>
#include <regex>

Entry::Entry(const Date& d, const std::string& t, const std::string& txt)
    : date(d), time(t), text(txt) {
    std::regex time_pattern(R"(^\d{2}:\d{2}$)");
    if (!std::regex_match(time, time_pattern)) {
        throw std::invalid_argument("Invalid time format. Use hh:mm");
    }
}

std::string Entry::to_line() const {
    return date.to_string() + "|" + time + "|" + MorseConverter::text_to_morse(text) + "|" + text;
}

Entry Entry::from_line(const std::string& line) {
    std::stringstream ss(line);
    std::string date_str, time_str, morse, decoded;

    std::getline(ss, date_str, '|');
    std::getline(ss, time_str, '|');
    std::getline(ss, morse, '|');
    std::getline(ss, decoded);

    return Entry(Date(date_str), time_str, decoded);
}

std::string Entry::get_time() const {
    return time;
}

Date Entry::get_date() const {
    return date;
}

std::string Entry::get_text() const {
    return text;
}

std::string Entry::get_morse() const {
    return MorseConverter::text_to_morse(text);
}

std::string Entry::decode() const {
    return text;
}