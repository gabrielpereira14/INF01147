#Gabriel Antônio Pereira - 0032449

etapa3: hash.o y.tab.o lex.yy.o  main.o ast.o
	gcc  -Wall hash.o y.tab.o lex.yy.o  main.o ast.o -o etapa3

ast.o : ast.c
	gcc  -Wall -c ast.c

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
	rm *.o lex.yy.c y.tab.c y.tab.h etapa3 


