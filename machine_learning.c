#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000
#define ARRAY_SIZE 958

int board[ARRAY_SIZE][10];
float weights[10] = {0,0,0,0,0,0,0,0,0,0};
float learning_rate = 0.0042069;

void shuffle(int length);

int main(void)
{
    FILE *fptr;
    char line[MAX_LINE_LENGTH];
    int row = 0, col = 0, player = -1, computer = 1, blank = 0;

    if ((fptr = fopen("tic-tac-toe.data", "r")) == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    while(fgets(line, MAX_LINE_LENGTH, fptr))
    {
        char *record;
        record = strtok(line,",");
        while(record != NULL)
        {
            record[strcspn(record, "\n")] = '\0';
            if(strcmp(record,"x") == 0)
            {
                board[row][col++] = player;
            }
            else if(strcmp(record,"o") == 0)
            {
                board[row][col++] = computer;
            }
            else if(strcmp(record,"b") == 0)
            {
                board[row][col++] = blank;
            }
            else if (strcmp(record,"positive") == 0)
            {
                board[row][col++] = 10;
            }
            else if (strcmp(record,"negative") == 0)
            {
                board[row][col++] = -10;
            }
            record = strtok(NULL,",");
        }
        ++row;
        col = 0;
    }
    fclose(fptr);
    shuffle(ARRAY_SIZE);
    
    return 0;
}

void shuffle(int length)
{
    srand(time(NULL));

    for(int i = 0; i < length; i++)
    {
        int swap_index = rand() % length;
        for(int j = 0; j < 10; j++)
        {
            int temp = board[i][j];
            board[i][j] = board[swap_index][j];
            board[swap_index][j] = temp;
        }
    }
}

void regression(int row)
{
    float yest = 0;
    for (int i = 0; i < 10; i++)
    {
        yest += weights[i] * board[row][i];
    }
}

void updateWeights(int row)
{
    float y, yest;
    int error = (1/ARRAY_SIZE)*(y-yest);
    for (int i = 0; i < 10; i++)
    {
        weights[i] = weights[i] + (learning_rate*error*board[row][i]);
    }
}