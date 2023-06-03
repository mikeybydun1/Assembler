// ExternLabel.h
#pragma once

#include "Label.h"

class ExternLabel : public Label {
public:
    ExternLabel(const std::string& name);
    int getType() const override;
};
