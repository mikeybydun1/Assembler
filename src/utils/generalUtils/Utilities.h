#include <string>
#include <unordered_map>
#include <algorithm>

class Utilities {
    public:
        std::unordered_map<std::string, int> commandNumber;

        Utilities() {
            commandNumber = {
                {"mov", 0}, {"cmp", 1}, {"add", 2}, {"sub", 3}, {"not", 4}, {"clr", 5}, {"lea", 6},
                {"inc", 7}, {"dec", 8}, {"jmp", 9}, {"bne", 10}, {"red", 11}, {"prn", 12},
                {"jsr", 13}, {"rts", 14}, {"stop", 15}
            };
        }

        int decimalToBinary(int num);
        int getCommandNumber(std::string command);
        bool is_substring(std::string check, std::string str);
        std::string removeSpaceFront(std::string s);
        std::string removeSpaceTail(std::string s);
        std::string getCommand(std::string s1);
        std::string getFirstArg(std::string s1);
        std::string getOnlyArg(std::string s1);
        std::string getSecondArg(std::string s1);
        std::string removeTillSpace(std::string s1);
        int amountInString(std::string s1, char ch);
        std::string getRegisterBainry(std::string s);
        int asciiToBinNumber(char ch);
};
