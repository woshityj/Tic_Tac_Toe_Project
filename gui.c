#include "global.h"
#include "tic_tac_toe.h"
#include "gui.h"
#include "minimax.h"

// Function Protoypes
void setAIdifficulty();
void initializeGUI();
void resetBoard();
void resetScore();
void resetGame();
void disableButtons();
void destroy(GtkWidget *widget, gpointer data);
void changeGamemode(GtkWidget *widget, gpointer data);
void announceWinner(int winner, int draw);
/* Creation of GTKWidgets for Graphical User Interface */
GtkWidget       *window;

/* Navigation Bar GTKWidgets */
GtkWidget       *player_vs_player;
GtkWidget       *player_vs_computer_easy;
GtkWidget       *player_vs_computer_medium;
GtkWidget       *player_vs_computer_hard;
GtkWidget       *quit;

/* Game Display */
GtkWidget       *stackfixed1;
GtkWidget       *announce;
GtkWidget       *player1;
GtkWidget       *player2;
GtkWidget       *score1;
GtkWidget       *score2;
GtkWidget       *resetbutton;
GtkWidget       *button1;
GtkWidget       *button2;
GtkWidget       *button3;
GtkWidget       *button4;
GtkWidget       *button5;
GtkWidget       *button6;
GtkWidget       *button7;
GtkWidget       *button8;
GtkWidget       *button9;
GtkBuilder      *builder;

char board[3][3];

// Main Functions
void destroy(GtkWidget *widget, gpointer data)
{
    gtk_window_close(data);
}

void initializeGUI()
{
    builder = gtk_builder_new_from_file("gui.glade");

    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    player_vs_player = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_player"));
    g_signal_connect(player_vs_player, "clicked", G_CALLBACK(changeGamemode), "0");
    player_vs_computer_easy = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_computer_easy"));
    g_signal_connect(player_vs_computer_easy, "clicked", G_CALLBACK(changeGamemode), "1");
    player_vs_computer_medium = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_computer_medium"));
    g_signal_connect(player_vs_computer_medium, "clicked", G_CALLBACK(changeGamemode), "2");
    player_vs_computer_hard = GTK_WIDGET(gtk_builder_get_object(builder, "player_vs_computer_hard"));
    g_signal_connect(player_vs_computer_hard, "clicked", G_CALLBACK(changeGamemode), "3");
    quit = GTK_WIDGET(gtk_builder_get_object(builder, "quit"));
    g_signal_connect(quit, "clicked", G_CALLBACK(destroy), window);
    
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    g_signal_connect(button1, "clicked", G_CALLBACK(playerMove), &board[0][0]);
    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));
    g_signal_connect(button2, "clicked", G_CALLBACK(playerMove), &board[0][1]);
    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3"));
    g_signal_connect(button3, "clicked", G_CALLBACK(playerMove), &board[0][2]);
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4"));
    g_signal_connect(button4, "clicked", G_CALLBACK(playerMove), &board[1][0]);
    button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5"));
    g_signal_connect(button5, "clicked", G_CALLBACK(playerMove), &board[1][1]);
    button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6"));
    g_signal_connect(button6, "clicked", G_CALLBACK(playerMove), &board[1][2]);
    button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7"));
    g_signal_connect(button7, "clicked", G_CALLBACK(playerMove), &board[2][0]);
    button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
    g_signal_connect(button8, "clicked", G_CALLBACK(playerMove), &board[2][1]);
    button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
    g_signal_connect(button9, "clicked", G_CALLBACK(playerMove), &board[2][2]);

    resetbutton = GTK_WIDGET(gtk_builder_get_object(builder, "resetbutton"));
    g_signal_connect(resetbutton, "clicked", G_CALLBACK(resetBoard), NULL);

    announce = GTK_WIDGET(gtk_builder_get_object(builder, "announce"));

    player1 = GTK_WIDGET(gtk_builder_get_object(builder, "player1"));
    player2 = GTK_WIDGET(gtk_builder_get_object(builder, "player2"));

    score1 = GTK_WIDGET(gtk_builder_get_object(builder, "score1"));
    score2 = GTK_WIDGET(gtk_builder_get_object(builder, "score2"));

    gtk_widget_show(window);

    gtk_main();
}

void announceWinner(int winner, int draw)
{
    if (winner == -1)
    {
        gtk_label_set_label(GTK_LABEL(announce), "Player 1 has won!");
        player_1_score = player_1_score + 1;
        gchar *display;
        display = g_strdup_printf("%d", player_1_score);
        gtk_label_set_label(GTK_LABEL(score1), display);
        g_free(display);
        disableButtons();
    }
    else if (winner == 1)
    {
        gtk_label_set_label(GTK_LABEL(announce), "Player 2 has won!");
        player_2_score = player_2_score + 1;
        gchar *display;
        display = g_strdup_printf("%d", player_2_score);
        gtk_label_set_label(GTK_LABEL(score2), display);
        g_free(display);
        disableButtons();
    }
    else if (draw == 1 && winner == 0)
    {
        gtk_label_set_label(GTK_LABEL(announce), "It's a Draw!");
        disableButtons();
    }
}

void resetBoard()
{
    memset(board, 0, sizeof(board));
    turncounter = 0;

    gtk_label_set_label(GTK_LABEL(announce), " ");

    gtk_button_set_label(GTK_BUTTON(button1), " ");
    gtk_button_set_label(GTK_BUTTON(button2), " ");
    gtk_button_set_label(GTK_BUTTON(button3), " ");
    gtk_button_set_label(GTK_BUTTON(button4), " ");
    gtk_button_set_label(GTK_BUTTON(button5), " ");
    gtk_button_set_label(GTK_BUTTON(button6), " ");
    gtk_button_set_label(GTK_BUTTON(button7), " ");
    gtk_button_set_label(GTK_BUTTON(button8), " ");
    gtk_button_set_label(GTK_BUTTON(button9), " ");

    gtk_widget_set_sensitive (button1, TRUE);
    gtk_widget_set_sensitive (button2, TRUE);
    gtk_widget_set_sensitive (button3, TRUE);
    gtk_widget_set_sensitive (button4, TRUE);
    gtk_widget_set_sensitive (button5, TRUE);
    gtk_widget_set_sensitive (button6, TRUE);
    gtk_widget_set_sensitive (button7, TRUE);
    gtk_widget_set_sensitive (button8, TRUE);
    gtk_widget_set_sensitive (button9, TRUE);
}

void resetScore()
{
    gtk_label_set_label(GTK_LABEL(score1), "0");
    gtk_label_set_label(GTK_LABEL(score2), "0");
}

void resetGame()
{
    resetBoard();
    resetScore();
}

void disableButtons()
{
    gtk_widget_set_sensitive (button1, FALSE);
    gtk_widget_set_sensitive (button2, FALSE);
    gtk_widget_set_sensitive (button3, FALSE);
    gtk_widget_set_sensitive (button4, FALSE);
    gtk_widget_set_sensitive (button5, FALSE);
    gtk_widget_set_sensitive (button6, FALSE);
    gtk_widget_set_sensitive (button7, FALSE);
    gtk_widget_set_sensitive (button8, FALSE);
    gtk_widget_set_sensitive (button9, FALSE);
}

void changeGamemode(GtkWidget *widget, gpointer data)
{
    char* ptr_gamemode = data;

    if (*ptr_gamemode == '0')
    {
        gamemode = 0;
        resetBoard();
    }
    else if (*ptr_gamemode == '1')
    {
        gamemode = 1;
        setAIDifficulty();
        gtk_label_set_label(GTK_LABEL(player2), "Computer (Easy)");
        resetBoard();
    }
    else if (*ptr_gamemode == '2')
    {
        gamemode = 2;
        setAIDifficulty();
        gtk_label_set_label(GTK_LABEL(player2), "Computer (Medium)");
        resetBoard();
    }
    else if (*ptr_gamemode == '3')
    {
        gamemode = 3;
        setAIDifficulty();
        gtk_label_set_label(GTK_LABEL(player2), "Computer (Hard)");
        resetBoard();
    }
}