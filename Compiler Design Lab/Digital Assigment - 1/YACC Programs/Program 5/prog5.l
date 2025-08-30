%{
#include "y.tab.h"
#include <stdlib.h>
%}

digit [0-9]

%%
"-"?{digit}+    { yylval.num = atoi(yytext); return NUM; }
[ \t\n]+        ;
.               { return yytext[0]; }
%%

int yywrap() { return 1; }