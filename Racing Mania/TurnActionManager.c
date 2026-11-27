#include "GameHeaders.h"

void DoAction(GameData *gamedata, Actions action)
{
    int invalid = 0; // Used by infirmary and train to not increment

    switch (action)
    {
        case DoTrain:
            invalid = main_training_hub(gamedata);
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

