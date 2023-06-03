// EntryLabel.cpp
#include "EntryLabel.h"

EntryLabel::EntryLabel(const std::string& name) : Label(name) {}

int EntryLabel::getType() const {
    return LABEL_TYPE_ENTRY; // 3 in your original code
}
