#ifndef OUTPUTFILES_H
#define OUTPUTFILES_H

#include <string>

class OutputFiles {
public:
    void createBinaryFile(const std::string& file_name);
    void createEntFile(const std::string& file_name);
    void createObjectAndExtFile(const std::string& file_name_ob, const std::string& file_name_ext);

private:
    static const int MAX_LABEL_AMOUNT = 100;
    static const int EXTERNAL_LABEL_TYPE = 2;
    static const int ENTRY_LABEL_TYPE = 3;
    static const int BYTE_LENGTH = 10;
    static const int START_CODE_INDEX = 100;
    static const int DEFAULT_COUNTER_VALUE = 0;

    void writeToBinaryFile(std::ofstream& file, const std::string& section_name, const std::string* arr);
    void writeEntryLabels(std::ofstream& file);
    int findFirstExtLabel();
    void convertDecimalToBase32(int decimal, char* base32);
    void convertBinaryToBase32(const std::string& binary, char* base32);
    void resetBinaryStr(char* binary_str) const;
    void convertByteCounterToBinary(int byte_counter, char* binary_str) const;
    void convertByteCounterToBase32(int byte_counter, char* base32) const;
    void convertBinaryToBase32WithPadding(const std::string& binary, char* base32) const;
    void writeAmountToBinaryFile(std::ofstream& file, int code_amount, int data_amount) const;
};

#endif  // OUTPUTFILES_H
