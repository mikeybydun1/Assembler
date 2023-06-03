// ExternLabel.cpp
#include "ExternLabel.h"

ExternLabel::ExternLabel(const std::string& name) : Label(name) {}

int ExternLabel::getType() const {
    return LABEL_TYPE_EXTERN; // 2 in your original code
}
