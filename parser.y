%{
	#include <ctype.h>
	#include <stdio.h>
	
	#define YYSTYPE char*

	int yyerror(const char *msg);
	int yylex();
	int yyparse();

	node *root;
	int stmt_cnt = 0;
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

PROG : FUNC MAIN {
		root = (node *)malloc(sizeof(node));
	 }
	 ;
MAIN : FUNC MAIN { 
		 // function, function, ....?
		 $$ = createFuncDeclNode($1.token, $1.type, $1.name, root); 
	   }
	 | _VOID _MAIN_F _RSQUARE_BRACKET {
		$$ = createMainDeclNode(tok, stmt_cnt, root);
	   }
	 ;
FUNC : _START_METHOD_DECL VARL _RPAREN _LBRACKET STMT _RBRACKET{	
		char *retStruct = strtok($1, " ");
		char *funcName = strtok(NULL, " ");
		TYPE t = VOID;
		if(!strcmp(retStruct, "int")) t = INT;
		// case : return integer array
		else if(!strcmp(retStruct, "int[")) t = INT_ARRAY;
		else t = VOID;
		createFuncDeclNode(tok, t, funcName, root);
		createFuncBodyNode(tok, t, stmt_cnt, root);
	 }
	 ;

STMT : STMT _SEMICOLON STMT { }
	 |
	 | _LBRACKET STMT _RBRACKET { $$ =  }
	 | _IF _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET { }
	 | _IF _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET _ELSE _LBRACKET STMT _RBRACKET { }
	 | _WHILE _LPAREN EXP _RPAREN _LBRACKET STMT _RBRACKET { }
	 | _PRINTF _LPAREN _VAR _RPAREN _SEMICOLON { }
	 | _VAR _ASSIGN _SCANF _SEMICOLON { 
		$$ = createVarDeclNode(); 
	 }
	 | _VAR _ASSIGN EXP _SEMICOLON { 
		 char *vtype = strtok($1, " ");
		 char *varName = strtok(NULL, " ");
		 TYPE t = VOID;
		 if(!strcmp(vtype, "int")) t = INT;
		 else if(!strcmp(vtype, "int[")) t = INT_ARRAY;
		 
		 $$ = createVarDeclNode(t, 0, 0, varName, ); 
	 }
	 | _ARR EXP _RSQUARE_BRACKET _ASSIGN EXP _SEMICOLON { }
	 ;

EXP : EXP _PLUS EXP _SEMICOLON { $$ = createArithmeticNode( , ,$1, $3); }
	| EXP _MINUS EXP _SEMICOLON { $$ = createArithmeticNode( , , $1, $3); }
	| EXP _TIMES EXP _SEMICOLON { $$ = createArithmeticNode( , , $1, $3); }
	| EXP _RELOP EXP _SEMICOLON { 
		if($2 == '>') $$ = createConditionNode( , , $1, $3);
		else $$ = createConditionNode(, , $1, $3);
	}
	| EXP _AND EXP _SEMICOLON { $$ = createArithmeticNode( , , $1, $3); }
	| EXP _OR EXP _SEMICOLON { $$ = createArithmeticNode(, , $1, $3); }
	| EXP _LSQUARE_BRACKET EXP _RSQUARE_BRACKET _SEMICOLON { // case ???? 
	}
	| _LPAREN EXP _RPAREN _SEMICOLON { // + 
	}
	| EXP _PLUS_PLUS _SEMICOLON { $$ = createAffixNode(, $1); }
	| EXP _MINUS_MINUS _SEMICOLON { $$ = createAffixNode( , $1); }
	| _NOTB EXP _SEMICOLON { $$ = createUnaryArithmeticNode( , $2); }
	| _NOT EXP _SEMICOLON { $$ = createUnaryArithmeticNode(, $2); }
	| _VAR _SEMICOLON {  }
	| _NUM _SEMICOLON { $$ = createConstNode(INT, }
	;

VARL : _VAR _COMMA _VAR { }
	 | _VAR { }
	 ;
%%
int main() { yyparse(); return 0; }
int yyerror(const char *msg){ fputs(msg, stderr); exit(-1);}
