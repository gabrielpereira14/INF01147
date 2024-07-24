etapa1: lex.yy.o hash.o main.o
	gcc lex.yy.o hash.o main.o -o etapa1


lex.yy.o: lex.yy.c
	gcc -c lex.yy.c

lex.yy.c: scanner.l
	lex scanner.l

hash.o: hash.c
	gcc -c hash.c

main.o: main.c
	gcc -c main.c

clean: 
	rm *.o lex.yy.c etapa1


