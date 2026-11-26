#include "GameHeaders.h"

void DoAction(GameData *gamedata, Actions action)
{
    int invalid = 0; // Used by infirmary to not increment a turn on the wrong press

    switch (action)
    {
        case TrainSpeed:
            break;

        case TrainPower:
            break;

        case TrainStamina:
            break;

        case TrainGuts:
            break;

        case TrainWits:
            break;

        case DoRest:
            main_rest(gamedata);
            break;

        case DoRecreation:

            /* boost mood/morale, minor stat/energy tweak */
            break;

        case DoInfirmary:
            invalid = main_infirmary(gamedata);
            break;

        default:
            break;
    }
    if (invalid) return;
    TurnTransition(gamedata);
    return;
}

