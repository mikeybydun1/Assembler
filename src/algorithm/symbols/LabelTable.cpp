// LabelTable.cpp
#include "LabelTable.h"
#include "DataLabel.h"
#include "ExternLabel.h"
#include "EntryLabel.h"
#include "CodeLabel.h"

LabelTable::LabelTable() {}

bool LabelTable::isInTable(const std::string& labelName) const {
    for (const auto& label : labels) {
        if (label->getName() == labelName)
            return true;
    }
    return false;
}

std::string LabelTable::isLabel(const std::string& line) const {
    // Your implementation here
}

int LabelTable::getLabelType(const std::string& line) const {
    // Your implementation here
}

int LabelTable::getLabelIndex(const std::string& labelName) const {
    for (int i = 0; i < labels.size(); i++) {
        if (labels[i]->getName() == labelName)
            return i;
    }
    return -1;
}

void LabelTable::addLabel(std::unique_ptr<Label> label) {
    labels.push_back(std::move(label));
}
