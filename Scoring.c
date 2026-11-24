#include "GameHeaders.h"
#include "Scoring.h"

int calculate_score(const GameData *gamedata, int current_score)
{
    const Racer *t = &gamedata->trainee;

    int stats_total = t->speed + t->stamina + t->power + t->guts + t->wit;
    int net_cash    = gamedata->trainer.cash - gamedata->trainer.debt; // can be negative

    return current_score + stats_total + net_cash;
}
