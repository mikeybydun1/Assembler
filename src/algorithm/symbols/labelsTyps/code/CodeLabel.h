// CodeLabel.h
#pragma once

#include "Label.h"

class CodeLabel : public Label {
public:
    CodeLabel(const std::string& name);
    int getType() const override;
};
