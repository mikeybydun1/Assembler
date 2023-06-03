#include "outputFiles.h"
#include "utilities.h"
#include "symbolTable.h"
#include "firstRide.h"
#include "secondRide.h"

#include <fstream>
#include <iostream>
#include <cstring>

void OutputFiles::createBinaryFile(const std::string& file_name) {
    std::ofstream binary_file(file_name);
    if (!binary_file) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    writeToBinaryFile(binary_file, "--- CODE ---", code_arr);
    writeToBinaryFile(binary_file, "--- DATA ---", data_arr);

    binary_file.close();
}

void OutputFiles::createEntFile(const std::string& file_name) {
    bool isEntryLabel = false;
    for (int p = 0; p < MAX_LABEL_AMOUNT; p++) {
        if (labelTable[p].type == ENTRY_LABEL_TYPE) {
            isEntryLabel = true;
            break;
        }
    }

    if (!isEntryLabel) {
        return;
    }

    std::ofstream ent_file(file_name);
    if (!ent_file) {
        std::cerr << "Failed to open file: " << file_name << std::endl;
        return;
    }

    writeEntryLabels(ent_file);

    ent_file.close();
}

void OutputFiles::createObjectAndExtFile(const std::string& file_name_ob, const std::string& file_name_ext) {
    bool isExtLabel = false;
    for (int t = 0; t < MAX_LABEL_AMOUNT; t++) {
        if (labelTable[t].type == EXTERNAL_LABEL_TYPE || labelTable[t].type == -1) {
            isExtLabel = true;
            break;
        }
    }

    std::ofstream ob_file(file_name_ob);
    if (!ob_file) {
        std::cerr << "Failed to open file: " << file_name_ob << std::endl;
        return;
    }

    if (isExtLabel) {
        std::ofstream ext_file(file_name_ext);
        if (!ext_file) {
            std::cerr << "Failed to open file: " << file_name_ext << std::endl;
            return;
        }

        writeAmountToBinaryFile(ob_file, getInstructionsCounter(), getDataCounter());
        writeEntryLabels(ext_file);

        int byte_counter = START_CODE_INDEX;

        for (int i = 0; i < getInstructionsCounter(); i++) {
            if (code_arr[i][9] == '1' && isExtLabel) {
                int ext_index = findFirstExtLabel();

                ext_file << labelTable[ext_index].name << "   ";
                convertByteCounterToBase32(byte_counter, code_arr[i]);
                ext_file << code_arr[i] << std::endl;

                ob_file << code_arr[i] << "   ";
                ob_file << code_arr[i] << std::endl;

                byte_counter++;
            } else {
                ob_file << code_arr[i] << "   ";
                ob_file << code_arr[i] << std::endl;

                byte_counter++;
            }
        }

        for (int j = 0; j < getDataCounter(); j++) {
            convertByteCounterToBase32(byte_counter, data_arr[j]);
            ob_file << data_arr[j] << "   ";
            ob_file << data_arr[j] << std::endl;

            byte_counter++;
        }

        ob_file.close();
        ext_file.close();
    } else {
        writeAmountToBinaryFile(ob_file, getInstructionsCounter(), getDataCounter());
        writeEntryLabels(ob_file);

        int byte_counter = START_CODE_INDEX;

        for (int i = 0; i < getInstructionsCounter(); i++) {
            ob_file << code_arr[i] << "   ";
            ob_file << code_arr[i] << std::endl;

            byte_counter++;
        }

        for (int j = 0; j < getDataCounter(); j++) {
            ob_file << data_arr[j] << "   ";
            ob_file << data_arr[j] << std::endl;

            byte_counter++;
        }

        ob_file.close();
    }
}

void OutputFiles::writeToBinaryFile(std::ofstream& file, const std::string& section_name, const std::string* arr) {
    file << section_name << std::endl;

    int i = 0;
    while (arr[i][0] != 'e') {
        file << arr[i] << std::endl;
        i++;
    }
}

void OutputFiles::writeEntryLabels(std::ofstream& file) {
    bool isEntryLabel = false;
    for (int p = 0; p < MAX_LABEL_AMOUNT; p++) {
        if (labelTable[p].type == ENTRY_LABEL_TYPE) {
            isEntryLabel = true;
            break;
        }
    }

    if (!isEntryLabel) {
        return;
    }

    char base32Chars[3];

    for (int i = 0; i < MAX_LABEL_AMOUNT; i++) {
        if (labelTable[i].type == ENTRY_LABEL_TYPE) {
            file << labelTable[i].name << "   ";

            int label_value = START_CODE_INDEX + labelTable[i].value;
            char binary_str[20] = "0000000000";
            convertByteCounterToBinary(label_value, binary_str);

            char base32[3];
            convertBinaryToBase32WithPadding(binary_str, base32);
            base32Chars[0] = base32[0];
            base32Chars[1] = base32[1];
            base32Chars[2] = '\0';

            file << base32Chars << std::endl;
        }
    }
}

int OutputFiles::findFirstExtLabel() {
    for (int i = 0; i < MAX_LABEL_AMOUNT; i++) {
        if (labelTable[i].type == EXTERNAL_LABEL_TYPE) {
            labelTable[i].type = -1;
            return i;
        }
    }

    return -1;
}

void OutputFiles::convertDecimalToBase32(int decimal, char* base32) {
    static const char base32Chars[] = "0123456789abcdefghijklmnopqrstuvwxyz";

    for (int i = 0; i < 2; i++) {
        base32[i] = base32Chars[decimal % 32];
        decimal /= 32;
    }
}

void OutputFiles::convertBinaryToBase32(const std::string& binary, char* base32) {
    int decimal = binaryToDecimal(binary);
    convertDecimalToBase32(decimal, base32);
}

void OutputFiles::resetBinaryStr(char* binary_str) const {
    for (int i = 0; i < BYTE_LENGTH; i++) {
        binary_str[i] = '0';
    }
}

void OutputFiles::convertByteCounterToBinary(int byte_counter, char* binary_str) const {
    std::string binary = decimalToBinary(byte_counter);
    int copying_counter = BYTE_LENGTH - binary.length();

    for (int i = 0; i < binary.length(); i++) {
        binary_str[copying_counter] = binary[i];
        copying_counter++;
    }
}

void OutputFiles::convertByteCounterToBase32(int byte_counter, char* base32) const {
    char binary_str[BYTE_LENGTH];
    resetBinaryStr(binary_str);
    convertByteCounterToBinary(byte_counter, binary_str);
    convertBinaryToBase32(binary_str, base32);
}

void OutputFiles::convertBinaryToBase32WithPadding(const std::string& binary, char* base32) const {
    std::string padded_binary = binary;
    while (padded_binary.length() < BYTE_LENGTH) {
        padded_binary = "0" + padded_binary;
    }

    convertBinaryToBase32(padded_binary, base32);
}

void OutputFiles::writeAmountToBinaryFile(std::ofstream& file, int code_amount, int data_amount) const {
    char code_amount_base32[3];
    char data_amount_base32[3];
    convertDecimalToBase32(code_amount, code_amount_base32);
    convertDecimalToBase32(data_amount, data_amount_base32);

    file << code_amount_base32[1] << "\t";
    if (data_amount_base32[0] == '!') {
        file << data_amount_base32[1] << std::endl;
    } else {
        file << data_amount_base32 << std::endl;
    }
}

