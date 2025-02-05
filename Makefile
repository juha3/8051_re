all: main

main: main.o op.o ui.o
	gcc main.o op.o ui.o -lncurses -o rev
ui.o:	ui.c
	gcc -c -Wall ui.c

main.o: main.c
	gcc -c -Wall main.c
op.o: op.c
	gcc -c -Wall op.c
clean:
	rm -rf *o rev



