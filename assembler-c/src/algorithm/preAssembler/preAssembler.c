/* [preAssembler.c]:
In this file: remove all the macroes in the file and replacing 
thier commands in the right place in the file.

author: Mikey Bar Yaacov Dunevich  
ID: 215356981 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "D:\Desktop\Assembler\assembler-c\src\utils\generalUtils\utilities.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\preAssembler\preAssembler.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\ride1\firstRide.h"
#include "D:\Desktop\Assembler\assembler-c\src\utils\dataUtils\dataUtils.h"

#define MAX_MACRO_NAME 30
#define MAX_MACRO_CODE 1024
#define MAX_BUFFER_SIZE 2048
#define FIRST_LINE 1
#define ZERO_INDEX 0
#define NO_MACROS -1
#define MAX_MACRO_AMOUNT 100

int isInMacroTable(char *s); 

// The struct macro has a name and a code.
struct macro
{
    char name[MAX_MACRO_NAME]; // The macro name
    char code[MAX_MACRO_CODE]; // The macro code
};

struct macro macroTable[MAX_MACRO_AMOUNT]; // Array for store all the macros.

/**
 * @brief Removes macros from a file and creates a new file without macros.
 *
 * This function reads the contents of the file specified by fileWithMacro and removes any macros
 * present in the file. It creates a new file specified by fileWithoutMacro and writes the modified
 * contents without macros into the new file. The function also updates the macroTable with the
 * macro definitions encountered in the file.
 *
 * @param fileWithMacro The name of the file containing macros.
 * @param fileWithoutMacro The name of the file to be created without macros.
 * @return None.
 */
void removeMacro(char *fileWithMacro, char *fileWithoutMacro) {

    FILE *fp = fopen(fileWithMacro,"r");
    FILE *fp2 = fopen(fileWithoutMacro,"w");
    char buffer[MAX_BUFFER_SIZE];

    if(fp == NULL || fp2 == NULL) {
        printf("Error: There is no file...");
        return;
    }
    
    bool isMacro = false; // Flag for knowing if there is a macro
    int line_counter = FIRST_LINE;
    int macroIndex = ZERO_INDEX;
    int amount_lines = amountLinesInFile(fileWithMacro)+1;

    while(feof(fp) == false) {
        buffer[0] = '\0';
        fgets(buffer, 1024, fp);

        if(amount_lines == line_counter && buffer[0] == '\0') {
            break;
        }

        // Clean the line from blank spaces (front and back)
        removeSpaceFront(buffer);
        removeSpaceTail(buffer);



        // There is a macro name in the current line
        if(isInMacroTable(buffer) != NO_MACROS) {
            int thisIndex = isInMacroTable(buffer);
            fprintf(fp2, macroTable[thisIndex].code);
        }

        // There is a macro definition in this line
        if(buffer[0] == 'm' && buffer[1] == 'a' && buffer[2] == 'c'
            && buffer[3] == 'r' && buffer[4] == 'o') {
                isMacro = true;
                buffer[0] = ' '; buffer[1] = ' '; buffer[2] = ' ';
                buffer[3] = ' '; buffer[4] = ' ';
                removeSpaceFront(buffer);

                strcpy(macroTable[macroIndex].name,buffer);
                //strcpy(macroTable[macroIndex].code,"");
        }

        // There is not a 'endmacro' and the isMacro flag is true
        else if(is_substring("endmacro",buffer) == false && isMacro == true) {
                strcat(macroTable[macroIndex].code, buffer);
                strcat(macroTable[macroIndex].code, "\n");
        }

        // Regular line - copying the line to the second file
        if(isInMacroTable(buffer) == NO_MACROS && isMacro == false) {
            removeSpaceFront(buffer);
            if(buffer[0] != ';' && buffer[0] != ' ') {
                fprintf(fp2, buffer);
                if(amount_lines != line_counter) {
                    fprintf(fp2,"\n");
                }
            }
        }

        // End of a macro line - update flag and macroIndex
        else if(buffer[0] == 'e' && buffer[1] == 'n' && buffer[2] == 'd' && 
            buffer[3] == 'm' && buffer[4] == 'a' && buffer[5] == 'c'
            && buffer[6] == 'r' && buffer[7] == 'o') {
            isMacro = false;
            macroIndex++;
        }
        line_counter++; // update the line counter
    }

    fclose(fp); // close the first file
    fclose(fp2); // close the second file
}

/**
 * @brief Checks if a string is present in the macroTable.
 *
 * This function searches for the given string in the macroTable and returns the index of the
 * corresponding macro if found. If the string is not found in the macroTable, it returns NO_MACROS.
 *
 * @param s The string to search for in the macroTable.
 * @return The index of the macro in the macroTable if found, or NO_MACROS if not found.
 */
int isInMacroTable(char *s) {
    int num = NO_MACROS;
    for(int i = 0; i < MAX_MACRO_AMOUNT; i++) {
        if(is_substring(s,macroTable[i].name)) {
            num = i;
        } 
    }
    return num;
}

