#ifndef MACHINE_LEARNING_H
#define MACHINE_LEARNING_H

//function declaration

int evaluateML(int depth);

int ml_algorithm();

void findBestMoveML();

void create_model();

void load_data();

void shuffle(int length);

void split_data();

void train_data(int row);

void updateWeights(int row);

void test_data(int row);

void save_weights();

void load_weights();

int checkWinner();

#endif