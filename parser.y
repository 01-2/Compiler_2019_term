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
%token _RETURN 
%token _MAIN_F
%token _COMMA
%token _VARL

%%

PROG : FUNC MAIN
	 ;
MAIN : _VOID _MAIN_F _RSQUARE_BRACKET { }
	 ;
FUNC : _START_METHOD_DECL VARL _RPAREN _LBRACKET STMT _RBRACKET{ }
	 ;

STMT : STMT _SEMICOLON STMT { }
	 |
	 | _LBRACKET STMT _RBRACKET { }
	 | _IF _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET { }
	 | _IF _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET _ELSE _LBRACKET STMT _RBRACKET { }
	 | _WHILE _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET { }
	 | _PRINTF _LPAREN _VAR _RPAREN _SEMICOLON { }
	 | _VAR _ASSIGN _SCANF _SEMICOLON { }
	 | _VAR _ASSIGN EXP _SEMICOLON { }
	 | _ARR EXP _RSQUARE_BRACKET _ASSIGN EXP _SEMICOLON { }
	 ;

EXP : EXP _PLUS EXP _SEMICOLON { }
	| EXP _MINUS EXP _SEMICOLON { }
	| EXP _TIMES EXP _SEMICOLON { }
	| EXP _RELOP EXP _SEMICOLON { }
	| EXP _AND EXP _SEMICOLON { }
	| EXP _OR EXP _SEMICOLON { }
	| EXP _LSQUARE_BRACKET EXP _RSQUARE_BRACKET _SEMICOLON { }
	| _LPAREN EXP _RPAREN _SEMICOLON { }
	| EXP _PLUS_PLUS _SEMICOLON { }
	| EXP _MINUS_MINUS _SEMICOLON { }
	| _NOTB EXP _SEMICOLON { }
	| _NOT EXP _SEMICOLON { }
	| _VAR _SEMICOLON { }
	| _NUM { }
	;

VARL : _VAR _COMMA _VAR { }
	 | _VAR { }
	 ;
%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg){ fputs(msg, stderr); exit(-1);}
