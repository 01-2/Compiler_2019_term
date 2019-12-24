%{
	#include "y.tab.h"
%} 
digit	[0-9] 
alpha	[a-zA-Z]
space	[ \t]
id		^[a-zA-Z_][a-zA-Z0-9_]*$
%%

"["			{ yylval = strdup(yytext); return _LSQUARE_BRACKET; }
"]"			{ yylval = strdup(yytext); return _RSQUARE_BRACKET; }
"("         { yylval = strdup(yytext); return _LPAREN; }
")"         { yylval = strdup(yytext); retrun _RPAREN; }

{id}		{ yylval.id = *yytext; return VAR_ID; }
{digit}+	{ yylval.ival = atoi(yytext); return NUMBER; }	

{space}+	{ }
\n			{ return 0; }
%%
int yywrap() { return 1; }
