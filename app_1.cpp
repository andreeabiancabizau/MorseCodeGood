#include <iostream>
#include <fstream>
#include <string>
#include "Date.h"
#include "Entry.h"
#include "utils.h"

void print_colored_menu() {
    clear_screen();
    std::cout << "\033[1;36m=== Welcome to Morse Diary ===\033[0m\n";
    std::cout << "\033[1;35m1.\033[0m \033[38;5;225mHow to use?\033[0m\n";
    std::cout << "\033[1;35m2.\033[0m \033[38;5;222mView entries (Morse)\033[0m\n";
    std::cout << "\033[1;35m3.\033[0m \033[38;5;151mView entries (Decoded)\033[0m\n";
    std::cout << "\033[1;35m4.\033[0m \033[38;5;159mAdd a new entry\033[0m\n";
    std::cout << "\033[1;35m5.\033[0m \033[38;5;245mExit\033[0m\n";
    std::cout << "Choose an option: ";
}

void how_to_use() {
    clear_screen();
    std::cout << "\n\033[1;34mUsage examples:\033[0m\n";
    std::cout << "./app_1 add_entry <dd.mm.yyyy> <hh:mm> \"Your text\"\n";
    std::cout << "./app_1 view_entries [--decoded]\n\n";
    std::cout << "Press Enter to return..."; std::cin.ignore(); std::cin.get();
}

void view_entries(bool decode) {
    clear_screen();
    std::ifstream in(decode ? "diary_decoded.txt" : "diary.txt");
    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << "\n";
    }
    in.close();
    std::cout << "\nPress Enter to continue..."; std::cin.ignore(); std::cin.get();
}

void add_new_entry_interactive() {
    clear_screen();
    std::string date_str, time_str, text;

    std::cin.ignore();
    std::cout << "\033[1;34mEnter date and time\033[0m (format \033[1;33mdd.mm.yyyy hh:mm\033[0m): ";
    std::getline(std::cin, date_str, ' ');
    std::getline(std::cin, time_str);

    while (!is_valid_date(date_str) || !is_valid_time(time_str)) {
        std::cout << "\033[1;31mInvalid date or time. Try again:\033[0m ";
        std::getline(std::cin, date_str, ' ');
        std::getline(std::cin, time_str);
    }

    std::cout << "\033[1;34mEnter diary entry:\033[0m ";
    std::getline(std::cin, text);

    Entry entry(Date::from_string(date_str), time_str, text);

    std::ofstream out("diary.txt", std::ios::app);
    out << entry.get_date().to_string() << " " << entry.get_time() << " | " << entry.get_morse() << "\n";
    out.close();

    std::ofstream out_decoded("diary_decoded.txt", std::ios::app);
    out_decoded << entry.get_date().to_string() << " " << entry.get_time() << " | " << entry.get_text() << "\n";
    out_decoded.close();

    std::ofstream log("logs.txt", std::ios::app);
    log << date_str << "|" << time_str << "|" << text << "\n";
    log.close();

    std::cout << "\033[1;32mSaved successfully!\033[0m\n";
    std::cout << "Press Enter to continue..."; std::cin.get();
}

int main(int argc, char* argv[]) {
    if (argc > 1) {
        std::string command = argv[1];
        if (command == "add_entry" && argc == 5) {
            std::string date_str = argv[2];
            std::string time_str = argv[3];
            std::string text = argv[4];

            if (!is_valid_date(date_str) || !is_valid_time(time_str)) {
                std::cerr << "\033[1;31mInvalid date/time format.\033[0m\n";
                return 1;
            }

            Entry entry(Date::from_string(date_str), time_str, text);

            std::ofstream out("diary.txt", std::ios::app);
            out << entry.get_date().to_string() << " " << entry.get_time() << " | " << entry.get_morse() << "\n";
            out.close();

            std::ofstream out_decoded("diary_decoded.txt", std::ios::app);
            out_decoded << entry.get_date().to_string() << " " << entry.get_time() << " | " << entry.get_text() << "\n";
            out_decoded.close();

            std::ofstream log("logs.txt", std::ios::app);
            log << date_str << "|" << time_str << "|" << text << "\n";
            log.close();

            std::cout << "\033[1;32mEntry saved.\033[0m\n";
        } else if (command == "view_entries") {
            bool decode = argc == 3 && std::string(argv[2]) == "--decoded";
            view_entries(decode);
        } else {
            std::cerr << "\033[1;31mInvalid command.\033[0m\n";
        }
        return 0;
    }

    int choice;
    do {
        print_colored_menu();
        std::cin >> choice;
        switch (choice) {
            case 1: how_to_use(); break;
            case 2: view_entries(false); break;
            case 3: view_entries(true); break;
            case 4: add_new_entry_interactive(); break;
            case 5:
                clear_screen();
                std::cout << "\033[1;36mGoodbye!\033[0m\n"; break;
            default:
                std::cout << "\033[1;31mInvalid option.\033[0m\n";
        }
    } while (choice != 5);

    return 0;
}