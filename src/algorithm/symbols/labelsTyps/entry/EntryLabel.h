// EntryLabel.h
#pragma once

#include "Label.h"

class EntryLabel : public Label {
public:
    EntryLabel(const std::string& name);
    int getType() const override;
};
