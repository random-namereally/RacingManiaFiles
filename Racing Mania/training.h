#include "GameHeaders.h"
#ifndef TRAINING_H
#define TRAINING_H

//ARE THESE THINGS GONNA BE USED ELSEWHERE?

//increases racer stats at the cost of energy and cash
void train_racer(Racer *trainee, Trainer *trainer, Pass stat_type);

//prints the menu of available choices for training
void print_training_choice(void);

//makes player choose which thing they want to train
void make_training_choice(Racer *trainee, Trainer *trainer);

#endif
