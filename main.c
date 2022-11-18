/* Libraries */
#include "global.h"
#include "gui.h"

/* Function Prototypes */
void initializeGUI();

/* Declaring value to global variables */
int turncounter = 0;
int player_1_score = 0;
int player_2_score = 0;
int gamemode = 0;
int bestMove[2] = {-1, -1};
float aiPercentage = 0;

int main(int argc, char *argv[])
{
    gtk_init(&argc, &argv);
    initializeGUI();
    srand(time(NULL));
}