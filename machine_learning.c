#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000
#define MAX_SIZE 958
#define TRAINING_SIZE 766
#define TESTING_SIZE 192

int board[MAX_SIZE][10];
int training[TRAINING_SIZE][10];
int testing[TESTING_SIZE][10];
float weights[10] = {0,0,0,0,0,0,0,0,0,0};
float error[10];
float learning_rate = 0.0042069;
float y, yest;

// Function prototypes
void load_data();
void shuffle(int length);
void train_data();
void split_data();

int main(void)
{
    load_data();    //loads data into board array
    shuffle(MAX_SIZE);
    split_data();
    for (int i = 0; i < TRAINING_SIZE; i++)
    {
        train_data(i);
    }
    
/*     for(int i = 0; i < TRAINING_SIZE; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            printf("The row %d contains: %d\n",i ,training[i][j]);
        }
    } */
    return 0;
}

void load_data()
{
    FILE *fptr;
    char line[MAX_LINE_LENGTH];
    int row = 0, col = 0, player = -1, computer = 1, blank = 0;;
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
}

void split_data()
{
    int k1 = 0, k2 = 0;
    for(int i = 0; i < MAX_SIZE; i++)
    {
        if(i < TRAINING_SIZE)
        {
            for(int j = 0; j < 10; j++)
            {
                training[k1][j] = board[i][j];
            }
            k1++;
        }
        else
        {
            for (int j = 0; j < 10; j++)
            {
                testing[k2][j] = board[i][j];
            }
            k2++;
        }
    }
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

void train_data(int row)
{
    y = training[row][9];
    for (int i = 0; i < 9; i++)
    {
        yest += weights[i] * training[row][i];
    }

    for (int j = 0; j < 10; j++)
    {
        if(j != 9)
        {
            error[j] = (1/MAX_SIZE)*((y-yest)*(y-yest))*training[row][j];
        }
        else
        {
            error[j] = (1/MAX_SIZE)*((y-yest)*(y-yest));
        }
    }
    updateWeights(row);
}

void updateWeights(int row)
{
    for (int i = 0; i < 10; i++)
    {
        weights[i] = weights[i] + (learning_rate*error[i]*training[row][i]);
    }
}