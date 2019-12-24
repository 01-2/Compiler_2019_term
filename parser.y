%{
	#include <ctype.h>
	#include <stdio.h>
	
	#define YYSTYPE char*

	int yyerror(const char *msg);
	int yylex();
	int yyparse();
%}
%token _VAR
%token _ARR
%token _START_METHOD_DECL
%token _NUM
%token _ARRAY_VALUE
%token _VOID
%token _TYPE
%token _IF
%token _ELSE
%token _WHILE
%token _PRINTF
%token _SCANF
%token _LPAREN
%token _RPAREN
%token _LBRACKET
%token _RBRACKET
%token _LSQUARE_BRACKET
%token _RSQUARE_BRACKET
%token _NOT
%token _NOTB
%token _PLUS_PLUS
%token _MINUS_MINUS
%token _PLUS
%token _MINUS
%token _TIMES
%token _RELOP
%token _AND
%token _OR
%token _SEMICOLON
%token _ASSIGN

%token EXP
%token STMT
%%

PROG : FUNC MAIN
MAIN : _VOID 'main()' _RSQUARE_BRACKET { }

FUNC : _START_METHOD_DECL { }

TYPE : _INT { }
	 | _ARR _NUM _RSQUARE_BRACKET { }

STMT : _LBRACKET STMT _RBRACKET { }
	 | _IF _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET { }
	 | _IF _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET _ELSE _LBRACKET STMT _RBRACKET { }
	 | _WHILE _LPAREN EXPR _RPAREN _LBRACKET STMT _RBRACKET { }
	 | _PRINTF _LPAREN _VAR _RPAREN _SEMICOLON { }
	 | _VAR _ASSIGN _SCANF _SEMICOLON { }
	 | _VAR _ASSIGN EXPR _SEMICOLON { }
	 | _ARR EXPR _RSQUARE_BRACKET ASSIGN EXPR _SEMICOLON { }

EXP : EXP _PLUS EXP { }
	| EXP _MINUS EXP { }
	| EXP _TIMES EXP { }
	| EXP _RELOP EXP { }
	| EXP _AND EXP { }
	| EXP _OR EXP { }
	| EXP _LSQUARE_BRACKET EXP _RSQUARE_BRACKET { }
	| _LPAREN EXP _RPAREN { }
	| EXP _PLUS_PLUS { }
	| EXP _MINUS_MINUS { }
	| _NOTB EXP { }
	| _NOT EXP { }
	| _VAR { }
	| _NUM { }

	;
%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg){ fputs(msg, stderr); exit(-1);}
