#Gabriel Antônio Pereira - 0032449

etapa4: hash.o y.tab.o lex.yy.o  main.o ast.o semantic.o
	gcc  -Wall hash.o y.tab.o lex.yy.o  main.o ast.o semantic.o -o etapa4

ast.o : ast.c
	gcc  -Wall -c ast.c

semantic.o : semantic.c
	gcc  -Wall -c semantic.c

y.tab.o: y.tab.c 
	gcc  -Wall -c y.tab.c

y.tab.c: parser.y
	yacc -d parser.y 

lex.yy.o: lex.yy.c
	gcc -Wall -c lex.yy.c

lex.yy.c: scanner.l y.tab.c
	lex scanner.l

hash.o: hash.c
	gcc -Wall -c hash.c

main.o: main.c y.tab.c
	gcc -Wall -c main.c
 
clean: 
	rm *.o lex.yy.c y.tab.c y.tab.h etapa4