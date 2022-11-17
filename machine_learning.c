#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1000
#define MAX_SIZE 958
#define TRAINING_SIZE 575
#define TESTING_SIZE 383

int board[MAX_SIZE][10];
int training[TRAINING_SIZE][10];
int testing[TESTING_SIZE][10];
float weights[9] = {0,0,0,0,0,0,0,0,0};
float error[10], training_error[TRAINING_SIZE];
float learning_rate = 0.5,training_error_total = 0,testing_error_total = 0;

// Function prototypes
void load_data();
void shuffle(int length);
void split_data();
void train_data(int row);
void updateWeights(int row);
void test_data(int row);
void save_weights();
void plot_data();

int main(void)
{
    load_data();    //loads data into board array
    shuffle(MAX_SIZE); //shuffles the data into random order
    split_data(); //splits the data into training and testing data
    remove("training_accuracy.dat");
    for (int i = 0; i < TRAINING_SIZE; i++)
    {
        train_data(i);
        updateWeights(i);
    }
    training_error_total = training_error_total/TRAINING_SIZE;
    printf("The accuracy for the training dataset is %f\n",training_error_total);
    for (int j = 0; j < TESTING_SIZE; j++)
    {
        test_data(j);
    }
    testing_error_total = testing_error_total/TRAINING_SIZE;
    printf("The accuracy for the testing dataset is %f",testing_error_total);
    //save_weights();
    return 0;
}

void load_data()
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
    float y = training[row][9]; 
    float yest = 0;
    for (int i = 0; i < 9; i++)
    {
        yest += weights[i] * training[row][i];
    }

    float errory = y - yest;
    
    for (int j = 0; j < 10; j++)
    {
        if(j != 9)
        {
            float x = training[row][j];
            error[j] = ((errory*errory)*x)/TRAINING_SIZE;
        }
        else
        {
            error[j] = (errory*errory)/TRAINING_SIZE;
            FILE *f_ptr = fopen("training_accuracy.dat","a");
            int written = fprintf(f_ptr, "%d\t%f\n",row, error[j]);
            if (written == 0)
            {
                printf("Error writing to file.");
            }
            fclose(f_ptr);
            training_error_total += (errory*errory);
        }
    }
}

void test_data(int row)
{
    float y = testing[row][9];
    float yest = 0;
    for (int i = 0; i < 9; i++)
    {
        yest += weights[i] * testing[row][i];
    }
    float errory = y - yest;
    testing_error_total += (errory*errory);
}

void updateWeights(int row)
{
    printf("At row %d, error is %f\n",row+1,error[9]);
    for (int i = 0; i < 9; i++)
    {
        weights[i] += (learning_rate*error[i]);
    }
}

void save_weights()
{
    FILE *f_ptr = fopen("weights.txt","w");
    for (unsigned i = 0; i < 9; i++)
    {
        int written = fprintf(f_ptr, "Weight %d: %f\n", i+1, weights[i]);
        if (written == 0)
        {
            printf("Error writing to file.");
        }
    }
    fclose(f_ptr);
}