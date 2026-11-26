#ifndef TURNMANAGER_H_INCLUDED
#define TURNMANAGER_H_INCLUDED

typedef enum
{
    TrainSpeed,
    TrainPower,
    TrainStamina,
    TrainGuts,
    TrainWits,
    DoRest,
    DoRecreation,
    DoInfirmary,
}   Actions;

void DoAction(GameData *gamedata, Actions action);
void main_rest(GameData *gamedata);
int main_infirmary(GameData *gamedata);
void TurnTransition(GameData *gamedata);

#endif
