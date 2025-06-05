#ifndef ENTRY_H
#define ENTRY_H

#include <string>
#include "Date.h"

class Entry {
private:
    Date date;
    std::string time;
    std::string text;
public:
    Entry(const Date& date, const std::string& time, const std::string& text);
    std::string to_line() const;
    static Entry from_line(const std::string& line);
    std::string get_time() const;
    Date get_date() const;
    std::string get_text() const;
    std::string get_morse() const;
    std::string decode() const;
};

#endif