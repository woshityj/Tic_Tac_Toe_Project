#include "global.h"
#include "minimax.h"
#include "gui.h"
#include "machine_learning.h"

// Function Prototypes
void playerMove(GtkWidget *widget, gpointer data);
void computerMove();
int checkFreeSpaces();
int draw(int freeSpaces);
void printBoard();
int checkWinner();
void announceWinner(int winner, int draw);

int check_draw, check_winner;

/*------------------------------------------------- playerMove -----
|  Function playerMove
|
|  Purpose:  Enables the User/Player to place their piece on the Tic Tac Toe
|            Board GUI and Board Array, depending on the current Gamemode the User is on.
|            If the gamemode is not on Player Vs Player, after the Player places
|            their piece on the Board GUI and Board Array, the AI/Computer will immediately place their
|            piece on the Board GUI and Board Array.
|           
|            After each placement of a piece on the Board by the Player or the Computer, we will check if
|            a win condition is fulfilled via the checkWinner() function or a draw has occured via the 
|            draw() function. If a win condition is fulfilled, the winner will be announced.
|
|  Parameters:
|      GtkWidget *widget -- Passes the Memory Address of the respective button clicked on the Tic Tac Toe Board
|      gpointer data -- Passes the Memory Address of the data passed through the respective button clicked on the Tic Tac Toe Board.
|                       In this case, the memory address of the respective position of the Global Tic Tac Toe Board Array is passed to the function.
|                       For instance, if Row 0 and Column 0 of the Board is clicked, the memory address of the Board Array [0][0] is passed.
|
*-------------------------------------------------------------------*/
void playerMove(GtkWidget *widget, gpointer data)
{
    /* ptr_board is a pointer to the specific Board Array position */
    char *ptr_board = data;

    /* Checks if the position on the Board Array is occupied */
    if (*ptr_board == 'X' || *ptr_board == 'O')
    {
        printf("\nInvalid Move!\n");
        return;
    }

    /* 
       Gamemode 0 indicates a the Player vs Player Gamemode whereby the piece
       piece played on the board would depend on the current turn counter,
       where "X" will be placed if its an even number and an "O" will be placed
       if its an odd number

       After the Player places his piece on the board, we will check if there is a Winner
       or a Draw via the checkWinner() function and the draw() function.
     */
    if (gamemode == 0)
    {
        if (turncounter % 2 == 0)
        {
            *ptr_board = PLAYER;
            gtk_button_set_label(GTK_BUTTON(widget), "X");
            turncounter = turncounter + 1;

        }
        else if (turncounter % 2 == 1)
        {
            *ptr_board = COMPUTER;
            gtk_button_set_label(GTK_BUTTON(widget), "O");
            turncounter = turncounter + 1;
        }
        check_winner = checkWinner();
        check_draw = draw(checkFreeSpaces());
        announceWinner(check_winner, check_draw);
    }

    /* 
       Gamemode 1, 2, 3 indicates a the Player vs Computer Gamemode whereby after 
       the Player places his piece on the board, the Computer would make its move
       immediately after via the computerMove() function.

       After the Player and Computer places his piece on the board, we will check if there is a Winner
       or a Draw via the checkWinner() function and the draw() function.
     */

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

    if (gamemode == 4)
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

/*------------------------------------------------- computerMove -----
|  Function computerMove
|
|  Purpose:  Based on ai_decision variable returned from the getAIDecision() function, if the ai_decision is 1,
|            the decision of the AI will be based off the MiniMax Algorithm. If the ai_decision is 0, then a random
|            spot on the board will be chosen.
|            Based on the row and column retrieved from the MiniMax Algorithm or Randomiser, we will place the Computer's piece
|            on the Board Array and the respective button on the Board GUI.
|
*-------------------------------------------------------------------*/
void computerMove()
{
    int ai_row = 0;
    int ai_column = 0;
    int x, y;
    if (gamemode == 1 || gamemode == 2 || gamemode == 3)
    {
        /* 
        ai_decision will contain the value which decides if the 
        MiniMax Algorithm will be used or a Random position on the board 
        will be picked
        */
        int ai_decision = getAIDecision();
        printf("\n%d", ai_decision);


        /* 
        If the ai_decision is 1, we will make use of the findBestMove() to get 
        the best row and column returned from the MiniMax Algorithm
        */
        if (ai_decision == 1)
        {
            findBestMove();
            ai_row = bestMove[0];
            ai_column = bestMove[1];
        }

        /* 
        If the ai_decision is 0, we will make use of the rand() function to select
        a random free space on the board
        */

        if (ai_decision == 0)
        {
            do
            {
                x = rand() % 3;
                y = rand() % 3;
            } while (strlen(&board[x][y]) != 0);
            
            ai_row = x;
            ai_column = y;
        }
    }
    
    if (gamemode == 4)
    {
        findBestMoveML();
        ai_row = bestMove[0];
        ai_column = bestMove[1];
    }

    /* 
       Based on the row and column returned from the ai_decision conditions,
       we will set Global Board Array to occupy the COMPUTER piece "O" and 
       set the Board GUI to display the COMPUTER piece "O".
     */
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

/*------------------------------------------------- checkFreeSpaces -----
|  Function checkFreeSpaces
|
|  Purpose:  Checks the current Tic Tac Toe Board Array for the number of free spaces left By
|            checking if the length of the specific position of the Board Array is 1 (Occupied).
|            If the length of the position is 1, the number of free spaces will decrease by 1.
|
|  Returns:  The number of free spaces left on the board.
*-------------------------------------------------------------------*/

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

/*------------------------------------------------- draw -----
|  Function draw
|
|  Purpose:  Based on the number of free spaces left on the Board, if the number of 
|            free spaces is 0, it will return the value 1, indicating a draw.
|
|  Parameters:
|      freeSpaces -- Passes the number of free spaces left on the board
|
|  Returns:  The number of free spaces left on the board.
*-------------------------------------------------------------------*/

int draw(int freeSpaces)
{
    if (freeSpaces == 0)
    {
        return 1;
    }
    return 0;
}

/*------------------------------------------------- printBoard -----
|  Function printBoard
|
|  Purpose:  Based on the current Global Tic Tac Toe Board Array, it will print out the current
|            values of the Board Array onto the terminal for verification purposes.
|
*-------------------------------------------------------------------*/

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

/*------------------------------------------------- checkWinner -----
|  Function checkWinner
|
|  Purpose:  Based on the Global Tic Tac Toe Board Array, it will check for the following patterns to determine
|            if a player has won the game.
|            1. If any row has 3 of the same pattern
|            2. If any column has 3 of the same pattern
|            3. If any diagonal direction has 3 of the same pattern
|            If any of the conditions above is fulfilled, the function would return -1 to indicate that the PLAYER has won
|            or it would return 1 if the COMPUTER has won.
|
|  Returns:  -1 -- If any of the conditions listed above is fulfilled with the Player's Pattern "X" to indicate that
|                  the Player has won
|             1 -- If any of the condition listed above is fulfilled with the Computer's Pattern "O" to indicate that
|                  the Computer has won
*-------------------------------------------------------------------*/

int checkWinner()
{
    /* 
    Checks every row to see if there is a combination whereby a row has the same piece, either 3 "X" in 
    a row or 3 "O" in a row.
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
    Checks every column to see if there is a combination whereby a column has the same piece, either 3 "X" in 
    a column or 3 "O" in a column.
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
    Checks left and right diagonally to see if there is a combination whereby the left or right diagonal has the same piece, either 3 "X" or 3 "O".
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