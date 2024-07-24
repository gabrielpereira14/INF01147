#Gabriel Antônio Pereira - 0032449

etapa2: y.tab.o lex.yy.o hash.o main.o 
	gcc  -Wall lex.yy.o hash.o main.o y.tab.o -o etapa2

y.tab.o: y.tab.c 
	gcc  -Wall -c y.tab.c

y.tab.c: parser.y lex.yy.o
	yacc -d parser.y 

lex.yy.o: lex.yy.c
	gcc -Wall -c lex.yy.c

lex.yy.c: scanner.l
	lex scanner.l

hash.o: hash.c
	gcc -Wall -c hash.c

main.o: main.c y.tab.c
	gcc -Wall -c main.c
 
clean: 
	rm *.o lex.yy.c y.tab.c etapa2


