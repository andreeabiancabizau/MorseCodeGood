#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "Entry.h"
#include "utils.h"



void search_word_in_logs(const std::string& word) {
    clear_screen();
    std::ifstream in("logs.txt");
    std::string line;
    bool found = false;

    std::regex entry_pattern(R"(Added entry on (\d{2}\.\d{2}\.\d{4}) at (\d{2}:\d{2}): (.*))");

    while (std::getline(in, line)) {
        std::smatch match;
        if (std::regex_match(line, match, entry_pattern)) {
            std::string date = match[1];
            std::string time = match[2];
            std::string text = match[3];

            if (text.find(word) != std::string::npos) {
                found = true;
                std::cout << "\033[1;34m" << date << " " << time << ":\033[0m " << text << "\n";
            }
        }
    }

    in.close();
    if (!found) {
        std::cout << "\033[1;31mNo entries found with the word \"" << word << "\".\033[0m\n";
    }
}

void export_decoded_entries(const std::string& filename) {
    clear_screen();
    std::ifstream in("diary.txt");
    std::ofstream out(filename);
    std::string line;

    while (std::getline(in, line)) {
        Entry e = Entry::from_line(line);
        out << e.get_date().to_string() << " " << e.get_time() << ": " << e.decode() << "\n";
    }

    in.close();
    out.close();
    std::cout << "\033[1;32mEntries exported to \033[1;33m" << filename << "\033[0m\n";
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cerr << "\033[1;31mUsage:\033[0m\n";
        std::cerr << "./app_2 search_word <word>\n";
        std::cerr << "./app_2 export_entries <filename>\n";
        return 1;
    }

    std::string command = argv[1];
    if (command == "search_word") {
        search_word_in_logs(argv[2]);
    } else if (command == "export_entries") {
        export_decoded_entries(argv[2]);
    } else {
        std::cerr << "\033[1;31mUnknown command.\033[0m\n";
        return 1;
    }

    return 0;
}