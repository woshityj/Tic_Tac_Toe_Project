// gcc $( pkg-config --cflags gtk+-3.0 ) -o game gui.c $( pkg-config --libs gtk+-3.0 )

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

/* Creation of GTKWidgets for Graphical User Interface */
GtkWidget       *window;

/* Navigation Bar GTKWidgets */
GtkWidget       *player_vs_player;
GtkWidget       *player_vs_computer_easy;
GtkWidget       *player_vs_computer_medium;
GtkWidget       *player_vs_computer_hard;
GtkWidget       *quit;

/* Game Display */
GtkWidget       *stackfixed1;
GtkWidget       *announce;
GtkWidget       *player1;
GtkWidget       *player2;
GtkWidget       *score1;
GtkWidget       *score2;
GtkWidget       *resetbutton;
GtkWidget       *button1;
GtkWidget       *button2;
GtkWidget       *button3;
GtkWidget       *button4;
GtkWidget       *button5;
GtkWidget       *button6;
GtkWidget       *button7;
GtkWidget       *button8;
GtkWidget       *button9;
GtkBuilder      *builder;

/* Constant Variables */
#define PLAYER 'X'
#define COMPUTER 'O'

/* Global Variables */
char board[3][3];
int turncounter = 0;
int player_1_score = 0;
int player_2_score = 0;
static int gamemode = 0;
int bestMove[2] = {-1, -1};
float aiPercentage = 0;

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

/* 
    Set a random seed for the AI Probability Calculation for 
    the AI's Difficulty
 */

/* Main Functions */
int main(int argc, char *argv[])
{    
    gtk_init(&argc, &argv);
    initializeGUI();
    srand(time(NULL));

    
    /* Test Case for MiniMax Algorithm */
    // board[0][0] = PLAYER;
    // board[0][1] = COMPUTER;
    // board[0][2] = PLAYER;

    // board[1][0] = COMPUTER;
    // board[1][1] = COMPUTER;
    // board[1][2] = PLAYER;

    // findBestMove();
    // printf("\n%d  %d", bestMove[0], bestMove[1]);
    // printBoard();
}

void initializeGUI()
{

    builder = gtk_builder_new_from_file("gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    player_vs_player = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_player"));
    g_signal_connect(player_vs_player, "clicked", G_CALLBACK(changeGamemode), "0");
    player_vs_computer_easy = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_computer_easy"));
    g_signal_connect(player_vs_computer_easy, "clicked", G_CALLBACK(changeGamemode), "1");
    player_vs_computer_medium = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_computer_medium"));
    g_signal_connect(player_vs_computer_medium, "clicked", G_CALLBACK(changeGamemode), "2");
    player_vs_computer_hard = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_computer_hard"));
    g_signal_connect(player_vs_computer_hard, "clicked", G_CALLBACK(changeGamemode), "3");
    quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    g_signal_connect(quit, "clicked", G_CALLBACK(destroy), window);

    stackfixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "stackfixed1"));
    
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    g_signal_connect(button1, "clicked", G_CALLBACK(playerMove), &board[0][0]);
    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    g_signal_connect(button2, "clicked", G_CALLBACK(playerMove), &board[0][1]);
    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    g_signal_connect(button3, "clicked", G_CALLBACK(playerMove), &board[0][2]);
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
    g_signal_connect(button4, "clicked", G_CALLBACK(playerMove), &board[1][0]);
    button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect(button5, "clicked", G_CALLBACK(playerMove), &board[1][1]);
    button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
    g_signal_connect(button6, "clicked", G_CALLBACK(playerMove), &board[1][2]);
    button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
    g_signal_connect(button7, "clicked", G_CALLBACK(playerMove), &board[2][0]);
    button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
    g_signal_connect(button8, "clicked", G_CALLBACK(playerMove), &board[2][1]);
    button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
    g_signal_connect(button9, "clicked", G_CALLBACK(playerMove), &board[2][2]);

    resetbutton = GTK_WIDGET(gtk_builder_get_object(builder, "resetbutton"));
    g_signal_connect(resetbutton, "clicked", G_CALLBACK(resetBoard), NULL);

    announce = GTK_WIDGET(gtk_builder_get_object(builder, "announce"));

    player1 = GTK_WIDGET(gtk_builder_get_object(builder, "player1"));
    player2 = GTK_WIDGET(gtk_builder_get_object(builder, "player2"));

    score1 = GTK_WIDGET(gtk_builder_get_object(builder, "score1"));
    score2 = GTK_WIDGET(gtk_builder_get_object(builder, "score2"));

    gtk_widget_show(window);

    gtk_main();
}

void changeGamemode(GtkWidget *widget, gpointer data)
{
    char* ptr_gamemode = data;

    if (*ptr_gamemode == '0')
    {
        gamemode = 0;
        resetBoard();
    }
    else if (*ptr_gamemode == '1')
    {
        gamemode = 1;
        setAIDifficulty();
        gtk_label_set_label(GTK_LABEL(player2), "Computer (Easy)");
        resetBoard();
    }
    else if (*ptr_gamemode == '2')
    {
        gamemode = 2;
        setAIDifficulty();
        gtk_label_set_label(GTK_LABEL(player2), "Computer (Medium)");
        resetBoard();
    }
    else if (*ptr_gamemode == '3')
    {
        gamemode = 3;
        setAIDifficulty();
        gtk_label_set_label(GTK_LABEL(player2), "Computer (Hard)");
        resetBoard();
    }
}

void playerMove(GtkWidget *widget, gpointer data)
{
    int row, column, check_winner, check_draw;
    /* Pointer to the Board Array */
    char* ptr_board = data;

    /* Check if the space is occupied */
    if (*ptr_board == 'X' || *ptr_board == 'O')
    {
        printf("\nInvalid Move!\n");
        return;
    }

    if (gamemode == 0)
    {
        if (turncounter % 2 == 0 || turncounter == 0)
        {
            *ptr_board = PLAYER;
            gtk_button_set_label(GTK_BUTTON(widget), "X");
            turncounter = turncounter + 1;

        }
        else if (turncounter % 2 == 1 && gamemode == 0)
        {
            *ptr_board = COMPUTER;
            gtk_button_set_label(GTK_BUTTON(widget), "O");
            turncounter = turncounter + 1;
        }
        check_winner = checkWinner();
        check_draw = draw(checkFreeSpaces());
        announceWinner(check_winner, check_draw);
    }

    if (gamemode == 1 || gamemode == 2 || gamemode == 3)
    {
        *ptr_board = PLAYER;
        gtk_button_set_label(GTK_BUTTON(widget), "X");
        turncounter = turncounter + 1;
        check_winner = checkWinner();
        check_draw = draw(checkFreeSpaces());
        announceWinner(check_winner, check_draw);

        if (check_winner == 0 && check_draw == 0)
        {
            computerMove();
            turncounter = turncounter + 1;
            check_winner = checkWinner();
            check_draw = draw(checkFreeSpaces());
            announceWinner(check_winner, check_draw);
        }
    }

    printBoard();
}

void computerMove()
{
    int ai_decision = getAIDecision();
    printf("\n%d", ai_decision);
    int ai_row, ai_column;
    int x, y;

    if (ai_decision == 1)
    {
        findBestMove();
        ai_row = bestMove[0];
        ai_column = bestMove[1];
    }
    else if (ai_decision == 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (strlen(&board[x][y]) != 0);
        
        ai_row = x;
        ai_column = y;
    }

    board[ai_row][ai_column] = COMPUTER;
    if (ai_row == 0 && ai_column == 0)
    {
        gtk_button_set_label(GTK_BUTTON(button1), "O");
    }
    else if (ai_row == 0 && ai_column == 1)
    {
        gtk_button_set_label(GTK_BUTTON(button2), "O");
    }
    else if (ai_row == 0 && ai_column == 2)
    {
        gtk_button_set_label(GTK_BUTTON(button3), "O");
    }
    else if (ai_row == 1 && ai_column == 0)
    {
        gtk_button_set_label(GTK_BUTTON(button4), "O");
    }
    else if (ai_row == 1 && ai_column == 1)
    {
        gtk_button_set_label(GTK_BUTTON(button5), "O");
    }
    else if (ai_row == 1 && ai_column == 2)
    {
        gtk_button_set_label(GTK_BUTTON(button6), "O");
    }
    else if (ai_row == 2 && ai_column == 0)
    {
        gtk_button_set_label(GTK_BUTTON(button7), "O");
    }
    else if (ai_row == 2 && ai_column == 1)
    {
        gtk_button_set_label(GTK_BUTTON(button8), "O");
    }
    else if (ai_row == 2 && ai_column == 2)
    {
        gtk_button_set_label(GTK_BUTTON(button9), "O");
    }
}

void announceWinner(int winner, int draw)
{
    if (winner == -1)
    {
        gtk_label_set_label(GTK_LABEL(announce), "Player 1 has won!");
        player_1_score = player_1_score + 1;
        gchar *display;
        display = g_strdup_printf("%d", player_1_score);
        gtk_label_set_label(GTK_LABEL(score1), display);
        g_free(display);
        disableButtons();
    }
    else if (winner == 1)
    {
        gtk_label_set_label(GTK_LABEL(announce), "Player 2 has won!");
        player_2_score = player_2_score + 1;
        gchar *display;
        display = g_strdup_printf("%d", player_2_score);
        gtk_label_set_label(GTK_LABEL(score2), display);
        g_free(display);
        disableButtons();
    }
    else if (draw == 1 && winner == 0)
    {
        gtk_label_set_label(GTK_LABEL(announce), "It's a Draw!");
        disableButtons();
    }
}

int checkFreeSpaces()
{
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (strlen(&board[i][j]) != 0)
            {
                freeSpaces = freeSpaces - 1;
            }
        }
    }

    return freeSpaces;
}

int draw(int freeSpaces)
{
    if (freeSpaces == 0)
    {
        return 1;
    }
    return 0;
}

void printBoard()
{
    printf("\n");
    printf(" %c  | %c   | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n--- | --- | --- \n ");
    printf(" %c | %c   | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n--- | --- | --- \n ");
    printf(" %c | %c   | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n--- | --- | --- \n ");
    printf("\n");
}

int checkWinner()
{
    /* 
    Check every row to see if there is a Winning Combination
    */
    for (int row = 0; row < 3; ++row){
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2] && strlen(&board[row][0]) != 0){
            if (board[row][0] == PLAYER){
                return -1;
            }
            else if (board[row][0] == COMPUTER){
                return 1;
            }
        }
    }

    /*
    Checek every column to see if there is a Winning Combination
    */
    for (int col = 0; col < 3; ++col){
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && strlen(&board[0][col]) != 0){
            if (board[0][col] == PLAYER){
                return -1;
            }
            else if (board[0][col] == COMPUTER){
                return 1;
            }
        }
    }


    /*
    Check Left-to-Right downward diagonally to see if there is a Winning Combination
    */
    int count = 0;
    for (int col = 0; col < 3; ++col)
    {
        if (board[col][col] == COMPUTER)
        {
            count = count + 1;
        }
        else if (board[col][col] == PLAYER)
        {
            count = count - 1;
        }
        else
        {
            count = count + 0;
        }
    }
    if (count == 3 || count == -3)
    {
        /*
        Returns either 1 or -1 to declare the appropriate winner
        */
        return count / abs(count); 
    }

    /*
    Check Left-to-Right upward diagonally to see if there is a Winning Combination
    */
    count = 0;
    for (int col = 0; col < 3; ++col)
    {
        if (board[col][2 - col] == COMPUTER)
        {
            count = count + 1;
        }
        else if (board[col][2 - col] == PLAYER)
        {
            count = count - 1;
        }
        else
        {
            count = count + 0;
        }
    }
    if (count == 3 || count == -3)
    {
        /*
        Returns either 1 or -1 to declare the appropriate winner
        */
        return count / abs(count);
    }
    
    return 0;
}

void resetBoard()
{
    memset(board, 0, sizeof(board));
    turncounter = 0;

    gtk_label_set_label(GTK_LABEL(announce), " ");

    gtk_button_set_label(GTK_BUTTON(button1), " ");
    gtk_button_set_label(GTK_BUTTON(button2), " ");
    gtk_button_set_label(GTK_BUTTON(button3), " ");
    gtk_button_set_label(GTK_BUTTON(button4), " ");
    gtk_button_set_label(GTK_BUTTON(button5), " ");
    gtk_button_set_label(GTK_BUTTON(button6), " ");
    gtk_button_set_label(GTK_BUTTON(button7), " ");
    gtk_button_set_label(GTK_BUTTON(button8), " ");
    gtk_button_set_label(GTK_BUTTON(button9), " ");

    gtk_widget_set_sensitive (button1, TRUE);
    gtk_widget_set_sensitive (button2, TRUE);
    gtk_widget_set_sensitive (button3, TRUE);
    gtk_widget_set_sensitive (button4, TRUE);
    gtk_widget_set_sensitive (button5, TRUE);
    gtk_widget_set_sensitive (button6, TRUE);
    gtk_widget_set_sensitive (button7, TRUE);
    gtk_widget_set_sensitive (button8, TRUE);
    gtk_widget_set_sensitive (button9, TRUE);
}

void disableButtons()
{
    gtk_widget_set_sensitive (button1, FALSE);
    gtk_widget_set_sensitive (button2, FALSE);
    gtk_widget_set_sensitive (button3, FALSE);
    gtk_widget_set_sensitive (button4, FALSE);
    gtk_widget_set_sensitive (button5, FALSE);
    gtk_widget_set_sensitive (button6, FALSE);
    gtk_widget_set_sensitive (button7, FALSE);
    gtk_widget_set_sensitive (button8, FALSE);
    gtk_widget_set_sensitive (button9, FALSE);
}

void destroy(GtkWidget *widget, gpointer data)
{
    gtk_window_close(data);
}

int evaluate()
{
    int check_winner;
    check_winner = checkWinner();
    if (check_winner == -1)
    {
        return -10;
    }
    else if (check_winner == 1)
    {
        return +10;
    }
    else
    {
        return 0;
    }

}

int minimax(int depth, int isMax)
{
    int score, spaces_left;

    score = evaluate();
    
    if (score == 10)
    {
        return score;
    }

    if (score == -10)
    {
        return score;
    }

    spaces_left = checkFreeSpaces();
    if (spaces_left == 0)
    {
        return 0;
    }

    if (isMax == 1)
    {
        int best = -1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (strlen(&board[i][j]) == 0)
                {
                    board[i][j] = COMPUTER;

                    best = max(best, minimax(depth + 1, !isMax));

                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
    else
    {
        int best = 1000;

        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (strlen(&board[i][j]) == 0)
                {
                    board[i][j] = PLAYER;

                    best = min(best, minimax(depth + 1, !isMax));

                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
}

void findBestMove()
{
    int bestVal = -1000;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (strlen(&board[i][j]) == 0)
            {
                board[i][j] = COMPUTER;

                int moveVal = minimax(0, 0);

                board[i][j] = 0;

                if (moveVal > bestVal)
                {
                    bestMove[0] = i;
                    bestMove[1] = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move: %d\n\n", bestVal);
}

int max(int num1, int num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    return num2;
}

int min(int num1, int num2)
{
    if (num1 < num2)
    {
        return num1;
    }
    return num2;
}

void setAIDifficulty()
{
    if (gamemode == 1)
    {
        aiPercentage = 0.0;
    }
    else if (gamemode == 2)
    {
        aiPercentage = 0.75;
    }
    else if (gamemode == 3)
    {
        aiPercentage = 1.0;
    }
    return;
}

/* Write a function to calculate the possibility of picking the MiniMax Best Move and a random move on the board */

int getAIDecision()
{
    float value;
    value = (float) rand() / RAND_MAX;
    printf("\nRandomised Value is:");
    printf("%f", value);

    if (value <= aiPercentage)
    {
        printf("\n Best Move");
        return 1; /* Return 1 indicates that AI uses MiniMax Algorithm */ 
    }
    printf("\n Not Best Move");
    return 0; /* Return 0 indicates that AI uses a randomiser */
}