%{
	#include <ctype.h>
	int yyerror(const char *msg);
	int yylex();
%}
%union{
	int		iVal;	
	char*	dopVal;
}
%token	<iVal> NUMBER
%type	<dopVal> DOPER
%%

EXP : EXP BOP EXP		{ }
	| EXP '[' EXP ']'	{ }
	| '(' EXP ')'		{ }
	| NUMBER PO_UOP		{ }
	| PR_UOP EXP		{ }
	| VAR_ID			{ }
	| NUMBER			{ }
	;
%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg){ fputs(msg, stderr); exit(-1);}
