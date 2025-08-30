/*
DA-1 : Yacc Program 5
---------------------------------------
Problem Statement:
Write a Yacc program that validates whether
the parentheses in an expression are balanced.
*/
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(char *s) { printf("Unbalanced\n"); return 0; }
%}

%%
S : '(' S ')' S
  | /* empty */
  ;
%%

int main() {
    printf("Enter parentheses string:\n");
    if(yyparse()==0) printf("Balanced\n");
    return 0;
}