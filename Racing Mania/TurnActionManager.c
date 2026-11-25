#include "GameHeaders.h"

void DoAction(GameData *gamedata, Actions action)
{

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
            /* recover energy, check side effects */
            break;

        case DoRecreation:
            /* boost mood/morale, minor stat/energy tweak */
            break;

        case DoInfirmary:
            /* clear injury/condition penalty */
            break;

        default:
            break;
    }
}
