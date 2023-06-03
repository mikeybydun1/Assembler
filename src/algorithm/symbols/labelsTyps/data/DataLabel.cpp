// DataLabel.cpp
#include "DataLabel.h"

DataLabel::DataLabel(const std::string& name) : Label(name) {}

int DataLabel::getType() const {
    return 0; // Replace with appropriate value for each label type.
}

// Similar for ExternLabel, EntryLabel, CodeLabel, just replace "DataLabel" with the appropriate class name.
