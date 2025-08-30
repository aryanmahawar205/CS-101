%{
/*
DA-1 : Lex Program 4
---------------------------------------
Problem Statement:
Write a Lex program that validates whether
an input string is a valid hexadecimal number.
Hex numbers must start with 0x or 0X.
*/
#include <stdio.h>
%}

%%
0[xX][0-9a-fA-F]+    { printf("%s -> Valid Hexadecimal\n", yytext); }
[0-9a-zA-Z]+         { printf("%s -> Not Hexadecimal\n", yytext); }
[ \t\n]+             ;
.                    ;
%%

int yywrap() { return 1; }

int main() {
    printf("Enter strings (Ctrl+D to stop):\n");
    yylex();
    return 0;
}