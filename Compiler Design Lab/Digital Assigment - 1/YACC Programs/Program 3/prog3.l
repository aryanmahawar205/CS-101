%{
#include "y.tab.h"
#include <ctype.h>
%}

%%
[0-9]+              { yylval = atoi(yytext); return NUM; }
[a-z]               { yylval = yytext[0]-'a'; return ID; }
[=+\-*/\n]          { return yytext[0]; }
[ \t]+              ;
.                   ;
%%

int yywrap() { return 1; }