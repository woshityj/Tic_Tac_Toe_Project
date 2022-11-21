#include "global.h"
#include "tic_tac_toe.h"

/* Machine Learning Variables*/
#define MAX_LINE_LENGTH 1000
#define MAX_SIZE 958
#define TRAINING_SIZE 766
#define TESTING_SIZE 192

// Global Variables for Machine Learning, not to be accessed by other files
int ml_board[MAX_SIZE][10];
int curr_board[9];
float weights[9] = {0,0,0,0,0,0,0,0,0};
int training[TRAINING_SIZE][10];
int testing[TESTING_SIZE][10];
float error[10], training_error[TRAINING_SIZE];
float learning_rate = 0.5,training_error_total = 0,testing_error_total = 0;

// Function prototypes
void create_model();
void load_data();
void shuffle(int length);
void split_data();
void train_data(int row);
void updateWeights(int row);
void test_data(int row);
void save_weights();
void load_weights();
int evaluateML(int depth);
int ml_algorithm();
void findBestMoveML();
int checkWinner();

void create_model()
{
    load_data();    //loads data into ml_board array
    shuffle(MAX_SIZE); //shuffles the data into random order
    split_data(); //splits the data into training and testing data
    remove("training_accuracy.dat");
    for (int i = 0; i < TRAINING_SIZE; i++)
    {
        train_data(i);
        updateWeights(i);
    }
    float training_MMSE = training_error_total/TRAINING_SIZE;
    printf("The error for the training dataset is %f\n",training_MMSE);
    for (int i = 0; i < 9; i++)
    {
        printf("Weight %d is %f\n",i,weights[i]);
    }
    for (int j = 0; j < TESTING_SIZE; j++)
    {
        test_data(j);
    }
    float testing_MMSE = testing_error_total/TESTING_SIZE;
    printf("\nThe error for the testing dataset is %f",testing_MMSE);
    save_weights();
}

void load_data()
{
    FILE *fptr = fopen("tic-tac-toe.data", "r");
    char line[MAX_LINE_LENGTH];
    int row = 0, col = 0, player = -1, computer = 1, blank = 0;
    if (fptr  == NULL)
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
                ml_board[row][col++] = player;
            }
            else if(strcmp(record,"o") == 0)
            {
                ml_board[row][col++] = computer;
            }
            else if(strcmp(record,"b") == 0)
            {
                ml_board[row][col++] = blank;
            }
            else if (strcmp(record,"positive") == 0)
            {
                ml_board[row][col++] = -1; //positive for player means negative for computer
            }
            else if (strcmp(record,"negative") == 0)
            {
                ml_board[row][col++] = 1;
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
                training[k1][j] = ml_board[i][j];
            }
            k1++;
        }
        else
        {
            for (int j = 0; j < 10; j++)
            {
                testing[k2][j] = ml_board[i][j];
            }
            k2++;
        }
    }
}

void shuffle(int length)
{
    for(int i = 0; i < length; i++)
    {
        int swap_index = rand() % length;
        for(int j = 0; j < 10; j++)
        {
            int temp = ml_board[i][j];
            ml_board[i][j] = ml_board[swap_index][j];
            ml_board[swap_index][j] = temp;
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
    
    if (yest > 0)
    {
        yest = 1;
    }
    else
    {
        yest = -1;
    }

    float errory = y - yest;
    
    for (int j = 0; j < 10; j++)
    {
        if(j != 9)
        {
            int x = training[row][j];
            error[j] = (errory*errory*x);
        }
        else
        {
            error[j] = errory;
            training_error_total += (errory*errory);
        }
    }
    FILE *f_ptr = fopen("training_accuracy.dat","a");
    int written = fprintf(f_ptr, "%d\t%f\n",row, errory);
    if (written == 0)
    {
        printf("Error writing to file.");
    }
    fclose(f_ptr);
}

void test_data(int row)
{
    float y = testing[row][9];
    float yest = 0;
    for (int i = 0; i < 9; i++)
    {
        yest += weights[i] * testing[row][i];
    }
    
    if (yest > 0)
    {
        yest = 1;
    }
    else
    {
        yest = -1;
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
    FILE *f_ptr = fopen("weights.txt","w+");
    for (unsigned i = 0; i < 9; i++)
    {
        int written = fprintf(f_ptr, "%f,", weights[i]);
        if (written == 0)
        {
            printf("Error writing to file.");
        }
    }
    fclose(f_ptr);
}

void load_weights()
{
    FILE *f_ptr = fopen("weights.txt", "r");
    char line[MAX_LINE_LENGTH];
    if (f_ptr  == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    while(fgets(line, MAX_LINE_LENGTH, f_ptr))
    {
        char *record;
        int i = 0;
        record = strtok(line,",");
        while(record != NULL)
        {
            if (atoi(record) != i)
            {
                weights[i] = atof(record);
                printf("\n%f", weights[i]);
                record = strtok(NULL,",");
            }
        }
        i += 1;
    }
    fclose(f_ptr);
}

int evaluateML(int depth)
{
    int check_winner;
    int score;
    check_winner = checkWinner();
    if (check_winner == -1)
    {
        score = -10;
        return score;
    }
    else if (check_winner == 1)
    {
        score = 10;
        return score;
    }
    else
    {
        return 0;
    }
}

int ml_algorithm()
{
    int move_val = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (strlen(&board[i][j]) == 0)
            {
                curr_board[(i*3)+j]=board[i][j];
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        move_val += weights[i] * curr_board[i];
    }

    return move_val;
}

void findBestMoveML()
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

                int moveVal = ml_algorithm();
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