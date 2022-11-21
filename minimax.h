#ifndef MINIMAX_H
#define MINIMAX_H

//function declaration
int evaluate();

int minimax(int depth, int isMax);

void findBestMove();

int max(int num1, int num2);

int min(int num1, int num2);

void setAIDifficulty();

int getAIDecision();

#endif