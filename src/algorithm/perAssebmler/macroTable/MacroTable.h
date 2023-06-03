#ifndef MACRO_TABLE_H
#define MACRO_TABLE_H

#include <vector>
#include "Macro.h"

class MacroTable {
public:
    MacroTable();

    int find(const std::string &name) const;
    void addMacro(const Macro &macro);

private:
    std::vector<Macro> macroList;
};

#endif // MACRO_TABLE_H
