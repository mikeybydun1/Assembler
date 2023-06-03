#ifndef PRE_ASSEMBLER_H
#define PRE_ASSEMBLER_H

#include <string>
#include "MacroTable.h"

class PreAssembler {
public:
    PreAssembler();

    void removeMacro(const std::string &fileWithMacro, const std::string &fileWithoutMacro);

private:
    MacroTable macroTable;
};

#endif // PRE_ASSEMBLER_H
