#include <cstdint>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "../utils/ride2Utils/Ride2Utils.h"
#include "../utils/generalUtils/Utilities.h"
#include "LabelTable.h"
#include "FirstRide.h"
#include "PreAssembler.h"
#include "SecondRide.h"
#include "debugger.h"
#include "dataUtils.h"
#include "outputFiles.h"

#define COUNTERS_DEFULT_VALUE 0
#define FIRST_LINE_VALUE 1
#define MAX_BYTES 2048
#define START_CODE_PLACE 100
#define DECIMAL_BASE 10
#define BYTE_FULL_SIZE 10
#define MAX_LABEL_AMOUNT 100
#define BYTE_LABEL_WITHOUT_ARE 8
#define MAX_BUFFER_SIZE 2048
#define ENTRY_LABEL_TYPE 3
#define LABEL_EXTERN_TYPE 2

extern int ic1;
extern int dc1;
extern int line_counter;
extern bool is_errors;
extern std::vector<std::string> code_arr, data_arr;

void reasetArr();
bool translateFileToBin(std::string file_name);
void translateLineToBinary(char* line);
void negativNumberToBin(char* arg, bool isSecond, int row);

