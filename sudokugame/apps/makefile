Main: Main.o
	gcc -o Main -L../lib Main.o -lsudoku
Main.o: Main.c
	gcc -g -c -I../include Main.c -o Main.o -lpthread
claen:
	rm Main.o Main 
