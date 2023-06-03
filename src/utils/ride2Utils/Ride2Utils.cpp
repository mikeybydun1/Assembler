// Ride2Utils.cpp
#include "Ride2Utils.h"

std::pair<char, char> Ride2Utils::binaryTo32Base(const std::string& bin_num) {
    std::string low_word = bin_num.substr(0, 5);
    std::string high_word = bin_num.substr(5, 5);

    int decimal_low = binaryToDecimal(low_word);
    int decimal_high = binaryToDecimal(high_word);

    char base32_low = decimalTo32Chars(decimal_low);
    char base32_high = decimalTo32Chars(decimal_high);

    return std::make_pair(base32_low, base32_high);
}

int Ride2Utils::binaryToDecimal(const std::string& binary_string) {
    int total = 0;
    int decval = 1;

    for(int i = binary_string.size()-1; i >= 0; i--) {
        if(binary_string[i] == '1')
            total += decval;
        decval *= 2;
    }
    return total;
}

char Ride2Utils::decimalTo32Chars(int dec_num) {
    static const char base32_table[] = {
        '!', '@', '#', '$', '%', '^', '&', '*', '<', '>', 'a', 'b', 'c', 'd', 'e', 'f', 
        'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v'
    };

    if(dec_num >= 0 && dec_num < sizeof(base32_table))
        return base32_table[dec_num];
    else
        throw std::out_of_range("Invalid base 32 decimal value.");
}

// Removes label from a line
void Ride2Utils::removeLabel(std::string& line_copy, int count) {
    while(line_copy[count] != ':') {
        line_copy[count] = ' ';
        count++;
    }
    line_copy[count] = ' ';
    removeSpaceFront(line_copy);
}

// Translates number to binary and stores it in data array
void Ride2Utils::translateNumberToBinary(std::string& data_pointer, int dc1, int diff_counter) {
    if(is_substring("-",data_pointer)) {
        negativNumberToBin(data_pointer,true,dc1+diff_counter);
    }
    else {
        int bin_number = decimalToBinary(std::stoi(data_pointer));
        std::string bin_str;
        my_itoa(bin_number, bin_str);
        
        int bin_counter = BYTE_FULL_SIZE - bin_str.length();
        for(int i = 0; i < bin_str.length(); i++) {
            data_arr[dc1+diff_counter][bin_counter] = bin_str[i];
            bin_counter++;
        }
    }
}

// Translates a string to ascii and stores it in data array
void Ride2Utils::translateStringToAscii(std::string& pointer, int dc1, int diff) {
    pointer = pointer.substr(1, pointer.length()-2);  // remove quotes
    removeSpaceFront(pointer);
    removeSpaceTail(pointer);

    int ascii_bin;
    std::string bin_str(BYTE_FULL_SIZE, '\0');
    int bin_counter;
    char ch;

    for(int i = 0; i < pointer.length(); i++) {
        ch = pointer[i];
        ascii_bin = asciiToBinNumber(ch);
        my_itoa(ascii_bin,bin_str);
        
        bin_counter = BYTE_FULL_SIZE - bin_str.length();

        for(int j = 0; j < bin_str.length(); j++) {
            data_arr[dc1 + diff][bin_counter] = bin_str[j];
            bin_counter++;
        }
        diff++;
    }
}