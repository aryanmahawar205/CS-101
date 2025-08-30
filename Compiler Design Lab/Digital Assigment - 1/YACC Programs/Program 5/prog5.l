%{
#include "y.tab.h"
%}

%%
"("     { return '('; }
")"     { return ')'; }
[ \t\n]+ ;
.        ;
%%

int yywrap() { return 1; }