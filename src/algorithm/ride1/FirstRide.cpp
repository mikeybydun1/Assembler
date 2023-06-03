#include <fstream>
#include <iostream>
#include <string>
#include "FirstRide.h"
#include "utilities.h"
#include "Label.h"

#define DEFAULT_COUNTER_VALUE 0
#define EXTERN_TYPE_VALUE 2
#define DEFAULT_LABEL_VALUE 0
#define DATA_LABEL 0
#define CODE_LABEL 1
#define MAX_LABEL_AMOUNT 100

FirstRide::FirstRide() : IC(DEFAULT_COUNTER_VALUE), DC(DEFAULT_COUNTER_VALUE), labelCounter(DEFAULT_COUNTER_VALUE) {}

int FirstRide::amountLinesInFile(const std::string &fileName) {
    std::ifstream fp(fileName);
    int line_counter = 0;
    std::string buffer;

    while (std::getline(fp, buffer)) {
        line_counter++;
    }
    return line_counter-1;
}

void FirstRide::executeFirstRide(const std::string &fileName) {
    std::ifstream fp(fileName);

    if (!fp) {
        std::cerr << "Unrecognized file: " << fileName << "\n";
        return;
    }
    
    std::string buffer;
    int line_counter = DEFAULT_COUNTER_VALUE;
    std::string label_name;

    while(std::getline(fp, buffer)) {
        if(is_substring(".entry", buffer)) {
            continue;
        }

        removeSpaceFront(buffer);
        removeSpaceTail(buffer);

        int L = sentenceLength(buffer);
        label_name = isLabel(buffer); 

        if(is_substring(".extern", buffer)) {
            buffer.replace(0, 7, "       ");
            removeSpaceFront(buffer); 

            Label ext_label;
            ext_label.setType(EXTERN_TYPE_VALUE);
            ext_label.setValue(DEFAULT_LABEL_VALUE);
            ext_label.setName(buffer);

            labelTable[labelCounter] = ext_label;
            labelCounter += 1;
            continue;           
        }
        else if(label_name[0] == '!') { 
            IC += L;
        }
        else if(label_name[0] != '!' && !is_substring(".extern",buffer)) {   
            if(isInLabelTable(label_name)) {
                if(line_counter != amountLinesInFile(fileName)) {
                    std::cerr << "Line " << line_counter << ":\tLabel error -> the Label '" << label_name << "' already exists\n\n";
                }
                continue;
            }
            else {
                int label_type = labelType(buffer);

                if(label_type == DATA_LABEL) { 
                    Label data_label;
                    std::string label_name1 = isLabel(buffer);

                    data_label.setName(label_name1);
                    data_label.setType(DATA_LABEL);
                    data_label.setValue(DC);

                    DC = DC + L;
                    labelTable[labelCounter] = data_label;
                }
                else if(label_type == CODE_LABEL) { 
                    Label code_label;
                    std::string label_name1 = isLabel(buffer);

                    code_label.setName(label_name1);
                    code_label.setType(CODE_LABEL);
                    code_label.setValue(IC);

                    IC += L; 
                    labelTable[labelCounter] = code_label;
                }
                labelCounter++; 
            }
        }
        line_counter++;
    }

    for(int i = 0; i < MAX_LABEL_AMOUNT; i++) {
        if(labelTable[i].getType() == DATA_LABEL) {
            labelTable[i].setValue(labelTable[i].getValue() + IC);
        }
    }
}  
