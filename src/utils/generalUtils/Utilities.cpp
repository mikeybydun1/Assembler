#include <string>
#include <unordered_map>
#include <algorithm>
#include "utilities.h"

int Utilities::decimalToBinary(int num) {
    int bin = 0, rem = 0, place = 1;
    while(num) {
        rem = num % 2;
        num /= 2;
        bin += rem * place;
        place *= 10;
    }
    return bin;
}

int Utilities::getCommandNumber(std::string command) {
    if (commandNumber.find(command) != commandNumber.end())
        return commandNumber[command];
    else
        return 16;
}

bool Utilities::is_substring(std::string check, std::string str) {
    return str.find(check) != std::string::npos;
}

std::string Utilities::removeSpaceFront(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
    return s;
}

std::string Utilities::removeSpaceTail(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

std::string Utilities::getCommand(std::string s1) {
    s1 = removeSpaceFront(s1);
    return s1.substr(0, s1.find(" "));
}

std::string Utilities::getFirstArg(std::string s1) {
    s1 = removeSpaceFront(s1);
    s1 = s1.substr(s1.find(" "), s1.length());
    if(s1.find(",") != std::string::npos)
        s1 = s1.substr(0, s1.find(","));
    s1 = removeSpaceFront(s1);
    s1 = removeSpaceTail(s1);
    return s1;
}

std::string Utilities::getOnlyArg(std::string s1) {
    s1 = removeSpaceFront(s1);
    s1 = s1.substr(s1.find(" "), s1.length());
    s1 = removeSpaceFront(s1);
    s1 = removeSpaceTail(s1);
    return s1;
}

std::string Utilities::getSecondArg(std::string s1) {
    if(s1.find(",") != std::string::npos) {
        s1 = s1.substr(s1.find(",") + 1, s1.length());
        s1 = removeSpaceFront(s1);
        s1 = removeSpaceTail(s1);
    }
    return s1;
}

std::string Utilities::removeTillSpace(std::string s1) {
    return s1.substr(s1.find(" ") + 1);
}

int Utilities::amountInString(std::string s1, char ch) {
    return std::count(s1.begin(), s1.end(), ch);
}

std::string Utilities::getRegisterBainry(std::string s) {
    std::string register_str = "0000";
    if(s=="r1") register_str[3] = '1';
    else if(s=="r2") register_str[2] = '1';
    else if(s=="r3") { register_str[2] = '1'; register_str[3] = '1'; }
    else if(s=="r4") register_str[1] = '1';
    else if(s=="r5") { register_str[1] = '1'; register_str[3] = '1'; }
    else if(s=="r6") { register_str[1] = '1'; register_str[2] = '1'; }
    else if(s=="r7") { register_str[1] = '1'; register_str[2] = '1'; register_str[3] = '1'; }
    return register_str;
}

int Utilities::asciiToBinNumber(char ch) {
    return decimalToBinary((int)ch);
}
