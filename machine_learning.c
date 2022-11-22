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
int ml_algorithm();
void findBestMoveML();
int checkWinner();

/*------------------------------------------------- create_model -----
|  Function create_model
|
|  Purpose:  To create a Machine Learning model based on linear regression through training and then
|            testing the model against the testing data and saving the weights afterwards.
|
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- load_data -----
|  Function load_data
|
|  Purpose:  To open the dataset file called "tic-tac-toe.data" and read the data and load it
|            into a 2-dimensional array.
|
|
*-------------------------------------------------------------------*/
void load_data()
{
    /* fptr is a pointer to the file "tic-tac-toe.data" */
    FILE *fptr = fopen("tic-tac-toe.data", "r");

    char line[MAX_LINE_LENGTH];

    int row = 0, col = 0, player = -1, computer = 1, blank = 0;
    /* Check is the file has been succesfully opened, otherwise stop the program from carrying on */
    if (fptr  == NULL)
    {
        printf("Error opening file!");
        exit(1);
    }

    /* Loops through the entire file and loads the data into the array line by line */
    while(fgets(line, MAX_LINE_LENGTH, fptr))
    {
        char *record;
        /* Splits the line based on "," and stores it into record pointer */
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
            /* 
               As positive in this case is positive for the player, we want the model to treat this as a negative value
               therefore we assign positive as "-1" and "1" for negative
             */
            else if (strcmp(record,"positive") == 0)
            {
                ml_board[row][col++] = -1; 
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

/*------------------------------------------------- split_data -----
|  Function split_data
|
|  Purpose:  Splits the given dataset that is already loaded into the 2D array into
|            training and testing dataset.
|            We split the training and testing in a ratio of 80:20 as given in the
|            project requirements.
|
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- shuffle ----------
|  Function shuffle
|
|  Purpose:  As the dataset is arranged in order for postitive to negative,
|            we will have to shuffle the dataset so that the model does not learn patterns
|            specific only to the positives.
|
|
|  Parameters:
|      length -- Passes the length of the entire dataset that we are required to shuffle
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- train_data ----------
|  Function train_data
|
|  Purpose:  Training is done per row and this function trains the model and outputs an
|            estimated y which will then be checked against the actual output.
|            After doing so, we write this error out to file called "training_accruracy.dat"
|            for plotting.
|
|  Parameters:
|      row -- Passes the current row that will be used for training
|
*-------------------------------------------------------------------*/
void train_data(int row)
{
    float y = training[row][9];
    float yest = 0;

    /* Formula to calculate estimated output based on the current state of the board */
    for (int i = 0; i < 9; i++)
    {
        yest += weights[i] * training[row][i];
    }
    
    /* Based on the estimated output, we convert this output into a stable number */
    if (yest > 0)
    {
        yest = 1;
    }
    else
    {
        yest = -1;
    }

    /* Calculating the error between the actual output and the estimated output */
    float errory = y - yest;
    
    /* Saving the error of each square so that we are able to update the weights afterwards */
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
    
    /* File process to save the error of each row into a file for further plotting */
    FILE *f_ptr = fopen("training_accuracy.dat","a");
    int written = fprintf(f_ptr, "%d\t%f\n",row, errory);
    if (written == 0)
    {
        printf("Error writing to file.");
    }
    fclose(f_ptr);
}

/*------------------------------------------------- test_data ----------
|  Function test_data
|
|  Purpose:  After training is done, we will need to run the model through testing
|            to see if the model has been overfitted to the training data
|
|  Parameters:
|      row -- Passes the current row that will be used for testing
|
*-------------------------------------------------------------------*/
void test_data(int row)
{
    float y = testing[row][9];
    float yest = 0;

    /* Formula to calculate estimated output based on the current state of the board */
    for (int i = 0; i < 9; i++)
    {
        yest += weights[i] * testing[row][i];
    }
    
    /* Based on the estimated output, we convert this output into a stable number */
    if (yest > 0)
    {
        yest = 1;
    }
    else
    {
        yest = -1;
    }

    float errory = y - yest;
    /* 
       As we do not need to update the weights at this stage, we only need to know the total error between the actual y and
       estimated y so that we can calculate the MMSE.
    */
    testing_error_total += (errory*errory);
}

/*------------------------------------------------- updateWeights ----
|  Function updateWeights
|
|  Purpose:  After one iteration in the training phase, we will need to update the weights.
|            The weights are updated following the formula for wi = wi + (learing rate * errorxi).
|
|  Parameters:
|      row -- Passes the current row that will be used for training
|
*-------------------------------------------------------------------*/
void updateWeights(int row)
{
    printf("At row %d, error is %f\n",row+1,error[9]);
    for (int i = 0; i < 9; i++)
    {
        weights[i] += (learning_rate*error[i]);
    }
}

/*------------------------------------------------- save_weights ----
|  Function save_weights
|
|  Purpose:  After the training and testing phase, we are required to save the weights for future use.
|            The weights that are stored in the array will be written to a file called "weights.txt",
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- load_weights ----
|  Function load_weights
|
|  Purpose:  This function is used for users who want to skip the training and testing phase and just
|            load the weights from a previously used model.
|            This function opens the same file called "weights.txt" to load the weights into the
|            global array weights.
|
*-------------------------------------------------------------------*/
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

/*------------------------------------------------- ml_algorithm -----
|  Function ml_algorithm
|
|  Purpose:  As the board we are currently using is a 2-dimensional array, we need to load the data into a one-dimensional
|            array which our model is familiar with.
|            After doing so, we will calculate the move value of the current move and return that value.
|
|  Returns:  move_val -- the current estimated output of the model, which tells the computer whether the move is good or bad
|                     
*-------------------------------------------------------------------*/
int ml_algorithm()
{
    int move_val = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (strlen(&board[i][j]) == 0)
            {
                curr_board[(i*3)+j]=0;
            }
            else if (strcmp(&board[i][j], "O") == 0)
            {
                curr_board[(i*3)+j]=1;
            }
            else if (strcmp(&board[i][j], "X") == 0)
            {
                curr_board[(i*3)+j]=-1;
            }
        }
    }

    for (int i = 0; i < 9; i++)
    {
        move_val += weights[i] * curr_board[i];
    }

    return move_val;
}

/*------------------------------------------------- findBestMoveML -----
|  Function findBestMoveML
|
|  Purpose:  This function will evaluate all the available moves using the Machine Learning Algorithm and 
|            returns the best move that the COMPUTER can make to the Global Best Move Array in the form of
|            the row and column.
|
*-------------------------------------------------------------------*/
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