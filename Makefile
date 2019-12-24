all: lex.yy.c y.tab.c y.tab.h ast.o
	gcc lex.yy.c y.tab.c ast.o -o overload
lex.yy.c: scanner.l y.tab.c
	flex scanner.l
y.tab.c: parser.y
	bison -dy parser.y
ast.o: ast.c
	gcc -c ast.c

clean:
	rm -rf lex.yy.c y.tab.c y.tab.h ast.o overload
