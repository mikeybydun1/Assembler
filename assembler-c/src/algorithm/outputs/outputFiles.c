/* [outputFiles.c]:
In this file: 2 functions for creating object, extern and entry files.

author: Mikey Bar Yaacov Dunevich  
ID: 215356981 */

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdbool.h>

#include "D:\Desktop\Assembler\assembler-c\src\algorithm\preAssembler\preAssembler.h"
#include "D:\Desktop\Assembler\assembler-c\src\utils\generalUtils\utilities.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\symbols\symbolTable.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\ride1\firstRide.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\ride2\secondRide.h"
#include "D:\Desktop\Assembler\assembler-c\src\utils\ride2Utils\utilRide2.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\debugger\debugger.h"
#include "D:\Desktop\Assembler\assembler-c\src\algorithm\outputs\outputFiles.h"
#include "D:\Desktop\Assembler\assembler-c\src\utils\dataUtils\dataUtils.h"

#define MAX_LABEL_AMOUNT 100
#define EXTERNAL_LABEL_TYPE 2
#define ENTRY_LABEL_TYPE 3
#define BYTE_LENGTH 10
#define START_CODE_INDEX 100
#define DEFULT_COUNTER_VALUE 0

/**
 * @brief Creates a binary file containing the source assembly code, code segment, and data segment.
 *
 * This function generates a binary file based on the provided source assembly code and the code/data segments.
 * It writes the contents of the source assembly code, code segment, and data segment into the binary file.
 *
 * @param file_name The name of the binary file to be created.
 * @return None.
 */
void createBinaryFile(char *file_name) {

    FILE* fp = fopen(file_name,"w");
    FILE* work_file = fopen("workFile.am","r");
    
    int ic3 = 0;
    int dc3 = 0;
    char buffer[2048];
    int counter = 0;

    fprintf(fp,"--------- 💻SORCE ASSEMBLY CODE💻 ---------\n");
    while(feof(work_file) == false) {
        buffer[0] = '\0';
        fgets(buffer,80,work_file);
        if(buffer[0] != '\0') {
            if(counter < 10)
                fprintf(fp,"Line %d:  %s",counter,buffer);
            else
                fprintf(fp,"Line %d: %s",counter,buffer);
        }
            
        counter++;
    }
    fprintf(fp,"\n\n");

    fprintf(fp,"--------- CODE SEGMENT (Binary) ---------\n");
    while(code_arr[ic3][0] != 'e') {

        if(ic3 < 10)
            fprintf(fp,"Line %d:   ",ic3);
        else
            fprintf(fp,"Line %d:  ",ic3);
        fprintf(fp,code_arr[ic3]);
        fprintf(fp,"\n");
        ic3++;
    }
    fprintf(fp,"\n--------- DATA SEGMENT (Binary) ---------\n");
    while(data_arr[dc3][0] != 'e') {

        if(dc3 < 10)
            fprintf(fp,"Line %d:   ",dc3);
        else
            fprintf(fp,"Line %d:  ",dc3);
        fprintf(fp,data_arr[dc3]);
        fprintf(fp,"\n");
        dc3++;
    }

    return;
}

/**
 * @brief Creates an entry (.ent) file containing the entry labels and their corresponding values.
 *
 * This function checks if there are any entry labels in the label table and creates an entry file
 * (specified by the file_name) that lists the entry labels and their corresponding values in base 32.
 * Each entry label is written in the format "<label_name>   <base_32_value>".
 *
 * @param file_name The name of the entry file to be created.
 * @return None.
 */
void createEntFile(char *file_name) {

    // Check if there is a entry label in the label table
    bool isEntryLabel = false; 
    for(int p = 0; p < MAX_LABEL_AMOUNT; p++) {
        if(labelTable[p].type == ENTRY_LABEL_TYPE) {
            isEntryLabel = true;
        }
    }

    if(isEntryLabel == false) 
    { // If there is no entry labels - stop the function befor creating the .ent file
        return;
    }
        
    FILE *ent_file = fopen(file_name,"w");

    if(ent_file == NULL) {
        printf("Unrecognized file '%s'\n",file_name);
    }

    char bin_str[10] = {0};
    char byte[] = "0000000000";
    int bin_value;
    int label_value;
    int bin_counter;

    char base32Chars[2];
    bool first_entry = true;

    for(int i = 0; i < sizeof(labelTable)/sizeof(labelTable[0]); i++) {
        
        // Check if the label type is an entry label
        if(labelTable[i].type == ENTRY_LABEL_TYPE)
        {
            // Pushing to the file the entry label name
            fprintf(ent_file,labelTable[i].name);
            fprintf(ent_file,"   ");

            // Finding the entry label value in base 32 and push to the file
            label_value = START_CODE_INDEX + labelTable[i].value;
            bin_value = decimalToBinary(label_value);
           
            my_itoa(bin_value,bin_str);

            bin_counter = 10 - strlen(bin_str);
            for(int j = 0; j < strlen(bin_str); j++) {
                byte[bin_counter] = bin_str[j];
                bin_counter++;
            }

            binaryTo32Base(byte,base32Chars);
            base32Chars[2] = '\0';

            fputc(base32Chars[0],ent_file);
            fputc(base32Chars[1],ent_file);
            fprintf(ent_file,"\n");

            /* 
            if(first_entry == true) {
                base32Chars[0] = base32Chars[1];
                fprintf(ent_file,base32Chars);
                first_entry = false;
            }
            */

            // Reaset the byte array for the next entry label
            byte[0] = '0'; byte[1] = '0'; byte[2] = '0'; byte[3] = '0'; byte[4] = '0'; 
            byte[5] = '0'; byte[6] = '0'; byte[7] = '0'; byte[8] = '0'; byte[9] = '0'; 

        }
    }
    fclose(ent_file); // Close the file pointer
   
}

/**
 * @brief Creates an object (.ob) file and an external (.ext) file based on the code and data segments.
 *
 * This function checks if there are any external labels in the label table and creates an object file
 * (specified by file_name_ob) and an external file (specified by file_name_ext). The object file contains
 * the code and data segments in base 32 format, while the external file lists the external labels and their
 * corresponding addresses in base 32. The function also handles writing the amount of memory bytes in the
 * code and data segments to the object file.
 *
 * @param file_name_ob The name of the object file to be created.
 * @param file_name_ext The name of the external file to be created.
 * @return None.
 */
void createObjectAndExtFile(char *file_name_ob, char *file_name_ext) {

    bool isExtLabel = false;
    for(int t = 0; t < MAX_LABEL_AMOUNT; t++) {
        if(labelTable[t].type == EXTERNAL_LABEL_TYPE || labelTable[t].type == -1) {
            isExtLabel = true;
        }

    }

    // Create the file pointers
    FILE *ob_file = fopen(file_name_ob,"w");
    if(isExtLabel == true) { // There is a extern label
        FILE *ext_file = fopen(file_name_ext,"w");;
        
        // Instructions and data counters
        int ic2 = DEFULT_COUNTER_VALUE; 
        int dc2 = DEFULT_COUNTER_VALUE;

        char code32[2];
        char data32[2];

        int byte_counter = START_CODE_INDEX;
        int bin_byte_counter;
        
        char bin_str[] = {0};
        char bin_byte_str[20] = "0000000000";
        int copying_counter;

        // char arrays for the code and data counter in base 32
        char code_counter[2];
        char data_counter[2];

        // flag for check if it is the first line
        bool first_line = true;

        // Finding the amount of memory bytes in the code and data arrays
        while(code_arr[ic2][0] != 'e')
            ic2++;
        while(data_arr[dc2][0] != 'e')
            dc2++;
        
        // Translate this amount number to base 32 and push to the .ob file in the first line
        int code_byte_amount = decimalToBinary(ic2);
        int data_byte_amount = decimalToBinary(dc2);

        char code_amount_base32[2];
        char data_amount_base32[2];

        char code_byte_amount_str[] = {0};
        char data_byte_amount_str[] = {0};
        char code_amount_buffer[20] = "0000000000";
        char data_amount_buffer[20] = "0000000000";

        my_itoa(code_byte_amount,code_byte_amount_str);
        int code_amount_counter = 10 - strlen(code_byte_amount_str);
        for(int d = 0; d < strlen(code_byte_amount_str); d++) {
            code_amount_buffer[code_amount_counter] = code_byte_amount_str[d];
            code_amount_counter++;
        }
        binaryTo32Base(code_amount_buffer,code_amount_base32);

        
        my_itoa(data_byte_amount,data_byte_amount_str);
        int data_amount_counter = 10 - strlen(data_byte_amount_str);
        for(int t = 0; t < strlen(data_byte_amount_str); t++) {
            data_amount_buffer[data_amount_counter] = data_byte_amount_str[t];
            data_amount_counter++;
        }
        binaryTo32Base(data_amount_buffer,data_amount_base32);

        code_amount_base32[2] = '\0';
        fputc(code_amount_base32[1],ob_file);
        fputc('\t',ob_file);

        if(data_amount_base32[0] == '!') {
            fputc(data_amount_base32[1],ob_file);
            fputc('\n',ob_file);
        }
        else {
            fputc(data_amount_base32[0],ob_file);
            fputc(data_amount_base32[1],ob_file);
            fputc('\n',ob_file);
        }

        // Reaset the counters
        ic2 = DEFULT_COUNTER_VALUE;
        dc2 = DEFULT_COUNTER_VALUE;
        

        // Going over the code till the end ('e' in the MSB)
        while(code_arr[ic2][0] != 'e')
        {
            bin_byte_counter = decimalToBinary(byte_counter);
            my_itoa(bin_byte_counter,bin_str);

            copying_counter = 10 - strlen(bin_str);
            for(int i = 0; i < strlen(bin_str); i++) {
                bin_byte_str[copying_counter] = bin_str[i];
                copying_counter++;
            }

            binaryTo32Base(bin_byte_str,code_counter);
            code_counter[2] = '\0';


            if(code_arr[ic2][9] == '1' && isExtLabel == true) { // push to extern file
                int ext_index = firstExtLabel();

                fprintf(ext_file,labelTable[ext_index].name);
                fprintf(ext_file,"   ");

                fputc(code_counter[0],ext_file);
                fputc(code_counter[1],ext_file);
                //fprintf(ext_file,code_counter);
                fprintf(ext_file,"\n");

                binaryTo32Base(code_arr[ic2],code32);
                code32[2] = '\0';
                
                fputc(code_counter[0],ob_file);
                fputc(code_counter[1],ob_file);
                
                //fprintf(ob_file,code_counter);
                
                fprintf(ob_file,"   ");

                fputc(code32[0],ob_file);
                fputc(code32[1],ob_file);
                
                fprintf(ob_file,"\n");

                byte_counter++;
                ic2++;
            }

            else { // Not an extern label
                binaryTo32Base(code_arr[ic2],code32);
                code32[2] = '\0';
                
                fputc(code_counter[0],ob_file);
                fputc(code_counter[1],ob_file);
                
                //fprintf(ob_file,code_counter);
                
                fprintf(ob_file,"   ");

                fputc(code32[0],ob_file);
                fputc(code32[1],ob_file);
                
                fprintf(ob_file,"\n");

                ic2++;
                byte_counter++;
                
                for(int j = 0; j < 10; j++) {
                    bin_byte_str[j] = '0';
                }
            }
        }

        // Going over the data till the end ('e' in the MSB)
        while(data_arr[dc2][0] != 'e')
        {
            bin_byte_counter = decimalToBinary(byte_counter);
            my_itoa(bin_byte_counter,bin_str);

            copying_counter = BYTE_LENGTH - strlen(bin_str);
            for(int i = 0; i < strlen(bin_str); i++) {
                bin_byte_str[copying_counter] = bin_str[i];
                copying_counter++;
            }

            binaryTo32Base(bin_byte_str,data_counter);
            data_counter[2] = '\0';

            binaryTo32Base(data_arr[dc2],data32);
            data32[2] = '\0';
            
            /*
            if(first_line == true) {
                fprintf(ob_file,data_counter);
                data_counter[0] = data_counter[1];
                fprintf(ob_file,data_counter);

                first_line = false;
            }
            */
            
            fputc(data_counter[0],ob_file);
            fputc(data_counter[1],ob_file);
            
            fprintf(ob_file,"   ");

            fputc(data32[0],ob_file);
            fputc(data32[1],ob_file);
            fprintf(ob_file,"\n");

            dc2++;
            byte_counter++;

            for(int j = 0; j < BYTE_LENGTH; j++) {
                bin_byte_str[j] = '0';
            }
            
        }
        
        fclose(ob_file); // Close the object file pointer
        fclose(ext_file); // Close the external file pointer
    }
    else { // There is minimum 1 extern label
        
        // Instructions and data counters
        int ic2 = DEFULT_COUNTER_VALUE; 
        int dc2 = DEFULT_COUNTER_VALUE;

        char code32[2];
        char data32[2];

        int byte_counter = START_CODE_INDEX;
        int bin_byte_counter;
        
        char bin_str[] = {0};
        char bin_byte_str[20] = "0000000000";
        int copying_counter;

        // char arrays for the code and data counter in base 32
        char code_counter[2];
        char data_counter[2];

        // flag for check if it is the first line
        bool first_line = true;

        // Finding the amount of memory bytes in the code and data arrays
        while(code_arr[ic2][0] != 'e')
            ic2++;
        while(data_arr[dc2][0] != 'e')
            dc2++;
        
        // Translate this amount number to base 32 and push to the .ob file in the first line
        int code_byte_amount = decimalToBinary(ic2);
        int data_byte_amount = decimalToBinary(dc2);

        char code_amount_base32[2];
        char data_amount_base32[2];

        char code_byte_amount_str[] = {0};
        char data_byte_amount_str[] = {0};
        char code_amount_buffer[20] = "0000000000";
        char data_amount_buffer[20] = "0000000000";

        my_itoa(code_byte_amount,code_byte_amount_str);
        int code_amount_counter = 10 - strlen(code_byte_amount_str);
        for(int d = 0; d < strlen(code_byte_amount_str); d++) {
            code_amount_buffer[code_amount_counter] = code_byte_amount_str[d];
            code_amount_counter++;
        }
        binaryTo32Base(code_amount_buffer,code_amount_base32);

        
        my_itoa(data_byte_amount,data_byte_amount_str);
        int data_amount_counter = 10 - strlen(data_byte_amount_str);
        for(int t = 0; t < strlen(data_byte_amount_str); t++) {
            data_amount_buffer[data_amount_counter] = data_byte_amount_str[t];
            data_amount_counter++;
        }
        binaryTo32Base(data_amount_buffer,data_amount_base32);

        code_amount_base32[2] = '\0';
        fputc(code_amount_base32[1],ob_file);
        fputc('\t',ob_file);

        if(data_amount_base32[0] == '!') {
            fputc(data_amount_base32[1],ob_file);
            fputc('\n',ob_file);
        }
        else {
            fputc(data_amount_base32[0],ob_file);
            fputc(data_amount_base32[1],ob_file);
            fputc('\n',ob_file);
        }

        // Reaset the counters
        ic2 = DEFULT_COUNTER_VALUE;
        dc2 = DEFULT_COUNTER_VALUE;
        

        // Going over the code till the end ('e' in the MSB)
        while(code_arr[ic2][0] != 'e')
        {
            bin_byte_counter = decimalToBinary(byte_counter);
            my_itoa(bin_byte_counter,bin_str);

            copying_counter = 10 - strlen(bin_str);
            for(int i = 0; i < strlen(bin_str); i++) {
                bin_byte_str[copying_counter] = bin_str[i];
                copying_counter++;
            }

            binaryTo32Base(bin_byte_str,code_counter);
            code_counter[2] = '\0';

            binaryTo32Base(code_arr[ic2],code32);
            code32[2] = '\0';
            
            fputc(code_counter[0],ob_file);
            fputc(code_counter[1],ob_file);
            
            //fprintf(ob_file,code_counter);
            
            fprintf(ob_file,"   ");

            fputc(code32[0],ob_file);
            fputc(code32[1],ob_file);
            
            fprintf(ob_file,"\n");

            ic2++;
            byte_counter++;
            
            for(int j = 0; j < 10; j++) {
                bin_byte_str[j] = '0';
            }
            
        }

        // Going over the data till the end ('e' in the MSB)
        while(data_arr[dc2][0] != 'e')
        {
            bin_byte_counter = decimalToBinary(byte_counter);
            my_itoa(bin_byte_counter,bin_str);

            copying_counter = BYTE_LENGTH - strlen(bin_str);
            for(int i = 0; i < strlen(bin_str); i++) {
                bin_byte_str[copying_counter] = bin_str[i];
                copying_counter++;
            }

            binaryTo32Base(bin_byte_str,data_counter);
            data_counter[2] = '\0';

            binaryTo32Base(data_arr[dc2],data32);
            data32[2] = '\0';
            
            /*
            if(first_line == true) {
                fprintf(ob_file,data_counter);
                data_counter[0] = data_counter[1];
                fprintf(ob_file,data_counter);

                first_line = false;
            }
            */
            
            fputc(data_counter[0],ob_file);
            fputc(data_counter[1],ob_file);
            
            fprintf(ob_file,"   ");

            fputc(data32[0],ob_file);
            fputc(data32[1],ob_file);
            fprintf(ob_file,"\n");

            dc2++;
            byte_counter++;

            for(int j = 0; j < BYTE_LENGTH; j++) {
                bin_byte_str[j] = '0';
            }
            
        }
        
        fclose(ob_file); // Close the object file pointer
    }
    
}

/**
 * @brief Returns the index of the first external label in the label table.
 *
 * This function searches for the first external label in the label table and returns its index.
 * It also updates the type of the found external label to -1, indicating that it has been processed.
 *
 * @return The index of the first external label, or -1 if no external labels are found.
 */
int firstExtLabel() {
    for(int i = 0; i < MAX_LABEL_AMOUNT; i++) {
        if(labelTable[i].type == EXTERNAL_LABEL_TYPE) {
            labelTable[i].type = -1;
            return i; // return the index of teh external label
        }
    }
    return -1;
}

/**
 * @brief Converts an integer to a string representation.
 *
 * This function converts the given integer to a string representation using the standard sprintf function.
 *
 * @param num The integer value to be converted.
 * @param str The character array to store the resulting string.
 * @return A pointer to the resulting string.
 */
char* my_itoa(int num, char *str)
{
    if(str == NULL)
    {
        return NULL;
    }
    sprintf(str, "%d", num);
    return str;
}
