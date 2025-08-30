/*
DA-1 : Yacc Program 4
---------------------------------------
Problem Statement:
Write a Yacc program that checks whether
a given statement is a valid 'if-else' structure.
*/
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(char *s) { printf("Invalid statement\n"); return 0; }
%}

%token IF ELSE COND STMT

%%
S : IF COND STMT
  | IF COND STMT ELSE STMT { printf("Valid if-else statement\n"); }
  ;
%%

int main() {
    printf("Enter if statement:\n");
    yyparse();
    return 0;
}