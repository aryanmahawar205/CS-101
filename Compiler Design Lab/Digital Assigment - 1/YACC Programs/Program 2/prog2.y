/*
DA-1 : Yacc Program 2
---------------------------------------
Problem Statement:
Write a Yacc program that validates
whether an input string is a valid C identifier.
Rules:
- Must start with letter/underscore
- Can contain letters, digits, underscore
- Cannot be keyword
*/
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(char *s) { printf("Invalid Identifier\n"); return 0; }
%}

%token ID

%%
start : ID { printf("Valid Identifier\n"); }
      ;
%%

int main() {
    printf("Enter an identifier:\n");
    yyparse();
    return 0;
}