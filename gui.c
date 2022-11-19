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
void hidegrid();
void hidemenu();
void disableButtons();
void destroy(GtkWidget *widget, gpointer data);
void changeGamemode(GtkWidget *widget, gpointer data);
void playerMove(GtkWidget *widget, gpointer data);
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
GtkWidget *window;
GtkWidget *mainMenu;
GtkWidget *player_vs_player;
GtkWidget *player_vs_computer_easy;
GtkWidget *player_vs_computer_medium;
GtkWidget *player_vs_computer_hard;
GtkWidget *quit;
GtkWidget *MainBox;
GtkWidget *tttpage;
GtkWidget *tttgrid;
GtkWidget *button1;
GtkWidget *child1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *button5;
GtkWidget *button6;
GtkWidget *button7;
GtkWidget *button8;
GtkWidget *button9;
GtkWidget *image;
GtkWidget *player1;
GtkWidget *player2;
GtkWidget *score1;
GtkWidget *score2;
GtkWidget *header;
GtkWidget *announce;
GtkWidget *back;
GtkWidget *reset;
GtkWidget *restart;
GtkWidget *optionbox;

char board[3][3];

// Main Functions
void destroy(GtkWidget *widget, gpointer data)
{
    gtk_window_close(data);
}

void initializeGUI()
{
    // gtk_init(&argc,&argv);
  
    //Creating a window and styling of window
    window =gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window),"Tic Tac Toe");
    gtk_window_set_default_size(GTK_WINDOW(window),800,600);
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    //gtk_window_set_decorated(GTK_WINDOW(window),FALSE);
    
    //gtk_widget_show (MainBox);
    //creating a MainBox container
    MainBox = gtk_fixed_new();
    
    gtk_widget_set_name(MainBox,"MainBox");
    
    gtk_container_add (GTK_CONTAINER (window), MainBox);
    
    //creating box container
    mainMenu = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    //tttpage = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    tttpage = gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
    gtk_container_add(GTK_CONTAINER(MainBox),mainMenu);
    
    gtk_container_add(GTK_CONTAINER (MainBox), tttpage);
    gtk_widget_set_name(mainMenu,"mainMenu");
    gtk_widget_set_name(tttpage,"tttpage");
    
   
    
    //Main Menu
    //creating elements in main menu 
    player_vs_player = gtk_button_new_with_label("Player Vs Player");
    player_vs_computer_easy = gtk_button_new_with_label("Player Vs Computer(Easy)");
    player_vs_computer_medium = gtk_button_new_with_label("Player Vs Computer(Medium)");
    player_vs_computer_hard = gtk_button_new_with_label("Player Vs Computer(Hard)");

    gtk_button_set_relief(GTK_BUTTON(player_vs_player), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(player_vs_computer_easy), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(player_vs_computer_medium), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(player_vs_computer_hard), GTK_RELIEF_NONE);


    quit= gtk_button_new_with_label("Quit");
    g_signal_connect(quit,"clicked", G_CALLBACK(gtk_main_quit),NULL);

    gtk_button_set_relief(GTK_BUTTON(quit), GTK_RELIEF_NONE);

    gtk_container_add(GTK_CONTAINER(mainMenu),player_vs_player);
    gtk_widget_set_name(player_vs_player,"player_vs_player");
    gtk_container_add(GTK_CONTAINER(mainMenu),player_vs_computer_easy);
    gtk_widget_set_name(player_vs_computer_easy,"player_vs_computer_easy");
    gtk_container_add(GTK_CONTAINER(mainMenu),player_vs_computer_medium);
    gtk_widget_set_name(player_vs_computer_medium,"player_vs_computer_medium");
    gtk_container_add(GTK_CONTAINER(mainMenu),player_vs_computer_hard);
    gtk_widget_set_name(player_vs_computer_hard,"player_vs_computer_hard");
    gtk_container_add(GTK_CONTAINER(mainMenu),quit);
    gtk_widget_set_name(quit,"quit");
    
    //Creating welcome page
    header = gtk_label_new("TIC TAC TOE");
    gtk_widget_set_name(header,"header");
    gtk_container_add(GTK_CONTAINER(MainBox),header);

    //Creating player 1,2 label
    player1 = gtk_label_new("Player 1");
    player2 = gtk_label_new("Player 2");
    gtk_container_add(GTK_CONTAINER(MainBox),player1);
    gtk_container_add(GTK_CONTAINER(MainBox),player2);
    gtk_widget_set_name(player1,"player1");
    gtk_widget_set_name(player2,"player2");


    //Create scores label
    score1 = gtk_label_new("0");
    score2 = gtk_label_new("0");
    gtk_container_add(GTK_CONTAINER(MainBox),score1);
    gtk_container_add(GTK_CONTAINER(MainBox),score2);
    gtk_widget_set_name(score1,"score1");
    gtk_widget_set_name(score2,"score2");


    //Announce winner label
    announce = gtk_label_new("Winner");
    gtk_container_add(GTK_CONTAINER(MainBox),announce);
    gtk_widget_set_name(announce,"winner");


    optionbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
    gtk_container_add(GTK_CONTAINER(MainBox),optionbox);
    gtk_widget_set_name(optionbox,"optionbox");


    back = gtk_button_new_with_label("Back");
    reset = gtk_button_new_with_label("Restart");
    restart = gtk_button_new_with_label("Reset Score");
    gtk_container_add(GTK_CONTAINER(optionbox),back);
    gtk_container_add(GTK_CONTAINER(optionbox),reset);
    gtk_container_add(GTK_CONTAINER(optionbox),restart);
    gtk_widget_set_name(back,"back");
    gtk_widget_set_name(reset,"reset");
    gtk_widget_set_name(restart,"restart");
    gtk_widget_set_halign(GTK_CONTAINER(optionbox), GTK_ALIGN_CENTER);

    gtk_button_set_relief(GTK_BUTTON(back), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(reset), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(restart), GTK_RELIEF_NONE);

    

    //Tic tac toe page 
    //creating elements in page ttt
    tttgrid = gtk_grid_new();
    gtk_widget_set_name(tttgrid,"tttgrid");
    gtk_container_add(GTK_CONTAINER(tttpage),tttgrid);
    

    button1 = gtk_button_new();
    button2 = gtk_button_new();
    button3 = gtk_button_new();
    button4 = gtk_button_new();
    button5 = gtk_button_new();
    button6 = gtk_button_new();
    button7 = gtk_button_new();
    button8 = gtk_button_new();
    button9 = gtk_button_new();

    gtk_widget_set_name(button1,"button1");
    gtk_widget_set_name(button2,"button2");
    gtk_widget_set_name(button3,"button3");
    gtk_widget_set_name(button4,"button4");
    gtk_widget_set_name(button5,"button5");
    gtk_widget_set_name(button6,"button6");
    gtk_widget_set_name(button7,"button7");
    gtk_widget_set_name(button8,"button8");
    gtk_widget_set_name(button9,"button9");

    gtk_grid_set_row_homogeneous(GTK_GRID(tttgrid),TRUE);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button1),1,0,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button2),2,0,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button3),3,0,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button4),1,1,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button5),2,1,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button6),3,1,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button7),1,2,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button8),2,2,1,1);
    gtk_grid_attach(GTK_GRID(tttgrid),GTK_BUTTON(button9),3,2,1,1);

    gtk_button_set_relief(GTK_BUTTON(button1), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button2), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button3), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button4), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button5), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button6), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button7), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button8), GTK_RELIEF_NONE);
    gtk_button_set_relief(GTK_BUTTON(button9), GTK_RELIEF_NONE);

    GtkCssProvider *cssProvider = gtk_css_provider_new();
    gtk_css_provider_load_from_path(cssProvider, "theme.css", NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),GTK_STYLE_PROVIDER(cssProvider),GTK_STYLE_PROVIDER_PRIORITY_USER);
    
  
    g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
    gtk_widget_show_all(window);

    gtk_widget_hide(tttpage);
    gtk_widget_hide(player1);
    gtk_widget_hide(player2);
    gtk_widget_hide(score1);
    gtk_widget_hide(score2);
    gtk_widget_hide(announce);
    gtk_widget_hide(back);
    gtk_widget_hide(reset);
    gtk_widget_hide(restart);

    
    g_signal_connect(player_vs_player, "clicked", G_CALLBACK(changeGamemode), "0");
    g_signal_connect(player_vs_computer_easy, "clicked", G_CALLBACK(changeGamemode), "1");
    g_signal_connect(player_vs_computer_medium, "clicked", G_CALLBACK(changeGamemode), "2");
    g_signal_connect(player_vs_computer_hard, "clicked", G_CALLBACK(changeGamemode), "3");

    g_signal_connect(button1, "clicked", G_CALLBACK(playerMove), &board[0][0]);
    g_signal_connect(button2, "clicked", G_CALLBACK(playerMove), &board[0][1]);
    g_signal_connect(button3, "clicked", G_CALLBACK(playerMove), &board[0][2]);
    g_signal_connect(button4, "clicked", G_CALLBACK(playerMove), &board[1][0]);
    g_signal_connect(button5, "clicked", G_CALLBACK(playerMove), &board[1][1]);
    g_signal_connect(button6, "clicked", G_CALLBACK(playerMove), &board[1][2]);
    g_signal_connect(button7, "clicked", G_CALLBACK(playerMove), &board[2][0]);
    g_signal_connect(button8, "clicked", G_CALLBACK(playerMove), &board[2][1]);
    g_signal_connect(button9, "clicked", G_CALLBACK(playerMove), &board[2][2]);

    g_signal_connect(back,"clicked", G_CALLBACK(hidegrid),NULL);
    g_signal_connect(reset,"clicked", G_CALLBACK(resetBoard),NULL);
    g_signal_connect(restart,"clicked", G_CALLBACK(resetGame),NULL);
    

    //gtk code comes here
    gtk_main();

}

void announceWinner(int winner, int draw)
{
    if (winner == -1)
    {
        gtk_label_set_label(GTK_LABEL(announce), "Player 1 wins!");
        player_1_score = player_1_score + 1;
        gchar *display;
        display = g_strdup_printf("%d", player_1_score);
        gtk_label_set_label(GTK_LABEL(score1), display);
        g_free(display);
        disableButtons();
    }
    else if (winner == 1)
    {
        if (gamemode == 1 || gamemode == 2 || gamemode == 3)
        {
            gtk_label_set_label(GTK_LABEL(announce), "Computer wins!");
        }
        else
        {
            gtk_label_set_label(GTK_LABEL(announce), "Player 2 wins!");
        }
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

void hidegrid()
{
    gtk_widget_show(mainMenu);
    gtk_widget_show(header);
    gtk_widget_hide(tttpage);
    gtk_widget_hide(player1);
    gtk_widget_hide(player2);
    gtk_widget_hide(score1);
    gtk_widget_hide(score2);
    gtk_widget_hide(announce);
    gtk_widget_hide(back);
    gtk_widget_hide(reset);
    gtk_widget_hide(restart);
    resetGame();
}

void hideMenu()
{
    gtk_widget_hide(mainMenu);
    gtk_widget_hide(header);
    gtk_widget_show(tttpage);
    gtk_widget_show(player1);
    gtk_widget_show(player2);
    gtk_widget_show(score1);
    gtk_widget_show(score2);
    gtk_widget_show(announce);
    gtk_widget_show(back);
    gtk_widget_show(reset);
    gtk_widget_show(restart);

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
    player_1_score = 0;
    player_2_score = 0;
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
        hideMenu();
        gtk_label_set_label(GTK_LABEL(player2), "Player 2");
        resetBoard();
    }
    else if (*ptr_gamemode == '1')
    {
        gamemode = 1;
        setAIDifficulty();
        hideMenu();
        gtk_label_set_label(GTK_LABEL(player2), "Easy");
        resetBoard();
    }
    else if (*ptr_gamemode == '2')
    {
        gamemode = 2;
        setAIDifficulty();
        hideMenu();
        gtk_label_set_label(GTK_LABEL(player2), "Medium");
        resetBoard();
    }
    else if (*ptr_gamemode == '3')
    {
        gamemode = 3;
        setAIDifficulty();
        hideMenu();
        gtk_label_set_label(GTK_LABEL(player2), "Hard");
        resetBoard();
    }
}