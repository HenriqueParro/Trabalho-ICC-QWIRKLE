erros.o : erros.c
	gcc -o erros.o -c erros.c

gerenciador.o : gerenciador.c
	gcc -o gerenciador.o -c gerenciador.c

help.o : help.c
	gcc -o help.o -c help.c

interface.o : interface.c
	gcc -o interface.o -c interface.c

tabuleiro.o : tabuleiro.c
	gcc -o tabuleiro.o -c tabuleiro.c

util.o : util.c 
	gcc -o util.o -c util.c

main.o : main.c
	gcc -o main.o -c main.c

main : main.o erros.o gerenciador.o help.o interface.o tabuleiro.o util.o
	gcc -o main main.o erros.o gerenciador.o help.o interface.o  tabuleiro.o util.o 

all : main

run : main
	./main

clean :
	@rm *.o 
