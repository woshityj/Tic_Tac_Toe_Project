#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000
#define ARRAY_SIZE 958

int board[ARRAY_SIZE][10];

void shuffle(int array[], int length);

int main(void)
{
    FILE *fptr;
    char line[MAX_LINE_LENGTH];

    if ((fptr = fopen("tic-tac-toe.data", "r")) == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    while(fgets(line, MAX_LINE_LENGTH, fptr))
    {
        int row = 0, col = 0, player = 1, computer = -1, blank = 0;
        char *record;
        record = strtok(line,",");
        while(record != NULL)
        {
            record[strcspn(record, "\n")] = '\0';
            if(strcmp(record,"x") == 0)
            {
                board[row][col++] = 1;
            }
            else if(strcmp(record,"o") == 0)
            {
                board[row][col++] = -1;
            }
            else if(strcmp(record,"b") == 0)
            {
                board[row][col++] = 0;
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
    }
    fclose(fptr);
    shuffle(board,ARRAY_SIZE);
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            
        }
    }
    return 0;
}

void shuffle(int array[], int length)
{
    srand(time(NULL));

    for(int i = 0; i < length; i++)
    {
        int swap_index = rand() % length;
        int temp = array[i];
        array[i] = array[swap_index];
        array[swap_index] = temp;
    }
}