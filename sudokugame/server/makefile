sudoku_server: sudoku_server.o
	gcc -o sudoku_server -L. sudoku_server.o -lserver -lpthread
libserver.a: sudoku_server.o
	ar rv libserver.a sudoku_server.o
sudoku_server.o: sudoku_server.c
	gcc -c -g -I. sudoku_server.c -o sudoku_server.o -lpthread
clean:
	rm -f sudoku_server sudoku_server.o libserver.a
