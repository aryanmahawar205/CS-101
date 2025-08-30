%{
/*
DA-1 : Lex Program 1
---------------------------------------
Problem Statement:
Write a Lex program that reads words from
the input and checks if they are palindromes.
For each word, print whether it is a palindrome
or not.
*/
#include <stdio.h>
#include <string.h>

int isPalindrome(const char *s) {
    int n = strlen(s);
    for (int i = 0; i < n/2; i++) {
        if (s[i] != s[n-1-i]) return 0;
    }
    return 1;
}
%}

%%
[a-zA-Z]+   {
                if(isPalindrome(yytext))
                    printf("%s -> Palindrome\n", yytext);
                else
                    printf("%s -> Not Palindrome\n", yytext);
            }
[ \t\n]+    ;   
.           ;   
%%

int yywrap() { return 1; }

int main() {
    printf("Enter words (Ctrl+D to stop):\n");
    yylex();
    return 0;
}