// Label.h
#pragma once

#include <string>

class Label {
public:
    Label(const std::string& name);
    virtual ~Label() = default;
    
    std::string getName() const;

    virtual int getType() const = 0;

protected:
    std::string name;
};
