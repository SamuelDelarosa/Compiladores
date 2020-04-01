all: ejecutar

ejecutar: sintactico.tab.o lex.yy.o
	gcc *.o -ll

todo.o: sintactico.tab.c lex.yy.c
	gcc *.c -c

sintactico.tab.c: sintactico.y
	bison -d sintactico.y

lex.yy.c: lexico.l 
	flex lexico.l

clean: 
	rm -f a.out *.o
