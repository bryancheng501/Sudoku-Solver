run: sudoku.o gui.o
	gcc -o run sudoku.o gui.o

sudoku.o: sudoku.c
	gcc -c sudoku.c

gui.o: gui.c
	gcc -c gui.c 'pkg-config --cflags gtk+-3.20.0' 'pkg-config --libs gtk+-3.20.0'

clean:
	rm -f run *.o