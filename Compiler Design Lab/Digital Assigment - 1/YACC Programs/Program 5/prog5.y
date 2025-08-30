%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror(char *s) { printf("Error parsing number\n"); return 0; }
%}

%union { int num; }
%token <num> NUM

%%
start : NUM { if ($1 > 0) printf("%d is Positive\n", $1);
              else if ($1 < 0) printf("%d is Negative\n", $1);
              else printf("Zero\n"); }
      ;
%%

int main() {
    printf("Enter a number:\n");
    return yyparse();
}