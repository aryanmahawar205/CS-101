%{
#include "y.tab.h"
#include <string.h>
#include <stdlib.h>
%}

%%
[a-zA-Z]+   { yylval.str = strdup(yytext); return ID; }
[ \t\n]+    ;
.           { return yytext[0]; }
%%

int yywrap() { return 1; }