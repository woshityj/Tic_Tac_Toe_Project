/* Libraries */
#include "global.h"
#include "gui.h"
#include "tic_tac_toe.h"
#include "minimax.h"

/* Function Prototypes */
void initializeGUI();
void changeGamemode(GtkWidget *widget, gpointer data);
void playerMove(GtkWidget *widget, gpointer data);
void computerMove();
void announceWinner(int winner, int draw);
int checkFreeSpaces();
int draw(int freeSpaces);
void printBoard();
int checkWinner();
void resetBoard();
void disableButtons();
void destroy(GtkWidget *widget, gpointer data);
int evaluate();
int minimax(int depth, int isMax);
void findBestMove();
int max(int num1, int num2);
int min(int num1, int num2);
void setAIDifficulty();
int getAIDecision();

/* Declaring value to global variables */
int turncounter = 0;
int player_1_score = 0;
int player_2_score = 0;
int gamemode = 0;
int bestMove[2] = {-1, -1};
float aiPercentage = 0;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    initializeGUI();
    srand(time(NULL));
}