#include <iostream>
#include <fstream>

#include "DataUtils.h"
#include "SymbolTable.h"
#include "Utilities.h"
#include "FirstRide.h"
#include "PreAssembler.h"
#include "Debugger.h"

#define DEFULT_LINE_COUNTER 1
#define BUFFER_MAX_SIZE 2048

// Global var for the label name
std::string label_name;

bool Debugger::debug(std::string file_name) {
    bool flag = true;
    std::ifstream fp(file_name.c_str());
    if(!fp.is_open()) {
        std::cout << "unrecognized file: " << file_name << "\n";
        return false;
    }

    std::string buffer;
    int line_counter = DEFULT_LINE_COUNTER;
    
    while(std::getline(fp, buffer)) {
        Utilities::removeSpaceFront(buffer);
        Utilities::removeSpaceTail(buffer);

        // Get the label name and instore in 'label_name' pointer
        std::string label_name = Utilities::isLabel(buffer);

        if(!Utilities::is_substring(".entry",buffer) && !Utilities::is_substring(".extern",buffer)) // Not a entry or extern
        {
            // check if it is a data or string or struct without a label:
            if((Utilities::is_substring(".data",buffer) || Utilities::is_substring(".struct",buffer)
                || Utilities::is_substring(".string",buffer)) && label_name.compare("!") == 0) 
            {
                flag = false;
                std::cout << "Line " << line_counter << ":\t Data declaration error -> data/string/struct must have a label.\n\n";
            }
            else if(!Utilities::is_substring(".data",buffer) && !Utilities::is_substring(".string",buffer)
                && !Utilities::is_substring(".struct",buffer))
            { // it is a command (with or without a label before it)

                if(label_name.compare("!") != 0) { // If there is a label - remove it
                    for(size_t count = 0; count < buffer.size() && buffer[count] != ':'; count++) {
                        buffer[count] = ' ';
                    }
                    Utilities::removeSpaceFront(buffer);
                }

                // checking if the command is legal:   
                std::string command_name = "aaa";
                command_name[0] = buffer[0];
                command_name[1] = buffer[1];
                command_name[2] = buffer[2];

                if(command_name[0] == 's' && command_name[1] == 't' && command_name[2] == 'o') {
                    command_name[3] = buffer[3];
                    command_name[4] = '\0';
                }      
                
                if(Utilities::getCommandNumber(command_name) == 16) {
                    flag = false;
                    std::cout << "Line " << line_counter << ":\tCommand type error " << command_name << " -> not a recognized command.\n\n";
                }

                else 
                { // legal command

                    // checking arguments amount of the current command:
                    int arg_amount = Utilities::amountInString(buffer,',') + 1;
                    
                    if(command_name.compare("rts") == 0 || command_name.compare("stop") == 0) {
                        arg_amount = 0;
                    }
                        

                    if(arg_amount != Utilities::argAmount(command_name)) 
                    {
                        flag = false;
                        std::cout << "Line " << line_counter << ":\t Arguments amount error -> the command '" << command_name << "' needs " << Utilities::argAmount(command_name) << " args\n";
                        std::cout << "         but you enter " << arg_amount << ".\n\n";
                    }

                    // Check if the addressing mode is legal:
                    bool isAddressingLegal = Utilities::isAddressingTypeOk(command_name,buffer);
                    if(isAddressingLegal == false) {
                        flag = false;
                        std::cout << "Line " << line_counter << "\t Addressing mode error in the arguments of the command '" << command_name << "'.\n\n";
                    }
                }
            }
        }
        
        else if(label_name.compare("!") != 0) // A label
        { 
            if(Utilities::getCommandNumber(label_name) != 16) {
                std::cout << "Label error in line: " << line_counter << " -> The label name is a command name\n";   
                flag = false; 
            }
        }
        line_counter++; // Update the line counter
    }
    
    fp.close(); // Close the file pointer
    return flag; // Return the flag that says if there was errors in the file
}
