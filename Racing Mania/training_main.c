#include "training.h"
#include "GameHeaders.h"

int main_training(GameData *gamedata){
    make_training_choice(&gamedata->trainee, &gamedata->trainer);
    getchar();
    return SceneActionHub;
}

void train_racer(Racer *trainee, Trainer *trainer, Pass stat_type){
    update_racer_stat(trainee, stat_type, +1);
    update_racer_stat(trainee, NumCurrentEnergy, -1);
    update_trainer_stat(trainer, NumCash, -10);
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
            train_racer(trainee, trainer, NumSpeed);
            printf("+1 Speed, -1 Energy, -10 Cash\n");
        }else if(playerchoice == '2'){
            train_racer(trainee, trainer, NumStamina);
            printf("+1 Stamina -1 Energy, -10 Cash\n");
        }else if(playerchoice == '3'){
            train_racer(trainee, trainer, NumPower);
            printf("+1 Power, -1 Energy, -10 Cash\n");
        }else if(playerchoice == '4'){
            train_racer(trainee, trainer, NumGuts);
            printf("+1 Guts, -1 Energy, -10 Cash\n");
        }else if(playerchoice == '5'){
            train_racer(trainee, trainer, NumWit);
            printf("+1 Wits, -1 Energy, -10 Cash\n");
        }else if(playerchoice == '6'){
            break;
        }else{
            printf("\nPlease enter a valid input \n");
        }
    }
}
