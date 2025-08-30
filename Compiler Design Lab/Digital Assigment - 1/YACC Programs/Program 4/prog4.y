%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int yylex();
int yyerror(char *s) { printf("Invalid word\n"); return 0; }
%}

%union { char* str; }
%token <str> ID

%%
start : ID { printf("Length of '%s' = %ld\n", $1, strlen($1)); }
      ;
%%

int main() {
    printf("Enter a word:\n");
    return yyparse();
}