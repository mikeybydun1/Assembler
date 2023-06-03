// CodeLabel.cpp
#include "CodeLabel.h"

CodeLabel::CodeLabel(const std::string& name) : Label(name) {}

int CodeLabel::getType() const {
    return LABEL_TYPE_CODE; // 1 in your original code
}
