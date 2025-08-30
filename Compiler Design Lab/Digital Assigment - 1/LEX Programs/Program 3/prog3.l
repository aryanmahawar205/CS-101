%{
/*
DA-1 : Lex Program 3
---------------------------------------
Problem Statement:
Write a Lex program that scans arithmetic
expressions and counts:
1. Number of operands (identifiers, numbers)
2. Number of operators (+, -, *, /, =)
*/
#include <stdio.h>
int operators = 0, operands = 0;
%}

%%
[0-9]+                  { operands++; }
[a-zA-Z_][a-zA-Z0-9_]*  { operands++; }
[+\-*/=]                { operators++; }
[ \t\n]+                ;
.                       ;
%%

int yywrap() { return 1; }

int main() {
    printf("Enter arithmetic expression (Ctrl+D to stop):\n");
    yylex();
    printf("Total Operators = %d\n", operators);
    printf("Total Operands  = %d\n", operands);
    return 0;
}