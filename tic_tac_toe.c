#include "global.h"
#include "minimax.h"
#include "gui.h"

// Function Prototypes
void changeGamemode(GtkWidget *widget, gpointer data);
void playerMove(GtkWidget *widget, gpointer data);
void computerMove();
int checkFreeSpaces();
int draw(int freeSpaces);
void printBoard();
int checkWinner();
void announceWinner(int winner, int draw);

int check_draw, check_winner;

// Main Functions
void playerMove(GtkWidget *widget, gpointer data)
{
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
    Check every column to see if there is a Winning Combination
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