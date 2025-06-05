//
// Created by Bianca Bizau on 06.06.2025.
//
#ifndef MORSE_CONVERTER_H
#define MORSE_CONVERTER_H

#include <string>

class MorseConverter {
public:
    static std::string text_to_morse(const std::string& text);
    static std::string morse_to_text(const std::string& morse);
};

#endif