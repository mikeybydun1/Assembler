#ifndef DATAUTILS_H
#define DATAUTILS_H

#include <string>

class DataUtils {
public:
    static int sentenceLength(std::string s1);
    static int argAmount(std::string s1);
    static int getAddressingType(std::string s1);
    static bool isAddressingTypeOk(std::string command, std::string sentence);
};

#endif // DATAUTILS_H
