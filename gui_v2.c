// gcc $( pkg-config --cflags gtk+-3.0 ) -o gui_v2 gui_v2.c $( pkg-config --libs gtk+-3.0 )

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glib/gstdio.h>

// Creation of GTKWidgets for Graphical User Interface
GtkWidget       *window;
GtkWidget       *fixed1;
GtkWidget       *button1;
GtkWidget       *button2;
GtkWidget       *button3;
GtkWidget       *button4;
GtkWidget       *button5;
GtkWidget       *button6;
GtkWidget       *button7;
GtkWidget       *button8;
GtkWidget       *button9;
GtkWidget       *resetbutton;
GtkWidget       *player1;
GtkBuilder      *builder;

// Global variables
char board[3][3]; //2D Array for Tic Tac Toe Backend
const char PLAYER = 'X';
const char COMPUTER = 'O';
int turncounter = 0;

static void printBoard()
{
    printf(" %c  | %c   | %c ", board[0][0], board[0][1], board[0][2]);
    printf("\n--- | --- | --- \n ");
    printf(" %c | %c   | %c ", board[1][0], board[1][1], board[1][2]);
    printf("\n--- | --- | --- \n ");
    printf(" %c | %c   | %c ", board[2][0], board[2][1], board[2][2]);
    printf("\n--- | --- | --- \n ");
    printf("\n");
}

static void playerMove (GtkWidget *widget, gpointer data)
{
    int row, column;
    if (strcmp(data, "00") == 0)
    {
        row = 0;
        column = 0;
    }
    else if (strcmp(data, "01") == 0)
    {
        row = 0;
        column = 1;
    }
    else if (strcmp(data, "02") == 0)
    {
        row = 0;
        column = 2;
    }
    else if (strcmp(data, "10") == 0)
    {
        row = 1;
        column = 0;
    }
    else if (strcmp(data, "11") == 0)
    {
        row = 1;
        column = 1;
    }
    else if (strcmp(data, "12") == 0)
    {
        row = 1;
        column = 2;
    }
    else if (strcmp(data, "20") == 0)
    {
        row = 2;
        column = 0;
    }
    else if (strcmp(data, "21") == 0)
    {
        row = 2;
        column = 1;
    }
    else if (strcmp(data, "22") == 0)
    {
        row = 2;
        column = 2;
    }

    /* 
    Checks if the position on the board is taken 
    If the position is occupied, it will output "Invalid Move!" in the terminal
    and return
    */
    if (board[row][column] == 'X' || board[row][column] == 'O')
    {
        printf("Invalid Move!\n");
        return;
    }

    if (turncounter % 2 == 0 || turncounter == 0) 
    {
        board[row][column] = PLAYER;
        gtk_button_set_label(GTK_BUTTON(widget), "X");
    }
    else if (turncounter % 2 == 1)
    {
        board[row][column] = COMPUTER;
        gtk_button_set_label(GTK_BUTTON(widget), "O");
    }
    
    printBoard();
    turncounter += 1;
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

static void resetBoard()
{
    memset(board, 0, sizeof(board));
    gtk_button_set_label(GTK_BUTTON(button1), " ");
    gtk_button_set_label(GTK_BUTTON(button2), " ");
    gtk_button_set_label(GTK_BUTTON(button3), " ");
    gtk_button_set_label(GTK_BUTTON(button4), " ");
    gtk_button_set_label(GTK_BUTTON(button5), " ");
    gtk_button_set_label(GTK_BUTTON(button6), " ");
    gtk_button_set_label(GTK_BUTTON(button7), " ");
    gtk_button_set_label(GTK_BUTTON(button8), " ");
    gtk_button_set_label(GTK_BUTTON(button9), " ");
}

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv); //init Gtk

    builder = gtk_builder_new_from_file("Tic_Tac_Toe_GUI.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    g_signal_connect (button1, "clicked", G_CALLBACK (playerMove), "00");

    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    g_signal_connect (button2, "clicked", G_CALLBACK (playerMove), "01");
    
    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    g_signal_connect (button3, "clicked", G_CALLBACK (playerMove), "02");
    
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
    g_signal_connect (button4, "clicked", G_CALLBACK (playerMove), "10");

    button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect (button5, "clicked", G_CALLBACK (playerMove), "11");

    button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
    g_signal_connect (button6, "clicked", G_CALLBACK (playerMove), "12");

    button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
    g_signal_connect (button7, "clicked", G_CALLBACK (playerMove), "20");

    button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
    g_signal_connect (button8, "clicked", G_CALLBACK (playerMove), "21");

    button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
    g_signal_connect (button9, "clicked", G_CALLBACK (playerMove), "22");

    resetbutton = GTK_WIDGET(gtk_builder_get_object(builder, "resetbutton"));
    g_signal_connect (resetbutton, "clicked", G_CALLBACK (resetBoard), NULL);

    player1 = GTK_WIDGET(gtk_builder_get_object(builder, "player1"));

    gtk_widget_show(window);

    gtk_main();

    return EXIT_SUCCESS;
}