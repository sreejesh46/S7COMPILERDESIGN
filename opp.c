/*ALOGITHM
Algorithm: Operator Precedence Parsing

1. Initialize variables and arrays:
   - char *input;
   - int i = 0, top = 0, l;
   - char stack[50], lasthandle[6];
   - char handles[][5] = {")E(", "E*E", "E+E", "i", "E^E"};
   - char prec[9][9] = { /* Operator precedence table */ };
/*
2. Allocate memory for input: input = (char *)malloc(50 * sizeof(char)).
3. Read the input string from the user and append '$' at the end.
   - Read the input string.
   - Concatenate '$' at the end of the input string.
   - Set l as the length of the input string.
4. Initialize the stack with '$' and display the initial configuration:
   - strcpy(stack, "$").
   - Display the initial configuration: "\nSTACK\tINPUT\tACTION".
5. Loop until i is less than or equal to l:
   a. Shift a character onto the stack:
      - Execute shift().
      - Display the current configuration: "\n%s\t%s\tShift", stack, input + i.
   b. Check for reductions based on the operator precedence table:
      - If prec[getindex(stack[top])][getindex(input[i])] == '>', then
        - Loop until reduce() returns true:
          - Execute reduce().
          - Display the reduction: "\n%s\t%s\tReduced: E->%s", stack, input + i, lasthandle.
6. Display the final result based on the stack contents:
   - Display the final configuration: "\n%s\n", strcmp(stack, "$E$") == 0 ? "Accepted;" : "Not Accepted;".
7. Deallocate memory (free(input)).
8. End of Algorithm.
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *input;
int i = 0, top = 0, l;
char stack[50], lasthandle[6];
char handles[][5] = {")E(", "E*E", "E+E", "i", "E^E"};
char prec[9][9] = {
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'>', '>', '<', '<', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '<', '<', '<', '>', '>'},
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    {'<', '<', '<', '<', '<', '<', '<', '>', 'e'},
    {'>', '>', '>', '>', '>', 'e', 'e', '>', '>'},
    {'<', '<', '<', '<', '<', '<', '<', '<', '>'},
};

int getindex(char c) {
    switch (c) {
        case '+': return 0;
        case '-': return 1;
        case '*': return 2;
        case '/': return 3;
        case '^': return 4;
        case 'i': return 5;
        case '(': return 6;
        case ')': return 7;
        case '$': return 8;
    }
}

int shift() {
    stack[++top] = input[i++];
    stack[top + 1] = '\0';
}

int reduce() {
    for (int k = 0; k < 5; k++) {
        int len = strlen(handles[k]);
        if (stack[top] == handles[k][0] && top + 1 >= len) {
            int found = 1, t;
            for (t = 0; t < len && stack[top - t] == handles[k][t]; t++);
            if (t == len) {
                stack[top - t + 1] = 'E';
                top = top - t + 1;
                strcpy(lasthandle, handles[k]);
                stack[top + 1] = '\0';
                return 1;
            }
        }
    }
    return 0;
}

void dispstack() {
    for (int j = 0; j <= top; j++)
        printf("%c", stack[j]);
}

void dispinput() {
    for (int j = i; j < l; j++)
        printf("%c", input[j]);
}

int main() {
    input = (char *)malloc(50 * sizeof(char));
    printf("\nEnter the string\n");
    scanf("%s", input);
    input = strcat(input, "$");
    l = strlen(input);
    strcpy(stack, "$");
    printf("\nSTACK\tINPUT\tACTION");

    while (i <= l) {
        shift();
        printf("\n%s\t%s\tShift", stack, input + i);
        if (prec[getindex(stack[top])][getindex(input[i])] == '>') {
            while (reduce()) {
                printf("\n%s\t%s\tReduced: E->%s", stack, input + i, lasthandle);
            }
        }
    }

    printf("\n%s\n", strcmp(stack, "$E$") == 0 ? "Accepted;" : "Not Accepted;");

    return 0;
}
/*
output 

Enter the string
i+i*i

STACK	INPUT	ACTION
$i	+i*i$	Shift
$E	+i*i$	Reduced: E->i
$E+	i*i$	Shift
$E+i	*i$	Shift
$E+E	*i$	Reduced: E->i
$E	*i$	Reduced: E->E+E
$E*	i$	Shift
$E*i	$	Shift
$E*E	$	Reduced: E->i
$E	$	Reduced: E->E*E
$E$		Shift
$E$		Shift
Accepted;

