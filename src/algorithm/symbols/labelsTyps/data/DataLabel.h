// DataLabel.h
#pragma once
#include "Label.h"

class DataLabel : public Label {
public:
    DataLabel(const std::string& name);
    int getType() const override;
};

// Similar for ExternLabel, EntryLabel, CodeLabel, just replace "DataLabel" with the appropriate class name.
