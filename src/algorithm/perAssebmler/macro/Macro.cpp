#include "Macro.h"

Macro::Macro(const std::string &name, const std::string &code) : name(name), code(code) {}

std::string Macro::getName() const {
    return name;
}

std::string Macro::getCode() const {
    return code;
}

void Macro::setName(const std::string &name) {
    this->name = name;
}

void Macro::setCode(const std::string &code) {
    this->code = code;
}
