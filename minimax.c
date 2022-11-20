#include "global.h"
#include "tic_tac_toe.h"

// Function Protoypes
int evaluate();
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

/*------------------------------------------------- minimax -----
|  Function minimax
|
|  Purpose:  Uses a Backtracking Algorithm to consider all the possible ways the game can go 
|            and find the most optimal move that results in a win for the COMPUTER,
|            the maximiser (-1000) will try to get the best score possible and the minimiser (1000) will try to get
|            the worse score possible. 
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

/*------------------------------------------------- minimax -----
|  Function minimax
|
|  Purpose:  Uses a Backtracking Algorithm to consider all the possible ways the game can go 
|            and find the most optimal move that results in a win for the COMPUTER,
|            the maximiser (-1000) will try to get the best score possible and the minimiser (1000) will try to get
|            the worse score possible. 
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

/*------------------------------------------------- getAIDecision -----
|  Function getAIDecision
|
|  Purpose:  Uses a Backtracking Algorithm to consider all the possible ways the game can go 
|            and find the most optimal move that results in a win for the COMPUTER,
|            the maximiser (-1000) will try to get the best score possible and the minimiser (1000) will try to get
|            the worse score possible.
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