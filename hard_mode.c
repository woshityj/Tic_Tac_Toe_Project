#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

// Creation of GTKWidgets for Graphical User Interface
GtkWidget       *window, *fixed1, *button1, *button2, *button3, *button4, *button5, *button6, *button7, *button8, *button9, *resetbutton, *player1;
GtkBuilder      *builder;

// Global variables
int board[3][3]; //2D Array for Tic Tac Toe Backend
const int PLAYER = -1;
const int COMPUTER = 1;
unsigned int turncounter;

char intToChar(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
    }
}

static void printBoard(int board[3][3])
{
    printf(" %c   | %c  | %c ", intToChar(board[0][0]), intToChar(board[0][1]), intToChar(board[0][2]));
    printf("\n--- | --- | --- \n ");
    printf(" %c   | %c  | %c ", intToChar(board[1][0]), intToChar(board[1][1]), intToChar(board[1][2]));
    printf("\n--- | --- | --- \n ");
    printf(" %c   | %c  | %c ", intToChar(board[2][0]), intToChar(board[2][1]), intToChar(board[2][2]));
    printf("\n--- | --- | --- \n ");
    printf("\n");
}

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
    if (board[row][column] == 1 || board[row][column] == -1)
    {
        printf("Invalid Move!\n");
        return;
    }
    board[row][column] = PLAYER;
    gtk_button_set_label(GTK_BUTTON(widget), "X");
    
    printBoard(board);
    turncounter += 1;
}

int win(int board[3][3]){
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

int minimax(int board[3][3], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int row = -1;
    int col = -1;
    int score = -2;//Losing moves are preferred to no move
    int i, j;
    for(i = 0; i < 3; ++i) {//For all rows,
        for(j = 0; j < 3; ++j){//For all columns,
            if(board[i][j] == 0) {//If box is empty,
            board[i][j] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                row = i;
                col = j;
            }//Pick the one that's worst for the opponent
            board[i][j] = 0;//Reset board after try
        }
        }
    }
    if(row == -1) return 0;
    return score;
}

static void computerMove() {
    int row = -1;
    int col = -1;
    int score = -2;
    int i, j;
    for(i = 0; i < 3; ++i) {
        for(j = 0; j < 3; ++j){
            if(board[i][j] == 0) {
                board[i][j] = COMPUTER;
                int tempScore = -minimax(board, -1);
                board[i][j] = 0;
                if(tempScore > score) {
                    score = tempScore;
                    row = i;
                    col = j;
                }
        }
        }
    }
    //returns a score based on minimax tree at a given node.
    board[row][col] = COMPUTER; // computer move
    switch (row){
        case 0:
            switch (col){
                case 0:
                    gtk_button_set_label(GTK_BUTTON(button1),"O");
                    break;
                case 1:
                    gtk_button_set_label(GTK_BUTTON(button2),"O");
                    break;
                case 2:
                    gtk_button_set_label(GTK_BUTTON(button3),"O");
                    break;
            }
            break;
        case 1:
            switch (col){
                case 0:
                    gtk_button_set_label(GTK_BUTTON(button4),"O");
                    break;
                case 1:
                    gtk_button_set_label(GTK_BUTTON(button5),"O");
                    break;
                case 2:
                    gtk_button_set_label(GTK_BUTTON(button6),"O");
                    break;
            }
            break;
        case 2:
            switch (col){
                case 0:
                    gtk_button_set_label(GTK_BUTTON(button7),"O");
                    break;
                case 1:
                    gtk_button_set_label(GTK_BUTTON(button8),"O");
                    break;
                case 2:
                    gtk_button_set_label(GTK_BUTTON(button9),"O");
                    break;
            }
            break;
    }
    printBoard(board);
}

static void resetBoard()
{
    memset(board, 0, sizeof(board));
    gtk_button_set_label(GTK_BUTTON(button1), " ");
    gtk_button_set_label(GTK_BUTTON(button2), " ");
    gtk_button_set_label(GTK_BUTTON(button3), " ");
    gtk_button_set_label(GTK_BUTTON(button4), " ");
    gtk_button_set_label(GTK_BUTTON(button5), " ");
    gtk_button_set_label(GTK_BUTTON(button6), " ");
    gtk_button_set_label(GTK_BUTTON(button7), " ");
    gtk_button_set_label(GTK_BUTTON(button8), " ");
    gtk_button_set_label(GTK_BUTTON(button9), " ");
}

int main(int argc, char *argv[])
{
    int board[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    gtk_init(&argc, &argv); //init Gtk

    builder = gtk_builder_new_from_file("Tic_Tac_Toe_GUI.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
    button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
    button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
    button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
    button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
    player1 = GTK_WIDGET(gtk_builder_get_object(builder, "player1"));
    g_signal_connect (button1, "clicked", G_CALLBACK (playerMove), "00");
    g_signal_connect (button2, "clicked", G_CALLBACK (playerMove), "01");
    g_signal_connect (button3, "clicked", G_CALLBACK (playerMove), "02");
    g_signal_connect (button4, "clicked", G_CALLBACK (playerMove), "10");
    g_signal_connect (button5, "clicked", G_CALLBACK (playerMove), "11");
    g_signal_connect (button6, "clicked", G_CALLBACK (playerMove), "12");
    g_signal_connect (button7, "clicked", G_CALLBACK (playerMove), "20");
    g_signal_connect (button8, "clicked", G_CALLBACK (playerMove), "21");
    g_signal_connect (button9, "clicked", G_CALLBACK (playerMove), "22");
    resetbutton = GTK_WIDGET(gtk_builder_get_object(builder, "resetbutton"));

    g_signal_connect (resetbutton, "clicked", G_CALLBACK (resetBoard), NULL);
    
    gtk_widget_show(window);

    for (turncounter = 0; turncounter < 9 && win(board) == 0; ++turncounter){
    printf("%d \n", turncounter);
        if(turncounter % 2 == 1){
            computerMove();
        }
        else{
            
        }
    }
    switch(win(board)) {
        case 0:
            printf("A draw. How droll.\n");
            break;
        case 1:
            printBoard(board);
            printf("You lose.\n");
            break;
        case -1:
            printf("You win. Inconceivable!\n");
            break;
    }
    gtk_main();

    return EXIT_SUCCESS;
}