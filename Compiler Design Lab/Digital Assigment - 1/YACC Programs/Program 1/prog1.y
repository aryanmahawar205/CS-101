/*
DA-1 : Yacc Program 1
---------------------------------------
Problem Statement:
Write a Yacc program that evaluates
arithmetic expressions containing
+ , - , * , / and parentheses.
This version fixes ambiguity by
defining operator precedence and associativity.
*/
%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(char *s) { printf("Error: %s\n", s); return 0; }
%}

/* Token */
%token NUM

/* Define precedence (lowest first) */
%left '+' '-'
%left '*' '/'
%right UMINUS   /* unary minus */

%%
expr : expr '+' expr   { $$ = $1 + $3; }
     | expr '-' expr   { $$ = $1 - $3; }
     | expr '*' expr   { $$ = $1 * $3; }
     | expr '/' expr   { $$ = $1 / $3; }
     | '-' expr %prec UMINUS { $$ = -$2; }
     | '(' expr ')'    { $$ = $2; }
     | NUM             { $$ = $1; }
     ;
%%

int main() {
    printf("Enter arithmetic expression:\n");
    return yyparse();
}