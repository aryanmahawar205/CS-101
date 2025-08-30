%{
#include "y.tab.h"
%}

%%
"if"        { return IF; }
"else"      { return ELSE; }
"(".*")"    { return COND; }
[a-zA-Z0-9]+ { return STMT; }
[ \t\n]+    ;
.           ;
%%

int yywrap() { return 1; }