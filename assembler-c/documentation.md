*Assembly Languge Documentation*

------ `ADDRESSING TYPES` ------
1. Numbers with '#'
2. Data declerations (data, string and struct)
3. Working with labels (LABEL.1...)
4. Registers (r0, r1,...r7)

------------------------ `COMMANDS TABLE` ------------------------
command name | command opcode  | short  explanation
mov          |       0         | copy the first arg and past to the second arg
cmp          |       1         | compare between 2 arguments
add          |       2         | add 2 arguments and save in the first one
sub          |       3         | sub 2 arguments and save in the first one
not          |       4         | switch binary 0 to 1, and 1 to 0
clr          |       5         | clear the argument
lea          |       6         | same as move but works with data
inc          |       7         | argument = argument + 1
dec          |       8         | argument = argument - 1
jmp          |       9         | go to a place in the code (a label)
bne          |       10        | after cmp - if the values are not equals, jmp to...
get          |       11        | call for a char from stdin
prn          |       12        | print a char from stdout
jsr          |       13        | call for a function
rts          |       14        | end of a function
hlt          |       15        | stop the program

------ `LABEL TYPES` ------
1. Code labels ==> LABEL: mov r1, r2
2. Data labels (for numbers) ==> LABEL: .data 1,4,-6 (Supports negativ numbers)
3. String labels ==> LABEL: .string "ABCgg"
4. Struct labels ==> LABEL: .struct "AB", -4, "Cc"

------ `EXTERNAL LABELS` ------
There is a option to import a label from other .am file.
To do so ==> write in the head of the file: .extern 'label_name'

------ `ENTRY LABELS` ------
There is also an option of export a label from the current .am
file to other file. 
To do so ==> write in the head of the file: .entry 'label_name'


------ `MACROES` ------
macros are a code block that in the begging of the .am file,
and with a given name. The assembler replace the code of the macro in the right place

*example:*

macro m1
    mov r2 ,r3
    cmp r2, #3
endmacro
.
.
.
m1

-The assembler will replace the macro code in the place of 'm1'-


------ `CODE EXAMPLE 1` ------
The code put the number 3 in r1, 7 in r0, add them both 
and compare the sum to 4. Then if the sum isn't 4, jmp to the begging of the code.

****
STRAT: mov r1, #3
       mov r0, #7

       add r1, r0
       cmp r1, #4
       bne LABEL

LABEL: jmp START
****


------ `CODE EXAMPLE 2` ------
The code add 1 to the first argument of DATA1, sub 4 from the second argument of DATA2.
Then, Put in registers and compare the result, if not equals inc first arg of DATA 1 and jmp again.

****
; Exporting the labels 'LOOP' and 'ADD1'
.entry LOOP
.entry ADD1

DATA1: .data 4,-5,7
DATA2: .data 9,3,1
STRUCT .struct "Gc", 8, -3

add DATA1.1, 1
sub DATA2.2, 4

mov r0, DATA1.1
mov r1, DATA2.2

LOOP: cmp r0, r1
      bne ADD1

ADD1: inc r0
      inc r1
      jmp LOOP

END:  hlt
****





