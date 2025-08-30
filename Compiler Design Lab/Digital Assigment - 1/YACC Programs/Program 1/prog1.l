%{
#include "y.tab.h"
%}

digit   [0-9]

%%
{digit}+    { yylval = atoi(yytext); return NUM; }
[ \t\n]+    ;   // ignore whitespace
.           { return yytext[0]; }  // operators and parentheses
%%

int yywrap() { return 1; }