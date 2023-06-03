#include <algorithm>
#include <sstream>
#include <vector>
#include "Utilities.h"
#include "DataUtils.h"

#define CHECH_STRING_SIZE 50
#define REGISTER_ADDRESSING_TYPE 3
#define NUMBER_AADDRESSING_TYPE 0

std::string checkString(CHECH_STRING_SIZE, ' ');

int DataUtils::sentenceLength(std::string s1) {
    int L = 1;
  
    if(s1.length() == 3) { 
        return L;
    }
    else if(!Utilities::is_substring(",",s1) && !Utilities::is_substring(".string",s1) 
            && !Utilities::is_substring(".data",s1) && !Utilities::is_substring(".struct",s1)) {
        std::string argument = Utilities::getFirstArg(s1);
        L++;
        if(Utilities::is_substring(".",argument)) {
            L++;
        }
        return L;
    }
    // More conditions go here with equivalent changes like the above.
}

int DataUtils::argAmount(std::string s1) {
    int arguments = -1;
    if(s1 == "mov" || s1 == "cmp" || s1 == "add" || s1 == "sub" || s1 == "lea") {
        arguments = 2;
    }
    else if(s1 == "not" || s1 == "clr" || s1 == "inc" || s1 == "dec" || s1 == "jmp" || s1 == "bne" 
            || s1 == "red" || s1 == "prn" || s1 == "jsr") {
        arguments = 1;
    }
    else if(s1 == "rts" || s1 == "stop") {
        arguments = 0;
    }
    return arguments;
}

int DataUtils::getAddressingType(std::string s1) {
    if(s1 == "r1" || s1 == "r2" || s1 == "r3" || s1 == "r4" || s1 == "r5" || s1 == "r6" || s1 == "r0" || s1 == "r7") {
        return REGISTER_ADDRESSING_TYPE;
    }
    if(Utilities::is_substring("#",s1)) {
        return NUMBER_AADDRESSING_TYPE;
    }
    if(Utilities::is_substring(".",s1)) {
        return 2;
    }
    else {
        return 1;
    }
}

bool DataUtils::isAddressingTypeOk(std::string command, std::string sentence) {
    if(command == "rts" || command == "stop" || command == "cmp" || command == "prn") {
        return true;
    }
    else if(command == "mov" || command == "add" || command == "sub") {
        std::string second_arg = Utilities::getSecondArg(sentence);
        if(getAddressingType(second_arg) == NUMBER_AADDRESSING_TYPE) {
            return false;
        }
        else {
            return true;
        }
    }
    // More conditions go here with equivalent changes like the above.
}