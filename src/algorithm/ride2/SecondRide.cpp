#include "secondRide.h"
#include "Ride2Utils.h"

int ic1 = COUNTERS_DEFULT_VALUE;
int dc1 = COUNTERS_DEFULT_VALUE;
int line_counter = FIRST_LINE_VALUE;
bool is_errors = false;
std::vector<std::string> code_arr(MAX_BYTES, "0000000000"), data_arr(MAX_BYTES, "0000000000");

void reasetArr() {
    std::fill(code_arr.begin(), code_arr.end(), "0000000000");
    std::fill(data_arr.begin(), data_arr.end(), "0000000000");
}

bool translateFileToBin(std::string file_name) {
    std::ifstream fp(file_name); 

    if(fp.fail()) {
        std::cout << "unrecognized file: " << file_name << std::endl;
        is_errors = false;
        return true;
    }

    reasetArr();

    std::string buffer;
    while(std::getline(fp, buffer)) {
        removeSpaceFront(buffer);
        removeSpaceTail(buffer);

        int L = sentenceLength(buffer); 
        std::string label_name = isLabel(buffer); 

        if(is_substring(".extern",buffer)) 
            continue;

        if(is_substring(".entry",buffer)) { 
            buffer = buffer.substr(6);
            removeSpaceFront(buffer);

            bool isExsitingLabel = isInLabelTabel(buffer);
            if(!isExsitingLabel) {
                std::cout << "Line " << line_counter << ":\tEntry error -> the label '" << buffer << "' doesn't exists\n\n";
                is_errors = true;
                break;
            }
            else {
                int label_index = indexInLabelTable(buffer);
                labelTable[label_index].type = ENTRY_LABEL_TYPE;

                for(int i = 0; i < MAX_LABEL_AMOUNT; i++) {
                    if(labelTable[i].type != LABEL_EXTERN_TYPE)
                        labelTable[i].value -= 0;
                }
            }
        }
        else {
            if(label_name[0] != '!' && is_substring(".data",buffer) == false
                && is_substring(".string",buffer) == false && is_substring(".struct",buffer) == false)
            { 
                int count = 0;
                while(buffer[count] != ':') {
                    buffer[count] = ' ';
                    count++;
                }
                buffer[count] = ' ';
                removeSpaceFront(buffer);
            }

            translateLineToBinary(buffer); 
            
            if(is_substring(".data",buffer) == true || is_substring(".string",buffer) == true
                || is_substring(".struct",buffer) == true) 
            {
                dc1 += L;
            }
            else 
            {
                ic1 += L;
            }   
        }
        line_counter++;
    }

    code_arr[ic1][0] = 'e'; 
    data_arr[dc1][0] = 'e';

    ic1 = COUNTERS_DEFULT_VALUE;
    dc1 = COUNTERS_DEFULT_VALUE;

    if(is_errors == true) {
        is_errors = false;
        return true;
    }
    else {
        return false;
    }
}

void translateLineToBinary(char* line) {

    char* label_name = isLabel(line);

    if (is_substring(".entry", line) == true || is_substring(".extern", line) == true) {
        return;
    }

    if (label_name[0] == '!' && is_substring(".entry", line) == false && is_substring(".extern", line) == false) {

        char command_name[4];
        strcpy(command_name, getCommand(line));

        int command_number = getCommandNumber(command_name);
        int command_binary = decimalToBinary(command_number);

        char command_str[BYTE_FULL_SIZE] = { 0 };
        my_itoa(command_binary, command_str);

        if (strlen(command_str) == 4) {
            code_arr[ic1][0] = command_str[0];
            code_arr[ic1][1] = command_str[1];
            code_arr[ic1][2] = command_str[2];
            code_arr[ic1][3] = command_str[3];
        }
        else if (strlen(command_str) == 3) {
            code_arr[ic1][1] = command_str[0];
            code_arr[ic1][2] = command_str[1];
            code_arr[ic1][3] = command_str[2];
        }
        else if (strlen(command_str) == 2) {
            code_arr[ic1][2] = command_str[0];
            code_arr[ic1][3] = command_str[1];
        }
        else if (strlen(command_str) == 1) {
            code_arr[ic1][3] = command_str[0];
        }

        if (is_substring(",", line) == false) {

            char* first_arg = getOnlyArg(line);
            int addressing_type = getAddressingType(first_arg);

            if (strcmp("stop", line) == 0) {
                first_arg = "";
                addressing_type = -1;
                ic1--;
            }

            if (addressing_type == 3) {
                code_arr[ic1][6] = '1';
                code_arr[ic1][7] = '1';

                char reg_bin[4];
                strcpy(reg_bin, getRegisterBainry(first_arg));

                code_arr[ic1 + 1][0] = reg_bin[0];
                code_arr[ic1 + 1][1] = reg_bin[1];
                code_arr[ic1 + 1][2] = reg_bin[2];
                code_arr[ic1 + 1][3] = reg_bin[3];
            }
            else if (isInLabelTabel(first_arg) == true && addressing_type != -1) {
                code_arr[ic1][7] = '1';

                int label_index = indexInLabelTable(first_arg);
                int label_value = labelTable[label_index].value;

                if (labelTable[label_index].type != 2 && labelTable[label_index].type != -1)
                    label_value += START_CODE_PLACE;

                int label_value_bin = decimalToBinary(label_value);

                char label_bin_str[] = { 0 };
                my_itoa(label_value_bin, label_bin_str);

                int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(label_bin_str);
                for (int i = 0; i < strlen(label_bin_str); i++) {
                    code_arr[ic1 + 1][bin_counter] = label_bin_str[i];
                    bin_counter++;
                }

                if (labelTable[label_index].type == 2 || labelTable[label_index].type == -1)
                    code_arr[ic1 + 1][9] = '1';
                else
                    code_arr[ic1 + 1][8] = '1';
            }
            else if (is_substring(".", first_arg) == true) {
                code_arr[ic1][6] = '1';

                removeSpaceFront(first_arg);
                removeSpaceTail(first_arg);

                int number = atoi(&first_arg[strlen(first_arg) - 1]);
                int bin_number = decimalToBinary(number);
                char bin_str[BYTE_FULL_SIZE] = { 0 };

                my_itoa(bin_number, bin_str);

                int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(bin_str);
                for (int i = 0; i < strlen(bin_str); i++) {
                    code_arr[ic1 + 2][bin_counter] = bin_str[i];
                    bin_counter++;
                }

                char dev[] = ".";
                char* label_name = strtok(first_arg, dev);

                if (isInLabelTabel(label_name) == false) {
                    printf("Line: %d\tLabel error -> '%s' doesn't exist\n\n", line_counter, label_name);
                    is_errors = true;
                }
                else {
                    int label_index = indexInLabelTable(first_arg);
                    int label_value = START_CODE_PLACE + labelTable[label_index].value;

                    int label_value_bin = decimalToBinary(label_value);

                    char label_bin_str[] = { 0 };
                    my_itoa(label_value_bin, label_bin_str);

                    int bin_counter1 = BYTE_LABEL_WITHOUT_ARE - strlen(label_bin_str);
                    for (int i = 0; i < strlen(label_bin_str); i++) {
                        code_arr[ic1 + 1][bin_counter1] = label_bin_str[i];
                        bin_counter1++;

                    }
                }

                code_arr[ic1 + 1][8] = '1';
            }
            else if (addressing_type == 0) {

                if (is_substring("-", first_arg) == true) {
                    removeSpaceFront(first_arg);
                    removeSpaceTail(first_arg);
                    negativNumberToBin(first_arg, false, ic1 + 1);
                }
                else {
                    first_arg[0] = ' ';
                    removeSpaceFront(first_arg);

                    int bin_num = decimalToBinary(atoi(first_arg));
                    char bin_str[] = { 0 };
                    my_itoa(bin_num, bin_str);

                    int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(bin_str);
                    for (int i = 0; i < strlen(bin_str); i++) {
                        code_arr[ic1 + 1][bin_counter] = bin_str[i];
                        bin_counter++;
                    }
                }
            }
            else {
                if (first_arg != "") {
                    printf("Line %d\tError: unrecognized argument '%s'\n\n", line_counter, first_arg);
                    is_errors = true;
                }
            }
        }
        else {

            char* first_arg = getFirstArg(line);
            char* second_arg = getSecondArg(line);
            bool isFirstArgHasPoint = false;

            int addressing_type_first = getAddressingType(first_arg);
            int addressing_type_second = getAddressingType(second_arg);

            if (addressing_type_first == 3 && addressing_type_second == 3) {
                code_arr[ic1][4] = '1';
                code_arr[ic1][5] = '1';

                char reg_bin[4];
                strcpy(reg_bin, getRegisterBainry(first_arg));

                code_arr[ic1 + 1][0] = reg_bin[0];
                code_arr[ic1 + 1][1] = reg_bin[1];
                code_arr[ic1 + 1][2] = reg_bin[2];
                code_arr[ic1 + 1][3] = reg_bin[3];

                code_arr[ic1][6] = '1';
                code_arr[ic1][7] = '1';

                char reg_bin1[4];
                strcpy(reg_bin1, getRegisterBainry(second_arg));

                code_arr[ic1 + 1][4] = reg_bin1[0];
                code_arr[ic1 + 1][5] = reg_bin1[1];
                code_arr[ic1 + 1][6] = reg_bin1[2];
                code_arr[ic1 + 1][7] = reg_bin1[3];
                return;
            }

            if (addressing_type_first == 3) {
                code_arr[ic1][4] = '1';
                code_arr[ic1][5] = '1';

                char reg_bin[4];
                strcpy(reg_bin, getRegisterBainry(first_arg));

                code_arr[ic1 + 1][0] = reg_bin[0];
                code_arr[ic1 + 1][1] = reg_bin[1];
                code_arr[ic1 + 1][2] = reg_bin[2];
                code_arr[ic1 + 1][3] = reg_bin[3];
            }
            else if (addressing_type_first == 0) {

                if (is_substring("-", first_arg) == true) {

                    removeSpaceFront(first_arg);
                    removeSpaceTail(first_arg);


                    negativNumberToBin(first_arg, false, ic1 + 1);
                }

                else {

                    first_arg[0] = ' ';
                    removeSpaceFront(first_arg);

                    int bin_num = decimalToBinary(atoi(first_arg));
                    char bin_str[] = { 0 };
                    my_itoa(bin_num, bin_str);

                    int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(bin_str);
                    for (int i = 0; i < strlen(bin_str); i++) {
                        code_arr[ic1 + 1][bin_counter] = bin_str[i];
                        bin_counter++;
                    }
                }
            }
            else if (isInLabelTabel(first_arg) == true) {

                code_arr[ic1][5] = '1';

                int label_index1 = indexInLabelTable(first_arg);
                int label_value1 = labelTable[label_index1].value;

                if (labelTable[label_index1].type != 2)
                    label_value1 += START_CODE_PLACE;

                int label_value_bin1 = decimalToBinary(label_value1);

                char label_bin_str1[] = { 0 };
                my_itoa(label_value_bin1, label_bin_str1);

                int bin_counter1 = BYTE_LABEL_WITHOUT_ARE - strlen(label_bin_str1);
                for (int i = 0; i < strlen(label_bin_str1); i++) {
                    code_arr[ic1 + 1][bin_counter1] = label_bin_str1[i];
                    bin_counter1++;
                }

                if (labelTable[label_index1].type == 2)
                    code_arr[ic1 + 1][9] = '1';
                else
                    code_arr[ic1 + 1][8] = '1';
            }
            else if (is_substring(".", first_arg) == true) {

                isFirstArgHasPoint = true;

                code_arr[ic1][4] = '1';

                removeSpaceFront(first_arg);
                removeSpaceTail(first_arg);

                int number = atoi(&first_arg[strlen(first_arg) - 1]);
                int bin_number = decimalToBinary(number);
                char bin_str[BYTE_FULL_SIZE] = { 0 };

                my_itoa(bin_number, bin_str);

                int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(bin_str);
                for (int i = 0; i < strlen(bin_str); i++) {
                    code_arr[ic1 + 2][bin_counter] = bin_str[i];
                    bin_counter++;
                }

                char dev[] = ".";
                char* label_name = strtok(first_arg, dev);

                if (isInLabelTabel(label_name) == false) {
                    printf("Line: %d\tLabel error -> '%s' doesn't exist\n\n", line_counter, label_name);
                    is_errors = true;
                }
                else {
                    int label_index = indexInLabelTable(first_arg);
                    int label_value = START_CODE_PLACE + labelTable[label_index].value;

                    int label_value_bin = decimalToBinary(label_value);

                    char label_bin_str[] = { 0 };
                    my_itoa(label_value_bin, label_bin_str);

                    int bin_counter1 = BYTE_LABEL_WITHOUT_ARE - strlen(label_bin_str);
                    for (int i = 0; i < strlen(label_bin_str); i++) {
                        code_arr[ic1 + 1][bin_counter1] = label_bin_str[i];
                        bin_counter1++;

                    }
                }

                code_arr[ic1 + 1][8] = '1';
            }
            else {
                printf("Line %d\tError: unrecognized argument '%s'\n\n", line_counter, first_arg);
                is_errors = true;
            }

            if (addressing_type_second == 3) {

                if (isFirstArgHasPoint == false) {
                    code_arr[ic1][6] = '1';
                    code_arr[ic1][7] = '1';
                }

                char reg_bin[4];
                strcpy(reg_bin, getRegisterBainry(second_arg));

                code_arr[ic1 + 1][4] = reg_bin[0];
                code_arr[ic1 + 1][5] = reg_bin[1];
                code_arr[ic1 + 1][6] = reg_bin[2];
                code_arr[ic1 + 1][7] = reg_bin[3];
            }
            else if (addressing_type_second == 0) {

                if (is_substring("-", second_arg) == true) {

                    removeSpaceFront(second_arg);
                    removeSpaceTail(second_arg);

                    negativNumberToBin(second_arg, true, ic1 + 1);
                }
                else {

                    second_arg[0] = ' ';
                    removeSpaceFront(second_arg);

                    int bin_num = decimalToBinary(atoi(second_arg));
                    char bin_str[] = { 0 };
                    my_itoa(bin_num, bin_str);

                    int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(bin_str);
                    for (int i = 0; i < strlen(bin_str); i++) {
                        code_arr[ic1 + 1][bin_counter] = bin_str[i];
                        bin_counter++;
                    }
                }
            }
            else if (isInLabelTabel(second_arg) == true) {

                code_arr[ic1][7] = '1';

                int label_index2 = indexInLabelTable(second_arg);
                int label_value2 = labelTable[label_index2].value;

                if (labelTable[label_index2].type != 2)
                    label_value2 += START_CODE_PLACE;

                int label_value_bin2 = decimalToBinary(label_value2);

                char label_bin_str2[] = { 0 };
                my_itoa(label_value_bin2, label_bin_str2);

                int bin_counter2 = BYTE_LABEL_WITHOUT_ARE - strlen(label_bin_str2);
                for (int i = 0; i < strlen(label_bin_str2); i++) {
                    code_arr[ic1 + 1][bin_counter2] = label_bin_str2[i];
                    bin_counter2++;
                }

                if (labelTable[label_index2].type == 2)
                    code_arr[ic1 + 1][9] = '1';
                else
                    code_arr[ic1 + 1][8] = '1';
            }
            else if (is_substring(".", second_arg) == true) {

                code_arr[ic1][7] = '1';

                removeSpaceFront(second_arg);
                removeSpaceTail(second_arg);

                int number = atoi(&second_arg[strlen(second_arg) - 1]);
                int bin_number = decimalToBinary(number);
                char bin_str[BYTE_FULL_SIZE] = { 0 };

                my_itoa(bin_number, bin_str);

                int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(bin_str);
                for (int i = 0; i < strlen(bin_str); i++) {
                    code_arr[ic1 + 2][bin_counter] = bin_str[i];
                    bin_counter++;
                }

                char dev[] = ".";
                char* label_name = strtok(second_arg, dev);

                if (isInLabelTabel(label_name) == false) {
                    printf("Line: %d\tLabel error -> '%s' doesn't exist\n\n", line_counter, label_name);
                    is_errors = true;
                }
                else {
                    int label_index = indexInLabelTable(second_arg);
                    int label_value = START_CODE_PLACE + labelTable[label_index].value;

                    int label_value_bin = decimalToBinary(label_value);

                    char label_bin_str[] = { 0 };
                    my_itoa(label_value_bin, label_bin_str);

                    int bin_counter1 = BYTE_LABEL_WITHOUT_ARE - strlen(label_bin_str);
                    for (int i = 0; i < strlen(label_bin_str); i++) {
                        code_arr[ic1 + 1][bin_counter1] = label_bin_str[i];
                        bin_counter1++;

                    }
                }

                code_arr[ic1 + 1][8] = '1';
            }
            else {
                printf("Line %d\tError: unrecognized argument '%s'\n\n", line_counter, second_arg);
                is_errors = true;
            }
        }
    }
}

void negativNumberToBin(char* arg, bool isSecond, int row)
{
    arg[0] = ' ';
    removeSpaceFront(arg);

    int bin_num = decimalToBinary(atoi(arg));
    char bin_str[] = { 0 };
    my_itoa(bin_num, bin_str);

    int bin_counter = BYTE_LABEL_WITHOUT_ARE - strlen(bin_str);
    for (int i = 0; i < strlen(bin_str); i++) {
        code_arr[row][bin_counter] = bin_str[i];
        bin_counter++;
    }

    if (isSecond == true)
        code_arr[row][5] = '1';
    else
        code_arr[row][6] = '1';
}