all: main
main: main.o mythreadpool.o
	gcc -l pthread main.o mythreadpool.o -o main
main.o: main.c mythreadpool.h 
	gcc -c main.c 
mythreadpool.o: mythreadpool.c mythreadpool.h
	gcc -c mythreadpool.c
