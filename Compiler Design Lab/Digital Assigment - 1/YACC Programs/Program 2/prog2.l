%{
#include "y.tab.h"
%}

%%
[_a-zA-Z][_a-zA-Z0-9]*   { return ID; }
.|\n                    { return yytext[0]; }
%%

int yywrap() { return 1; }