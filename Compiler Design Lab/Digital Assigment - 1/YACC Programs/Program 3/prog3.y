/*
DA-1 : Yacc Program 3
---------------------------------------
Problem Statement:
Write a Yacc program that acts as a simple
calculator supporting assignment and usage
of integer variables.
Example:
a = 5
b = a + 3
*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int yylex(void);
int yyerror(char *s) { printf("Error: %s\n", s); return 0; }

int vars[26];   // store values for variables a-z
%}

%token NUM ID

%%
stmt_list : stmt_list stmt
          | stmt
          ;

stmt : ID '=' expr { vars[$1] = $3; printf("%c = %d\n", 'a'+$1, $3); }
     | expr        { printf("= %d\n", $1); }
     ;

expr : expr '+' expr { $$ = $1 + $3; }
     | expr '-' expr { $$ = $1 - $3; }
     | expr '*' expr { $$ = $1 * $3; }
     | expr '/' expr { $$ = $1 / $3; }
     | NUM           { $$ = $1; }
     | ID            { $$ = vars[$1]; }
     ;
%%

int main() {
    printf("Enter expressions (Ctrl+D to stop):\n");
    yyparse();
    return 0;
}