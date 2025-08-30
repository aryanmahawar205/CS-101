%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(char *s) { printf("Invalid boolean expression\n"); return 0; }
%}

%union { int num; }

%token <num> NUM
%left '|' 
%left '&'
%right '!'

%type <num> expr

%%
expr : expr '|' expr { $$ = $1 || $3; printf("= %d\n", $$); }
     | expr '&' expr { $$ = $1 && $3; printf("= %d\n", $$); }
     | '!' expr      { $$ = !$2; printf("= %d\n", $$); }
     | '(' expr ')'  { $$ = $2; }
     | NUM           { $$ = $1; }
     ;
%%

int main() {
    printf("Enter boolean expression (1/0 with & | !):\n");
    return yyparse();
}