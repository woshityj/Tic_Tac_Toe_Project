#ifndef GUI_H
#define GUI_H

#include "global.h"

//function declaration

void initializeGUI();

void resetBoard();

void disableButtons();

void destroy(GtkWidget *widget, gpointer data);

void changeGamemode(GtkWidget *widget, gpointer data);

void announceWinner(int winner, int draw);

#endif