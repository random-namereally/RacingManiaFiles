#ifndef TURNMANAGER_H_INCLUDED
#define TURNMANAGER_H_INCLUDED

typedef enum
{
    NOTHING,
    TrainSpeed = 1,
    TrainStamina = 2,
    TrainPower = 3,
    TrainGuts = 4,
    TrainWit = 5,
    ActionHub = 6,
    DoTrain,
    DoRest,
    DoRecreation,
    DoInfirmary,
}   Actions;

void DoAction(GameData *gamedata, Actions action);
int main_training_hub(GameData *gamedata);
void main_rest(GameData *gamedata);
int main_infirmary(GameData *gamedata);
void TurnTransition(GameData *gamedata);

#endif
