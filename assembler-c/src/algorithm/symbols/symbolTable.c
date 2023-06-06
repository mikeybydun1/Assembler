/* [symbolTable.c]:
In this file: The symbol table for all the labels, and also some functions to handle with the symbolTable,
    like check if a label in the symbol table, check if a string is a label and more.

author: Mikey Bar Yaacov Dunevich  
ID: 215356981 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "D:\Desktop\Assembler\assembler-c\src\utils\generalUtils\utilities.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\symbols\symbolTable.h"
#include "D:\Desktop\Assembler\assembler-c\src\utils\dataUtils\dataUtils.h"

#define MAX_LABEL_CHARS 50
#define NOT_IN_LABEL_TABLE -1
#define LABEL_TYPE_DATA 0
#define LABEL_TYPE_EXTERN 2
#define LABEL_TYPE_ENTRY 3
#define LABEL_TYPE_CODE 1



/**
 * Checks if a given string is present in the label table.
 *
 * @param s1 The string to search for in the label table.
 * @return True if the string is found in the label table, false otherwise.
 */
bool isInLabelTabel(char *s1) {
    bool flag = false;
    for(int i = 0; i < MAX_LABEL_AMOUNT; i++) {
        if(strcmp(s1,labelTable[i].name) == 0) {
            return true;
        }
    }
    return flag;
}

/*Gloval string to help functions returns strings*/ 
char labelsNames[MAX_LABEL_CHARS] = "";

/**
 * Checks if a given string represents a label.
 *
 * @param s1 The string to check.
 * @return Returns the label name if the string is a label, or "!" if it is not a label.
 */
char* isLabel(char *s1) {
    for(int i = 0; i < MAX_LABEL_CHARS; i++) {
        labelsNames[i] = ' ';
    }
    if(is_substring(":",s1) == true) 
    {
        int count = 0;
        while(s1[count] != ':') {
            count++;
        }
        for(int i = 0; i < count; i++) {
            labelsNames[i] = s1[i];
        }
        removeSpaceFront(labelsNames);
        removeSpaceTail(labelsNames);
        return labelsNames;
    }
    else {
        return "!";
    }
}

/**
 * Determines the type of a label based on the given string.
 *
 * @param s1 The string to check.
 * @return Returns the label type based on the string.
 */
int labelType(char *s1) {
    if(is_substring(".data",s1) || is_substring(".struct",s1)
        || is_substring(".string",s1)) 
    {
        return LABEL_TYPE_DATA;
    }
    else if(is_substring(".extern",s1)) {
        return LABEL_TYPE_EXTERN;
    }
    else if(is_substring(".entry",s1))
    {
        return LABEL_TYPE_ENTRY;
    }
    else {
        return LABEL_TYPE_CODE;
    }
}

/**
 * Finds the index of a label in the label table based on its name.
 *
 * @param s The name of the label.
 * @return Returns the index of the label in the label table, or NOT_IN_LABEL_TABLE if not found.
 */
int indexInLabelTable(char *s) {
    int index = NOT_IN_LABEL_TABLE;
    for(int i = 0; i < MAX_LABEL_AMOUNT; i++) {
        if(strcmp(s,labelTable[i].name) == 0) {
            return i;
        }
    }
    return index;
}

