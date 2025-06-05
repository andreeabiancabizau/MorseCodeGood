//
// Created by Bianca Bizau on 06.06.2025.
//
#include "MorseConverter.h"
#include <unordered_map>
#include <sstream>

std::string MorseConverter::text_to_morse(const std::string& text) {
    static const std::unordered_map<char, std::string> morse_map = {
        {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."}, {'E', "."},
        {'F', "..-."}, {'G', "--."}, {'H', "...."}, {'I', ".."}, {'J', ".---"},
        {'K', "-.-"}, {'L', ".-.."}, {'M', "--"}, {'N', "-."}, {'O', "---"},
        {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
        {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"}, {'Y', "-.--"},
        {'Z', "--.."},
        {'0', "-----"}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"},
        {'4', "....-"}, {'5', "....."}, {'6', "-...."}, {'7', "--..."},
        {'8', "---.."}, {'9', "----."},
        {' ', "/"}
    };

    std::stringstream ss;
    for (char c : text) {
        char uc = toupper(c);
        auto it = morse_map.find(uc);
        if (it != morse_map.end()) {
            ss << it->second << " ";
        }
    }
    return ss.str();
}

std::string MorseConverter::morse_to_text(const std::string& morse) {
    static const std::unordered_map<std::string, char> text_map = {
        {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'},
        {"..-.", 'F'}, {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'},
        {"-.-", 'K'}, {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'},
        {".--.", 'P'}, {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'},
        {"..-", 'U'}, {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'},
        {"--..", 'Z'},
        {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
        {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'},
        {"---..", '8'}, {"----.", '9'},
        {"/", ' '}
    };

    std::stringstream ss(morse);
    std::string token;
    std::string result;

    while (ss >> token) {
        auto it = text_map.find(token);
        if (it != text_map.end()) {
            result += it->second;
        }
    }
    return result;
}
