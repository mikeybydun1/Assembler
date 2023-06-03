#ifndef MACRO_H
#define MACRO_H

#include <string>

class Macro {
public:
    Macro(const std::string &name = "", const std::string &code = "");

    std::string getName() const;
    std::string getCode() const;
    void setName(const std::string &name);
    void setCode(const std::string &code);

private:
    std::string name;
    std::string code;
};

#endif // MACRO_H
