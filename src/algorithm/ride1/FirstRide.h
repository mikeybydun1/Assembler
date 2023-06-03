#ifndef FIRST_RIDE_H
#define FIRST_RIDE_H

#include <string>
#include <vector>
#include "MacroTable.h"
#include "Label.h"

class FirstRide {
public:
    FirstRide();

    void executeFirstRide(const std::string &fileName);

private:
    int IC;
    int DC;
    int labelCounter;
    std::vector<Label> labelTable;
    int amountLinesInFile(const std::string &fileName);
};

#endif // FIRST_RIDE_H
