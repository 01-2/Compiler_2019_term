%{
	#include <string.h>
	#include "y.tab.h"

	int line = 1;
%} 
digit	[0-9] 
letter	[a-zA-Z]
space	[ \t]
%%

("int")(" ")({letter}|"_")({letter}|{digit}|"_")* { yylval = strdup(yytext); return _VAR; }
("int")(" ")({letter}|"_")({letter}|{digit}|"_")*("[") { yylval = strdup(yytext); return _ARR; }
("int"|"void")(" ")({letter}|"_")({letter}|{digit}|"_")*("(") { yylval = strdup(yytext); return _START_METHOD_DECL; }

{digit}+	{ yylval.ival = atoi(yytext); return NUMBER; }
{id}"["		{ yylval = strdup(yytext); return _ARRAY_VALUE; }
{space}+	{ }

"void"		{ yylval = strdup(yytext); return _VOID; }
"int"		{ yylval = strdup(yytext); return _TYPE; }

"if"		{ yylval = strdup(yytext); return _IF; }
"else"		{ yylval = strdup(yytext); return _ELSE; }
"while"		{ yylval = strdup(yytext); return _WHILE; }

"printf"	{ yylval = strdup(yytext); return _PRINTF; }
"scanf"		{ yylval = strdup(yytext); return _SCANF; }

"("         { yylval = strdup(yytext); return _LPAREN; }
")"         { yylval = strdup(yytext); return _RPAREN; }
"["			{ yylval = strdup(yytext); return _LSQUARE_BRACKET; }
"]"			{ yylval = strdup(yytext); return _RSQUARE_BRACKET; }

"!"			{ yylval = strdup(yytext); return _NOT; }
"~"         { yylval = strdup(yytext); return _NOTB; }
"++"        { yylval = strdup(yytext); return _PLUS_PLUS; }
"--"        { yylval = strdup(yytext); return _MINUS_MINUS; }

"+"         { yylval = strdup(yytext); return _PLUS; }
"-"         { yylval = strdup(yytext); return _MINUS; }
"*"         { yylval = strdup(yytext); return _TIMES; }
"<"         { yylval = strdup(yytext); return _RELOP; }
">"         { yylval = strdup(yytext); return _RELOP; }
"&&"        { yylval = strdup(yytext); return _AND; }
"||"        { yylval = strdup(yytext); return _OR; }

";"         { yylval = strdup(yytext); return _SEMICOLON; }
\n			{ line++; }
%%
int yywrap() { 
	return 1; 
}
