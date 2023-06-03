#include <fstream>
#include <sstream>
#include "PreAssembler.h"
#include "utilities.h"

PreAssembler::PreAssembler() {}

void PreAssembler::removeMacro(const std::string &fileWithMacro, const std::string &fileWithoutMacro) {
    std::ifstream fp(fileWithMacro);
    std::ofstream fp2(fileWithoutMacro);

    if (!fp || !fp2) {
        std::cerr << "Error: File not found...\n";
        return;
    }

    bool isMacro = false;
    std::string line;
    Macro currentMacro;

    while (std::getline(fp, line)) {
        trim(line); // Assume trim function from utilities

        if (!isMacro && macroTable.find(line) != -1) {
            int thisIndex = macroTable.find(line);
            fp2 << macroTable.getMacro(thisIndex).getCode() << "\n";
        }
        else if (startsWith(line, "macro")) {  // Assume startsWith function from utilities
            isMacro = true;
            line = line.substr(5);  // Remove 'macro'
            trim(line);
            currentMacro.setName(line);
            currentMacro.setCode("");
        }
        else if (startsWith(line, "endmacro")) {
            isMacro = false;
            macroTable.addMacro(currentMacro);
        }
        else if (isMacro) {
            currentMacro.setCode(currentMacro.getCode() + line + "\n");
        }
        else {
            fp2 << line << "\n";
        }
    }
}
