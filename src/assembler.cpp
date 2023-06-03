/* [mmn 14 : assembler.cpp]:
In this file: The main function of the assembler project

author: Mikey Bar Yaacov Dunevich | Date: 21.8.2022
ID: 215356981 */

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

#include "Utilities.h"
#include "SymbolTable.h"
#include "FirstRide.h"
#include "SecondRide.h"
#include "UtilRide2.h"
#include "Debugger.h"
#include "PreAssembler.h"
#include "OutputFiles.h"
#include "DataUtils.h"

#define LABEL_MAX_AMOUNT 100

// The main function of the project: the function get a .am file names and
// create 3 files - .ob, .ext and .ent file in base 32.
int main(int argc, char* argv[]) {
    
    // The file names
    char file_name[20];
    char ob_file_name[20];
    char ent_file_name[20];
    char ext_file_name[20];
    char bin_file_name[20];

    for(int i = 1; i < argc; i++) {

        // Copy the file name
        strcpy(file_name, argv[i]);
        strcpy(ob_file_name, argv[i]);
        strcpy(ent_file_name, argv[i]);
        strcpy(ext_file_name, argv[i]);
        strcpy(bin_file_name, argv[i]);

        // Add to the file names the file type:
        strcat(file_name, ".am");
        strcat(ob_file_name, ".ob");
        strcat(ent_file_name, ".ent");
        strcat(ext_file_name, ".ext");
        strcat(bin_file_name, ".bin");
        
        std::ifstream file(file_name); // The file stream
        
        // If there is no file with this name - stop the function and return error message
        if(!file) {
            std::cout << "File error: There is no file named as '" << file_name << "'" << std::endl;
            file.close();
            continue;
        }
        file.close();

        std::cout << "\n----- FILE " << i << ": '" << argv[i] << "' -----" << std::endl;

        removeMacro(file_name, "workFile.am"); // PreAssembler - remove and replace the macro in the file using preAssembler.cpp
        bool no_errors = debug("workFile.am"); // Check if there are errors in the file using debugger.cpp

        if(no_errors) { // If there are no errors - continue
            ride1("workFile.am"); // Go over the file and give every label a value using firstRide.cpp
            // Translate the file to binary and check if there were errors during the translation using secondRide.cpp
            bool is_translate_bin_errors = translateFileToBin("workFile.am");

            // If there were no errors during the translation - create object, extern, and entry files
            if(!is_translate_bin_errors) {
                createBinaryFile(bin_file_name);
                createObjectAndExtFile(ob_file_name, ext_file_name);
                createEntFile(ent_file_name);  
                std::cout << "\nThe file '" << argv[i] << "' is a legal assembly file and passed successfully the assembler compilation!" << std::endl;
            }
            else { // Print error message to the user
                std::cout << "There was an error during the translation of the .am file to binary." << std::endl;
            }
        }

        reasetArr(); // Reset the data and code arrays
        // Reset the label table
        for(int j = 0; j < LABEL_MAX_AMOUNT; j++) {
            labelTable[j].name[0] = '\0';
            labelTable[j].value = 0;
            labelTable[j].type = -2;
        }
    }
      
    return 0;
} // End of the function
