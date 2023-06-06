/* [mmn 14 : symbolTable.h]:
In this file: The symbol table for all the labels, and also some functions to handle with the symbolTable,
    like check if a label in the symbol table, check if a string is a label and more.

author: Mikey Bar Yaacov Dunevich  
ID: 215356981 */


#define MAX_LABEL_AMOUNT 100
#define MAX_LABEL_NAME_LENGTH 100

int labelType(char *s1);
char* isLabel(char *s1); 
bool isInLabelTabel(char *s1);
int indexInLabelTable(char *s);

// The struct label has a value, a type (data, code...) and a name.
struct label 
{
    int value; // the label value
    int type; // data - 0, code - 1, extern - 2, entry - 3.
    char name[100]; // The name of the label
};

// Global array of labels with store all the labels.
struct label labelTable[100];
