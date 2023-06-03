// Label.cpp
#include "Label.h"

Label::Label(const std::string& name) : name(name) {}

std::string Label::getName() const {
    return name;
}
