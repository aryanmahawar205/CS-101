%{
/*
DA-1 : Lex Program 5
---------------------------------------
Problem Statement:
Write a Lex program that classifies tokens
into integers, floats, and identifiers.
*/
#include <stdio.h>
%}

%%
[0-9]+\.[0-9]+         { printf("%s -> Float\n", yytext); }
[0-9]+                 { printf("%s -> Integer\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("%s -> Identifier\n", yytext); }
[ \t\n]+               ;
.                      ;
%%

int yywrap() { return 1; }

int main() {
    printf("Enter tokens (Ctrl+D to stop):\n");
    yylex();
    return 0;
}