#include "MacroTable.h"

MacroTable::MacroTable() {}

int MacroTable::find(const std::string &name) const {
    for (int i = 0; i < macroList.size(); i++) {
        if (macroList[i].getName() == name) {
            return i;
        }
    }
    return -1;
}

void MacroTable::addMacro(const Macro &macro) {
    macroList.push_back(macro);
}
