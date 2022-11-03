#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

GtkWidget       *window, *fixed1, *PVP, *PVC_Hard, *PVC_Easy, *quitbutton;
GtkBuilder      *builder;

static void pvp (GtkWidget *widget, gpointer data){
    // need change gui_v2 into pvp and put .h files and .c files accordingly
    // see https://stackoverflow.com/questions/31519449/c99-call-main-function-from-another-main#
}

static void pvc_hard (GtkWidget *widget, gpointer data){
    // redirect to hard_mode, need put .h files and .c accordingly
    // see https://stackoverflow.com/questions/31519449/c99-call-main-function-from-another-main#
}

static void pvc_easy (GtkWidget *widget, gpointer data){
    // redirect to easy_mode, need put .h files and .c accordingly
    // see https://stackoverflow.com/questions/31519449/c99-call-main-function-from-another-main#
}

static void quit (GtkWidget *widget, gpointer data){
    // on a button click close the application
    // see https://stackoverflow.com/questions/55981279/how-do-i-quit-a-gtk-application-from-a-button-click
}

int main (int argc, char *argv[]){
    gtk_init(&argc, &argv);

    builder = gtk_builder_new_from_file("Main_Menu.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));

    PVP = GTK_WIDGET(gtk_builder_get_object(builder, "PVP")); //Goes to PVP Page
    g_signal_connect (PVP, "clicked", G_CALLBACK (pvp), "");

    PVC_Hard = GTK_WIDGET(gtk_builder_get_object(builder, "PVC_Hard")); // Goes to vs AI Page (Perfect Minimax Algorithm)
    g_signal_connect (PVP, "clicked", G_CALLBACK (pvc_hard), "");

    PVC_Easy = GTK_WIDGET(gtk_builder_get_object(builder, "PVC_Easy")); // Goes to vs AI Page (Imperfect Minimax Algorithm)
    g_signal_connect (PVP, "clicked", G_CALLBACK (pvc_easy), "");

    gtk_widget_show(window);
    
    gtk_main();

    return EXIT_SUCCESS;
}


/* char board[3][3];
const char PLAYER = 'X';
const char COMPUTER = 'O';

void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove();
void computerMove();
char checkWinner();
void printWinner(char);

int main()
{
    char winner = ' ';

    resetBoard();
    
    while(winner == ' ' && checkFreeSpaces() != 0)
    {
        printBoard();

        playerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }

        computerMove();
        winner = checkWinner();
        if (winner != ' ' || checkFreeSpaces() == 0)
        {
            break;
        }
    }

    printBoard();
    printWinner(winner);

    return 0;
}

void resetBoard()
{
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' ';
        }
    }
}

void printBoard()
{
    printf(" %c  | %c   | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n--- | --- | --- \n ");
    printf(" %c | %c   | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n--- | --- | --- \n ");
    printf(" %c | %c   | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n--- | --- | --- \n ");
    printf("\n");
}

int checkFreeSpaces()
{
    int freeSpaces = 9;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

void playerMove()
{
    int x;
    int y;

    do
    {
        printf("Enter row #(1-3): ");
        scanf("%d", &x);
        x--;
        printf("Enter column #(1-3): ");
        scanf("%d", &y);
        y--;

        if (board[x][y] != ' ')
        {
            printf("Invalid move!\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } 
    while (board[x][y] != ' ');
    

    
}

void computerMove()
{
    //Creates a Seed based on current time
    srand(time(0));
    int x;
    int y;

    if (checkFreeSpaces() > 0)
    {
        do
        {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
    else
    {
        printWinner(' ');
    }
}

char checkWinner()
{
    //Check Rows
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2])
        {
            return board[i][0];
        }
    }

    //Check Columns
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i])
        {
            return board[0][i];
        }
    }

    //Check Diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2])
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0])
    {
        return board[0][2];
    }

    return ' ';
}

void printWinner(char winner)
{
    if (winner == PLAYER)
    {
        printf("YOU WIN!");
    }
    else if (winner == COMPUTER)
    {
        printf("YOU LOSE!");
    }
    else
    {
        printf("ITS A TIE!");
    }
} */