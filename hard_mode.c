#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

// Creation of GTKWidgets for Graphical User Interface
GtkWidget       *window, *fixed1, *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9, *resetbutton, *player1;
GtkBuilder      *builder;

// Global variables
char board[3][3]; //2D Array for Tic Tac Toe Backend
const char PLAYER = 'X';
const char COMPUTER = 'O';
int turncounter = 0;

static void playerMove (GtkWidget *widget, gpointer data)
{
    int row, column;
    if (strcmp(data, "00") == 0)
    {
        row = 0;
        column = 0;
    }
    else if (strcmp(data, "01") == 0)
    {
        row = 0;
        column = 1;
    }
    else if (strcmp(data, "02") == 0)
    {
        row = 0;
        column = 2;
    }
    else if (strcmp(data, "10") == 0)
    {
        row = 1;
        column = 0;
    }
    else if (strcmp(data, "11") == 0)
    {
        row = 1;
        column = 1;
    }
    else if (strcmp(data, "12") == 0)
    {
        row = 1;
        column = 2;
    }
    else if (strcmp(data, "20") == 0)
    {
        row = 2;
        column = 0;
    }
    else if (strcmp(data, "21") == 0)
    {
        row = 2;
        column = 1;
    }
    else if (strcmp(data, "22") == 0)
    {
        row = 2;
        column = 2;
    }

    /* 
    Checks if the position on the board is taken 
    If the position is occupied, it will output "Invalid Move!" in the terminal
    and return
    */
    if (board[row][column] == 'X' || board[row][column] == 'O')
    {
        printf("Invalid Move!\n");
        return;
    }

    if (turncounter % 2 == 0 || turncounter == 0) 
    {
        board[row][column] = PLAYER;
        gtk_button_set_label(GTK_BUTTON(widget), "X");
    }
    else if (turncounter % 2 == 1)
    {
        board[row][column] = COMPUTER;
        gtk_button_set_label(GTK_BUTTON(widget), "O");
    }
    
    printBoard();
    turncounter += 1;
}

int win(char board[3][3]){
    //Check rows
    for (int row = 0; row < 3; ++row){
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]){
            if (board[row][0] == PLAYER){
                return -1;
            }
            else if (board[row][0] == COMPUTER){
                return 1;
            }
        }
    }

    //Check columns
    for (int col = 0; col < 3; ++col){
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]){
            if (board[0][col] == PLAYER){
                return -1;
            }
            else if (board[0][col] == COMPUTER){
                return 1;
            }
        }
    }

    //Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]){
        if (board[0][0] == PLAYER){
            return -1;
        }
        else if (board[0][0] == COMPUTER){
            return 1;
        }
    }
    else if (board[0][2] == board[1][1] && board[1][1] == board[2][0]){
        if (board[0][0] == PLAYER){
            return -1;
        }
        else if (board[0][0] == COMPUTER){
            return 1;
        }
    }
    return 0;
}

int checkFreeSpaces()
{
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

static void computerMove (GtkWidget *widget, gpointer data)
{
    printBoard();
}