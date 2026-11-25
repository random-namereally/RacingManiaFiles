#include "GameHeaders.h"
#ifndef TRAINING_H
#define TRAINING_H

#define TRAINING_COST_CASH 10

#define TRAINING_COST_ENERGY 1

#define TRAINING_GAIN_STAT 10

#define TRAINING_LOSE_STAT 10

#define TRAINING_lOSE_MOOD 1

//Allows it to be used elsewhere
int main_training(GameData *gamedata);

//increases racer stats at the cost of energy and cash
int train_racer(Racer *trainee, Trainer *trainer, Pass stat_type);

//prints the menu of available choices for training
void print_training_choice(void);

//makes player choose which thing they want to train
void make_training_choice(Racer *trainee, Trainer *trainer);

#endif
