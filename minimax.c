#include "global.h"
#include "tic_tac_toe.h"

// Function Protoypes
int evaluate(int depth);
int minimax(int depth, int isMax, int alpha, int beta, int *ptr_counter);
void findBestMove();
int max(int num1, int num2);
int min(int num1, int num2);
void setAIDifficulty();
int getAIDecision();
int checkWinner();
int checkFreeSpaces();

/*------------------------------------------------- evaluate -----
|  Function evaluate
|
|  Purpose:  Based on the placement of the pieces on the Temporary Board by the MiniMax Algorithm,
|            this function would return a value based on whether the placement of the pieces via the MiniMax Function results in a win
|            for the COMPUTER or a loss for the COMPUTER
|
|  Returns:  -10 -- If the placement of the pieces results in a loss for the COMPUTER, the value -10 will be returned
|            +10 -- If the placement of the pieces results in a win for the COMPUTER, the value +10 will be returned
|              0 -- If the placement of the piece results in a draw, the value 0 will be returned
*-------------------------------------------------------------------*/
int evaluate(int depth)
{
    int check_winner;
    int score;
    check_winner = checkWinner();
    if (check_winner == -1)
    {
        score = -10 + depth;
        return score;
    }
    else if (check_winner == 1)
    {
        score = 10 - depth;
        return score;
    }
    else
    {
        return 0;
    }
}

/*------------------------------------------------- minimax -----
|  Function minimax
|
|  Purpose:  Uses a Backtracking Algorithm to consider all the possible ways the game can go 
|            and find the most optimal move that results in a win for the COMPUTER,
|            the maximiser (-1000) will try to get the best score possible and the minimiser (1000) will try to get
|            the worse score possible.
|
|  Parameters:
|      depth -- Determines the level that the MiniMax Algorithm is currently on, where 0 signifies that its currently
|               on the highest level (0).
|      isMax -- A boolean to check if we are looking for the maximiser score or the minimiser score
|      alpha -- Contains the best value that the maximiser currently can guarantee at that level or above
|      beta  -- Contains the best value that the minimiser currently can guarantee at that level or below
|
|  Returns:  score -- If 10 is returned, it means that the position results in a win for the COMPUTER (maximiser),
|                     but if -10 is returned it means the position results in a loss for the COMPUTER (minimiser).
|            best  -- Returns the maximiser or minimisers score.
*-------------------------------------------------------------------*/
int minimax(int depth, int isMax, int alpha, int beta, int *ptr_counter)
{
    int score;
    int spaces_left;
    int check_winner;

    score = evaluate(depth);

    check_winner = checkWinner();
    
    if (check_winner == - 1)
    {
        return score;
    }

    if (check_winner == 1)
    {
        return score;
    }

    spaces_left = checkFreeSpaces();
    if (spaces_left == 0)
    {
        return 0;
    }

    if (imperfect)
    {
        if(depth == 3)
        {
            return score;
        }
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

                    *ptr_counter = *ptr_counter + 1;

                    best = max(best, minimax(depth + 1, !isMax, alpha, beta, ptr_counter));

                    alpha = max(alpha, best);

                    board[i][j] = 0;
                    
                    if (beta <= alpha)
                    {
                        break;
                    }
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

                    *ptr_counter = *ptr_counter + 1;

                    best = min(best, minimax(depth + 1, !isMax, alpha, beta, ptr_counter));

                    beta = min(beta, best);

                    board[i][j] = 0;

                    if (beta <= alpha)
                    {
                        break;
                    }
                }
            }
        }
        return best;
    }
}

/*------------------------------------------------- findBestMove -----
|  Function findBestMove
|
|  Purpose:  This function will evaluate all the available moves using the MiniMax Algorithm and 
|            returns the best move that the COMPUTER can make to the Global Best Move Array in the form of
|            the row and column.
|
*-------------------------------------------------------------------*/
void findBestMove()
{
    int bestVal = -1000;
    int counter = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (strlen(&board[i][j]) == 0)
            {
                board[i][j] = COMPUTER;

                int moveVal = minimax(0, 0, -1000, 1000, &counter);
                printf("\n%d", moveVal);

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
    printf("The amount of iterations are: %d\n", counter);
}

/*------------------------------------------------- max -----
|  Function max
|
|  Purpose:  This function will do a comparison between 2 numbers and return the higher number
|
|  Parameters:
|      num1  -- The 1st number to be used to be compared with the 2nd number
|      num2  -- The 2nd number to be compared with the 1st number
|
|  Returns:  num1 -- If the 1st number is greater than the 2nd number, the 1st number is returned
|            num2 -- If the 2nd number is greater than the 1st number, the 2nd number is returned
|
*-------------------------------------------------------------------*/
int max(int num1, int num2)
{
    if (num1 > num2)
    {
        return num1;
    }
    return num2;
}

/*------------------------------------------------- min -----
|  Function min
|
|  Purpose:  This function will do a comparison between 2 numbers and return the lower number
|
|  Parameters:
|      num1  -- The 1st number to be used to be compared with the 2nd number
|      num2  -- The 2nd number to be compared with the 1st number
|
|  Returns:  num1 -- If the 1st number is smaller than the 2nd number, the 1st number is returned
|            num2 -- If the 2nd number is smaller than the 1st number, the 2nd number is returned
|
*-------------------------------------------------------------------*/
int min(int num1, int num2)
{
    if (num1 < num2)
    {
        return num1;
    }
    return num2;
}

/*------------------------------------------------- setAIDifficulty -----
|  Function setAIDifficulty
|
|  Purpose:   This function would determine the chances of when the most optimal position (MiniMax Algorithm) is picked and save it 
|             to a global variable known as aiPercentage based on the Gamemode the user has picked.
|             For instance if the player has chosen a Gamemode of 1 (Easy), the AI Percentage would be 0, which means that 
|             the chances of the MiniMax Algorithm is picked is 0. If the Gammode the player chose is 2 (Medium), the chances
|             of the most optimal position (MiniMax Algorithm) being chosen is 75%.
|             1. Gamemode of 1 (Easy) -- Chances of MiniMax Algorithm being picked is 0%
|             2. Gamemode of 2 (Medium) -- Chances of MiniMax Algorithm being picked is 75%
|             3. Gamemode of 3 (Hard) -- Chances of MiniMax Algorithm being picked is 100%
|
*-------------------------------------------------------------------*/
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
    else if (gamemode == 4)
    {
        aiPercentage = 0.0;
    }
    return;
}

/*------------------------------------------------- getAIDecision -----
|  Function getAIDecision
|
|  Purpose:  Generates a random value between 0.0 and 1.0 to determine if the COMPUTER should use the 
|            MiniMax Algorithm should or the COMPUTER should use a random position on the Tic Tac Toe 
|            Board.
|
|  Returns:  1 -- Indicates that the random value generated is less than the AI Percentage variable defined 
|                 from the setAIDifficulty() function and the AI will use the MiniMax Algorithm to pick the most optimal
|                 position on the board
|            0 -- Indicates that the random value generated is more than the AI Percentage variable defined
|                 from the SetAIDifficulty() function and the AI pick a random position on the Tic Tac Toe Board
*-------------------------------------------------------------------*/
int getAIDecision()
{
    /* 
       By making use of the rand() function, a random value between 0.0 to 1.0 will be generated
     */
    float value;
    value = (float) rand() / RAND_MAX;
    printf("\nRandomised Value is:");
    printf("%f", value);

    /*
       If the random value is less than the value definede in the aiPercentage variable, the 
       MiniMax Algorithm will be used to pick the most optimal position on the board.
     */
    if (value <= aiPercentage)
    {
        printf("\n Best Move");
        return 1;
    }

    /*
       If the random value is more than the value definede in the aiPercentage variable, a
       random position on the board will be picked.
     */
    printf("\n Not Best Move");
    return 0;
}