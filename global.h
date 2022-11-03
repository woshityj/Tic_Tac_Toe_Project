#ifndef GLOBAL_H
#define GLOBAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

/* Constant Variables */
#define PLAYER 'X'
#define COMPUTER 'O'

/* Creation of GTKWidgets for Graphical User Interface */
extern GtkWidget       *window;

/* Navigation Bar GTKWidgets */
extern GtkWidget       *player_vs_player;
extern GtkWidget       *player_vs_computer_easy;
extern GtkWidget       *player_vs_computer_medium;
extern GtkWidget       *player_vs_computer_hard;
extern GtkWidget       *quit;

/* Game Display */
extern GtkWidget       *stackfixed1;
extern GtkWidget       *announce;
extern GtkWidget       *player1;
extern GtkWidget       *player2;
extern GtkWidget       *score1;
extern GtkWidget       *score2;
extern GtkWidget       *resetbutton;
extern GtkWidget       *button1;
extern GtkWidget       *button2;
extern GtkWidget       *button3;
extern GtkWidget       *button4;
extern GtkWidget       *button5;
extern GtkWidget       *button6;
extern GtkWidget       *button7;
extern GtkWidget       *button8;
extern GtkWidget       *button9;
extern GtkBuilder      *builder;

/* Global Variables */
extern char board[3][3];
extern int turncounter;
extern int player_1_score;
extern int player_2_score;
extern int gamemode;
extern int bestMove[2];
extern float aiPercentage;
extern int row;
extern int column;
extern int check_winner;
extern int check_draw;

#endif