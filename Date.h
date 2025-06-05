#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day, month, year;
public:
    Date();  // default
    Date(int d, int m, int y);
    Date(const std::string& date_str);

    static Date today();                         // get today's date
    static Date from_string(const std::string&); // used in app_1
    std::string to_string() const;
};

#endif