// LabelTable.h
#pragma once

#include <vector>
#include "Label.h"

class LabelTable {
public:
    LabelTable();

    bool isInTable(const std::string& labelName) const;
    std::string isLabel(const std::string& line) const;
    int getLabelType(const std::string& line) const;
    int getLabelIndex(const std::string& labelName) const;

    void addLabel(std::unique_ptr<Label> label);
private:
    std::vector<std::unique_ptr<Label>> labels;
};
