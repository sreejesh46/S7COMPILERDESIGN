#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX_INPUT_LENGTH 30

char input[MAX_INPUT_LENGTH];
int i = 0, error = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

int main() {
    printf("******PROVIDED GRAMMER******");
    printf("\nE->TE | E->TE/e | T->FT/e | F->(E)/id \n");
    printf("\nEnter the function to check: ");
    
    // Use fgets to safely read input and avoid buffer overflow
    fgets(input, sizeof(input), stdin);
    
    // Remove the newline character at the end of the input string
    input[strcspn(input, "\n")] = '\0';

    E();

    if (strlen(input) == i && error == 0)
        printf("\nAccepted \n");
    else
        printf("Not Accepted! \n");

    return 0;
}

void E() {
    T();
    Eprime();
}

void T() {
    F();
    Tprime();
}

void Eprime() {
    if (input[i] == '+') {
        i++;
        T();
        Eprime();
    }
}

void Tprime() {
    if (input[i] == '*') {
        i++;
        F();
        Tprime();
    }
}

void F() {
    if (input[i] == '(') {
        i++;
        E();
        if (input[i] == ')') {
            i++;
        } else
            error = 1;
    } else if (input[i] == 'i' && input[i + 1] == 'd')
        i += 2;
    else
        error = 1;
}

