/* [utilities.c]:
In this file: Super usefull and simple functions like function that check
if one string is substring of the other, remove blank spaces and so more...

author: Mikey Bar Yaacov Dunevich  
ID: 215356981 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "D:\Desktop\Assembler\assembler-c\src\utils\generalUtils\utilities.h"
#include "../dataUtils/dataUtils.h"

/**
 * decimalToBinary(): Converts a decimal number to binary.
 *
 * @param num The decimal number to convert.
 * @return The binary representation of the decimal number.
 */
int decimalToBinary(int num) {
    int bin = 0, rem = 0, place = 1;
    while(num) {
        rem = num % 2;
        num = num / 2;
        bin += rem * place;
        place = place * 10;
    }
    
    return bin;
}


/**
 * getCommandNumber(): Gets a command name and returns the corresponding command number.
 *
 * @param command The command name.
 * @return The command number. Returns 16 if the command is not in the commands list.
 */
int getCommandNumber(char command[]) {
    int number = 16;
    if(strcmp(command,"mov") == 0) {number = 0;}
    if(strcmp(command,"cmp") == 0) {number = 1;}
    if(strcmp(command,"add") == 0) {number = 2;}
    if(strcmp(command,"sub") == 0) {number = 3;}
    if(strcmp(command,"not") == 0) {number = 4;}
    if(strcmp(command,"clr") == 0) {number = 5;}
    if(strcmp(command,"lea") == 0) {number = 6;}
    if(strcmp(command,"inc") == 0) {number = 7;}
    if(strcmp(command,"dec") == 0) {number = 8;}
    if(strcmp(command,"jmp") == 0) {number = 9;}
    if(strcmp(command,"bne") == 0) {number = 10;}
    if(strcmp(command,"red") == 0) {number = 11;}
    if(strcmp(command,"prn") == 0) {number = 12;}
    if(strcmp(command,"jsr") == 0) {number = 13;}
    if(strcmp(command,"rts") == 0) {number = 14;}
    if(strcmp(command,"stop") == 0) {number = 15;}

    return number;
}

/**
 * is_substring(): Checks if the first string is a substring of the second string.
 *
 * @param check The substring to check.
 * @param string The string to check against.
 * @return True if the first string is a substring of the second string, false otherwise.
 */
bool is_substring(char *check, char *string) {
  int slen = strlen(string);
  int clen = strlen(check);
  int end = slen - clen + 1;
  
  for (int i = 0; i < end; i++) {
    bool check_found = true;
    
    for (int j = 0; j < clen; j++) {
      if (check[j] != string[i + j]) {
        check_found = false;
        break;
      }
    }
    if (check_found) return true;
  }
      
  return false;
}

/**
 * removeSpaceFront(): Removes leading blank spaces from a string.
 *
 * @param s The string to remove leading blank spaces from.
 */
void removeSpaceFront(char *s)
{
  int count = 0;
  while (s[count] == ' ' || s[count] == '\n' || s[count] == '\t') count++;

  if (count != 0)
  {
    int i = 0;
    while (s[i + count] != '\0')
    {
      s[i] = s[i + count];
      i++;
    }
    s[i] = '\0';
  }
}

/**
 * removeSpaceTail(): Removes trailing blank spaces from a string.
 *
 * @param s The string to remove trailing blank spaces from.
 */
void removeSpaceTail(char *s)
{
  int i = strlen(s) - 1;
  while (i >= 0)
  {
    if (s[i] == ' ' || s[i] == '\n' ||
        s[i] == '\t') i--;
    else break;
  }
  s[i + 1] = '\0';
}

// Helpfull global vars
char command[4];
char arg[50];
char arg2[50];
char arg3[50];

/**
 * getCommand(): Extracts the command name from a string.
 *
 * @param s1 The string containing the command.
 * @return The extracted command name.
 */
char* getCommand(char *s1) {
  removeSpaceFront(s1);
  command[0] = s1[0];
  command[1] = s1[1];
  command[2] = s1[2];
  if(command[0] == 's' && command[1] == 't' && command[2] == 'o') {
      command[3] = s1[3];
      command[4] = '\0';
  }
  else {
      command[3] = '\0';
  }
  return command;
}

/**
 * getFirstArg(): Extracts the first argument from a string.
 *
 * @param s1 The string containing the arguments.
 * @return The first argument.
 */
char* getFirstArg(char *s1) {
  removeSpaceFront(s1);
  for(int i = 0; i < strlen(s1); i++) {
    arg[i] = s1[i];
  }
  arg[0] = ' ';
  arg[1] = ' ';
  arg[2] = ' ';
  removeSpaceFront(arg);
  removeSpaceTail(arg);

  if(is_substring(",",arg) == false) {
    return arg;
  }

  else {
      int count = 0;
      while(arg[count] != ',') {
          count++;
          if(arg[count] == ',') {
              arg[count] = '\0';
              break;
          }
      }
      return arg;
  }
}

/**
 * getOnlyArg(): Extracts the argument when there is only one argument.
 *
 * @param s1 The string containing the argument.
 * @return The extracted argument.
 */
char* getOnlyArg(char *s1) {
  for(int i = 0; i < strlen(s1); i++) {
    arg3[i] = s1[i];
  }
  removeSpaceFront(s1);
  for(int i = 0; i < strlen(s1); i++) {
    arg3[i] = s1[i];
  }
  arg3[strlen(s1)] = '\0';
  arg3[0] = ' ';
  arg3[1] = ' ';
  arg3[2] = ' ';
  removeSpaceFront(arg3);
  removeSpaceTail(arg3);

  return arg3;
}

/**
 * getSecondArg(): Extracts the second argument from a string.
 *
 * @param s1 The string containing the arguments.
 * @return The second argument.
 */
char* getSecondArg(char *s1) {
  int count = 0;
  while(s1[count] != ',') {
    count++;
  }
  count++;
  int argPointer = 0;
  for(int i = count; i < strlen(s1); i++) {
    arg2[argPointer] = s1[i];
    argPointer++;
  }
  removeSpaceFront(arg2);
  removeSpaceTail(arg2);
  return arg2;
}

/**
 * removeTillSpace(): Removes characters until the first blank space from a string.
 *
 * @param s1 The string to remove characters from.
 * @return The modified string.
 */
char* removeTillSpace(char *s1) {
    int count = 0;
    while(s1[count] != ' ') {
      s1[count] = ' ';
      count++;
    }
    removeSpaceFront(s1); // Remove all the blank spaces in front
    return s1; // return the pointer to the string
}

/**
 * amountInString(): Counts the number of occurrences of a character in a string.
 *
 * @param s1 The string to search.
 * @param ch The character to count.
 * @return The number of occurrences of the character in the string.
 */
int amountInString(char *s1, char ch) {
  int count = 0;
  for(int i = 0; i < strlen(s1); i++) {
    if(s1[i] == ch) {
      count++;
    }
  }
  return count;

}

char register_str[4];

/**
 * getRegisterBainry(): Converts a register name to its binary representation.
 *
 * @param s The register name.
 * @return A 4-character array representing the binary code of the register.
 */
char* getRegisterBainry(char *s) {

    register_str[0] = '0';
    register_str[1] = '0';
    register_str[2] = '0';
    register_str[3] = '0';

    if(strcmp("r0",s) == 0) {}
    if(strcmp("r1",s) == 0) {
        register_str[3] = '1';
    }
    if(strcmp("r2",s) == 0) {
        register_str[2] = '1';
    }
    if(strcmp("r3",s) == 0) {
        register_str[2] = '1';
        register_str[3] = '1';
    }
    if(strcmp("r4",s) == 0) {
        register_str[1] = '1';
    }
    if(strcmp("r5",s) == 0) {
        register_str[1] = '1';
        register_str[3] = '1';
    }
    if(strcmp("r6",s) == 0) {
        register_str[1] = '1';
        register_str[2] = '1';
    }
    if(strcmp("r7",s) == 0) {
        register_str[1] = '1';
        register_str[2] = '1';
        register_str[3] = '1';

    }

    return register_str;

}

/**
 * asciiToBinNumber(): Converts an ASCII character to its binary representation.
 *
 * @param ch The ASCII character.
 * @return The binary representation of the ASCII character.
 */
int asciiToBinNumber(char ch) {
    int ascii_num;
    if(ch == 'a') {ascii_num = 97;} if(ch == 'b') {ascii_num = 98;} if(ch == 'c') {ascii_num = 99;} if(ch == 'd') {ascii_num = 100;}
    if(ch == 'e') {ascii_num = 101;} if(ch == 'f') {ascii_num = 102;} if(ch == 'g') {ascii_num = 103;} if(ch == 'h') {ascii_num = 104;}
    if(ch == 'i') {ascii_num = 105;} if(ch == 'j') {ascii_num = 106;} if(ch == 'k') {ascii_num = 107;} if(ch == 'l') {ascii_num = 108;}
    if(ch == 'm') {ascii_num = 109;} if(ch == 'n') {ascii_num = 110;} if(ch == 'o') {ascii_num = 111;} if(ch == 'p') {ascii_num = 112;}
    if(ch == 'q') {ascii_num = 113;} if(ch == 'r') {ascii_num = 114;} if(ch == 's') {ascii_num = 115;} if(ch == 't') {ascii_num = 116;}
    if(ch == 'u') {ascii_num = 117;} if(ch == 'v') {ascii_num = 118;} if(ch == 'w') {ascii_num = 119;} if(ch == 'x') {ascii_num = 120;}
    if(ch == 'y') {ascii_num = 121;} if(ch == 'z') {ascii_num = 122;} 

    if(ch == 'A') {ascii_num = 65;} if(ch == 'B') {ascii_num = 66;} if(ch == 'C') {ascii_num = 67;}
    if(ch == 'D') {ascii_num = 68;} if(ch == 'E') {ascii_num = 69;} if(ch == 'F') {ascii_num = 70;} if(ch == 'G') {ascii_num = 71;}
    if(ch == 'H') {ascii_num = 72;} if(ch == 'I') {ascii_num = 73;} if(ch == 'J') {ascii_num = 74;} if(ch == 'K') {ascii_num = 75;}
    if(ch == 'L') {ascii_num = 76;} if(ch == 'M') {ascii_num = 77;} if(ch == 'N') {ascii_num = 78;} if(ch == 'O') {ascii_num = 79;}
    if(ch == 'P') {ascii_num = 80;} if(ch == 'Q') {ascii_num = 81;} if(ch == 'R') {ascii_num = 82;} if(ch == 'S') {ascii_num = 83;}
    if(ch == 'T') {ascii_num = 84;} if(ch == 'U') {ascii_num = 85;} if(ch == 'V') {ascii_num = 86;} if(ch == 'W') {ascii_num = 87;}
    if(ch == 'X') {ascii_num = 88;} if(ch == 'Y') {ascii_num = 89;} if(ch == 'Z') {ascii_num = 90;}
    if(ch == '"') {ascii_num = 34; return 34;}
    
    return decimalToBinary(ascii_num);
    
}