libsudoku.a: Sudoku.o
	ar rv libsudoku.a Sudoku.o
Sudoku.o: Sudoku.c
	gcc -c -g -I../include Sudoku.c -o Sudoku.o
clean:
	rm -f Sudoku.o libsudoku.a
