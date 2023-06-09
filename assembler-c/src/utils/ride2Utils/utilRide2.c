/* [utilRide2.c]:
In this file: helpfull functions for secondRide.c that help
to convert binary number to 32 base numbers.

author: Mikey Bar Yaacov Dunevich  
ID: 215356981 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "D:\Desktop\Assembler\assembler-c\src\utils\generalUtils\utilities.h"
#include "D:\Desktop\Assembler\assembler-c\src\utils\ride2Utils\utilRide2.h"
#include "D:\Desktop\Assembler\assembler-c\src\utils\dataUtils\dataUtils.h"

/**
 * binaryTo32Base(): Converts a binary number to 32 base numbers.
 *
 * @param bin_num The binary number as a string.
 * @param new_word The buffer to store the 32 base characters.
 */
void binaryTo32Base(char *bin_num, char new_word[]) 
{
    char low_word[] = "00000";
    char high_word[] = "00000";

    low_word[0] = bin_num[0]; low_word[1] = bin_num[1]; low_word[2] = bin_num[2];
    low_word[3] = bin_num[3]; low_word[4] = bin_num[4];

    high_word[0] = bin_num[5]; high_word[1] = bin_num[6]; high_word[2] = bin_num[7];
    high_word[3] = bin_num[8]; high_word[4] = bin_num[9];

    int decimal_low = binaryToDecimal(low_word);
    int decimal_high = binaryToDecimal(high_word);

    char base32_low = decimalTo32Chars(decimal_low);
    char base32_high = decimalTo32Chars(decimal_high);

    new_word[0] = base32_low;
    new_word[1] = base32_high;

}

/**
 * binaryToDecimal(): Converts a binary number to decimal.
 *
 * @param string The binary number as a string.
 * @return The decimal representation of the binary number.
 */
int binaryToDecimal(char *string) {
    int slen = strlen(string);
    int total = 0;
    int decval = 1;

    for(int i = (slen-1); i >= 0; i--) {
        if(string[i] == '1')
            total += decval;
        decval *= 2;
    }
    return total;
}

/**
 * decimalTo32Chars(): Converts a decimal number to a base 32 character.
 *
 * @param dec_num The decimal number.
 * @return The base 32 character representation of the decimal number.
 */
char decimalTo32Chars(int dec_num) {

    if(dec_num == 0) {return '!';} if(dec_num == 1) {return '@';} if(dec_num == 2) {return '#';} if(dec_num == 3) {return '$';}
    if(dec_num == 4) {return '%';} if(dec_num == 5) {return '^';} if(dec_num == 6) {return '&';} if(dec_num == 7) {return '*';}
    if(dec_num == 8) {return '<';} if(dec_num == 9) {return '>';} if(dec_num == 10) {return 'a';} if(dec_num == 11) {return 'b';}
    if(dec_num == 12) {return 'c';} if(dec_num == 13) {return 'd';} if(dec_num == 14) {return 'e';} if(dec_num == 15) {return 'f';}

    if(dec_num == 16) {return 'g';} if(dec_num == 17) {return 'h';} if(dec_num == 18) {return 'i';} if(dec_num == 19) {return 'j';}
    if(dec_num == 20) {return 'k';} if(dec_num == 21) {return 'l';} if(dec_num == 22) {return 'm';} if(dec_num == 23) {return 'n';}
    if(dec_num == 24) {return 'o';} if(dec_num == 25) {return 'p';} if(dec_num == 26) {return 'q';} if(dec_num == 27) {return 'r';}
    if(dec_num == 28) {return 's';} if(dec_num == 29) {return 't';} if(dec_num == 30) {return 'u';} if(dec_num == 31) {return 'v';}

}

