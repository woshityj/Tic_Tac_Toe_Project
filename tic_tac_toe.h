#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

#include "global.h"

//function declaration
void changeGamemode(GtkWidget *widget, gpointer data);

void playerMove(GtkWidget *widget, gpointer data);

void computerMove();

int checkFreeSpaces();

int draw(int freeSpaces);

void printBoard();

int checkWinner();

#endif