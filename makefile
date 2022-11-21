all: main 

main: main.c
	gcc -Wall -g $(shell pkg-config --cflags gtk+-3.0 ) -o game.exe main.c gui.c tic_tac_toe.c minimax.c machine_learning.c $(shell pkg-config --libs gtk+-3.0 )