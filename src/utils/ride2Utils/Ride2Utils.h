// Ride2Utils.h
#pragma once

#include <string>
#include <vector>

class Ride2Utils {
public:
    static std::pair<char, char> binaryTo32Base(const std::string& bin_num);
    static int binaryToDecimal(const std::string& binary_string);
    static char decimalTo32Chars(int dec_num);
    static void removeLabel(std::string& line_copy, int count);
    static void translateNumberToBinary(std::string& data_pointer, int dc1, int diff_counter);
    static void translateStringToAscii(std::string& pointer, int dc1, int diff);
};
