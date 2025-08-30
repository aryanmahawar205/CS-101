%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(char *s) { printf("Error parsing number\n"); return 0; }
%}

%union { int num; }
%token <num> NUM

%%
start : NUM { if ($1 % 2 == 0) printf("%d is Even\n", $1);
              else printf("%d is Odd\n", $1); }
      ;
%%

int main() {
    printf("Enter a number:\n");
    return yyparse();
}