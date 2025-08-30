%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%
"0"         { yylval.num = 0; return NUM; }
"1"         { yylval.num = 1; return NUM; }
[&|!()]     { return yytext[0]; }
[ \t\n]+    ;
.           { return yytext[0]; }
%%

int yywrap() { return 1; }