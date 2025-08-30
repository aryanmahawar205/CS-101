%{
/*
DA-1 : Lex Program 2
---------------------------------------
Problem Statement:
Write a Lex program that checks if binary
numbers from input are divisible by 3.
*/
#include <stdio.h>
#include <string.h>

int isDivBy3(const char *s) {
    int num = 0;
    for (int i = 0; s[i]; i++) {
        num = (num * 2 + (s[i]-'0')) % 3;
    }
    return num == 0;
}
%}

%%
[01]+       {
                if (isDivBy3(yytext))
                    printf("%s -> Divisible by 3\n", yytext);
                else
                    printf("%s -> Not Divisible by 3\n", yytext);
            }
[ \t\n]+    ;
.           ;
%%

int yywrap() { return 1; }

int main() {
    printf("Enter binary numbers (Ctrl+D to stop):\n");
    yylex();
    return 0;
}