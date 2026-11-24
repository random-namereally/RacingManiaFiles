#include "training.h"
#include "GameHeaders.h"

int main_training(GameData *gamedata){
    make_training_choice(&gamedata->trainee, &gamedata->trainer);
    return SceneActionHub;
}

int train_racer(Racer *trainee, Trainer *trainer, Pass stat_type){
    if (trainee->current_energy > 0){
        update_racer_stat(trainee, stat_type, +TRAINING_GAIN_STAT);
        update_racer_stat(trainee, NumCurrentEnergy, -TRAINING_COST_ENERGY);
        update_trainer_stat(trainer, NumCash, -TRAINING_COST_CASH);
        return 1;
    }else{
        update_racer_stat(trainee, stat_type, -TRAINING_LOSE_STAT);
        update_racer_stat(trainee, NumCurrentEnergy, -TRAINING_COST_ENERGY);
        update_racer_stat(trainee, NumMood, -TRAINING_lOSE_MOOD);
        update_trainer_stat(trainer, NumCash, -TRAINING_COST_CASH);
        return 0;
    }
}

void print_training_choice(void){
    printf("Training Grounds\n");
    printf("1. Run as quickly as possible on the track\n");
    printf("2. Run around the track repeatedly\n");
    printf("3. Run 100 meters as fast as possible\n");
    printf("4. Run for as long as possible\n");
    printf("5. Maneuver around obstacles\n");
    printf("6. Stop Training");
}

void make_training_choice(Racer *trainee, Trainer *trainer)
{

    char playerchoice = '0';

    print_training_choice();

    while(1)
        {
        scanf(" %1c", &playerchoice);
        getflush();
        if(playerchoice == '1'){
            if(train_racer(trainee, trainer, NumSpeed)){
                printf("+%d Speed, -%d Energy, -%d Cash\n", TRAINING_GAIN_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }else{
                printf("-%d Mood, -%d Speed, -%d Energy, -%d Cash\n", TRAINING_lOSE_MOOD, TRAINING_LOSE_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }
        }else if(playerchoice == '2'){
            train_racer(trainee, trainer, NumStamina);
            if(train_racer(trainee, trainer, NumStamina)){
                printf("+%d Stamina, -%d Energy, -%d Cash\n", TRAINING_GAIN_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }else{
                printf("-%d Mood, -%d Stamina, -%d Energy, -%d Cash\n", TRAINING_lOSE_MOOD, TRAINING_LOSE_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }
        }else if(playerchoice == '3'){
            train_racer(trainee, trainer, NumPower);
            if(train_racer(trainee, trainer, NumPower)){
                printf("+%d Power, -%d Energy, -%d Cash\n", TRAINING_GAIN_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }else{
                printf("-%d Mood, -%d Power, -%d Energy, -%d Cash\n", TRAINING_lOSE_MOOD, TRAINING_LOSE_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }
        }else if(playerchoice == '4'){
            train_racer(trainee, trainer, NumGuts);
            if(train_racer(trainee, trainer, NumGuts)){
                printf("+%d Guts, -%d Energy, -%d Cash\n", TRAINING_GAIN_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }else{
                printf("-%d Mood, -%d Guts, -%d Energy, -%d Cash\n", TRAINING_lOSE_MOOD, TRAINING_LOSE_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }
        }else if(playerchoice == '5'){
            train_racer(trainee, trainer, NumWit);
            if(train_racer(trainee, trainer, NumWit)){
                printf("+%d Wits, -%d Energy, -%d Cash\n", TRAINING_GAIN_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }else{
                printf("-%d Mood, -%d Wits, -%d Energy, -%d Cash\n", TRAINING_lOSE_MOOD, TRAINING_LOSE_STAT, TRAINING_COST_ENERGY, TRAINING_COST_CASH);
            }
        }else if(playerchoice == '6'){
            break;
        }else{
            printf("\nPlease enter a valid input \n");
        }
    }
}
