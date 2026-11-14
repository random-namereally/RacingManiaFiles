#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"DataManager.h"


// Initializes all values needed for game startup (WIP)
void initialize_game(GameData *gamedata)
{
    gamedata->trainee = (Racer)
    {
        .name = "Magnolia Inam O",

        .current_energy = 100,
        .max_energy = 100,
        .mood = 6,

        .speed = 50,
        .stamina = 50,
        .power = 50,
        .guts = 50,
        .wit = 50,

        .speed_multiplier = 1,
        .stamina_multiplier = 1,
        .power_multiplier = 1,
        .guts_multiplier = 1,
        .wit_multiplier = 1,

        .frontrunner_affinity = 3,
        .pacechaser_affinity = 3,
        .latesurger_affinity = 3,
        .endcloser_affinity = 3,

        .dirt_affinity = 3,
        .turf_affinity = 3,

        .sprint_affinity = 3,
        .mile_affinity = 3,
        .medium_affinity = 3,
        .long_affinity = 3,

        .popularity = 0,
        .fans = 0,
    };

    gamedata->trainer = (Trainer)
    {
        .cash = 0,
        .debt = 0,
        .debt_limit = 0,
        .credit_score = 0,
    };

    gamedata->date = (Date)
    {
        .turn = 1,
        .biweek = 1,
        .month = 1,
        .season = 1,
        .year = 1
    };
}


void increment_turn(Date *date)
{
    date->turn++;

    int t = date->turn;

    date->biweek = (t % 2) + 1;

    date->month = ((t % 24) / 2) + 1;

    date->season = ((date->month - 1) / 3) + 1;

    date->year = (t / 24) + 1;
}

void update_racer_stat(Racer *racer, Pass stat_type, int modifier)
{
    switch (stat_type)
    {
        // racer well-being
        case NumCurrentEnergy: racer->current_energy += modifier; break;
        case NumMaxEnergy: racer->max_energy += modifier; break;
        case NumMood: racer->mood += modifier; break;

        // Racing stats
        case NumSpeed: racer->speed += modifier; break;
        case NumStamina: racer->stamina += modifier; break;
        case NumPower: racer->power += modifier; break;
        case NumGuts: racer->guts += modifier; break;
        case NumWit: racer->wit += modifier; break;

        // Multipliers
        case NumSpeedMult: racer->speed_multiplier += modifier; break;
        case NumStaminaMult: racer->stamina_multiplier += modifier; break;
        case NumPowerMult: racer->power_multiplier += modifier; break;
        case NumGutsMult: racer->guts_multiplier += modifier; break;
        case NumWitMult: racer->wit_multiplier += modifier; break;

        // Affinities
        case NumFrontrunnerAffinity: racer->frontrunner_affinity += modifier; break;
        case NumPacechaserAffinity: racer->pacechaser_affinity += modifier; break;
        case NumLatesurgerAffinity: racer->latesurger_affinity += modifier; break;
        case NumEndcloserAffinity: racer->endcloser_affinity += modifier; break;

        case NumDirtAffinity: racer->dirt_affinity += modifier; break;
        case NumTurfAffinity: racer->turf_affinity += modifier; break;

        case NumSprintAffinity: racer->sprint_affinity += modifier; break;
        case NumMileAffinity: racer->mile_affinity += modifier; break;
        case NumMediumAffinity: racer->medium_affinity += modifier; break;
        case NumLongAffinity: racer->long_affinity += modifier; break;

        //Miscellaneous
        case NumPopularity: racer->popularity += modifier; break;
        case NumFans: racer->fans += modifier; break;

        //Error
        default: break;
    }
}

void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier)
{
    switch (stat_type)
    {

        // Trainer finance
        case NumCash: trainer->cash += modifier; break;
        case NumDebt: trainer->debt += modifier; break;
        case NumDebtLimit: trainer->debt_limit += modifier; break;
        case NumCreditScore: trainer->credit_score += modifier; break;

        //Error
        default: break;
    }
}

void update_racer_name(Racer *racer, char *input)
{
    strcpy(racer->name, input);
}

void update_trainer_name(Trainer *trainer, char *input)
{
    strcpy(trainer->name, input);
}


// Technically not robust, but we will move to raylib anyway so who cares //floats crashes it but raylib vrochacho
int input_integer(int min, int max, int *input)
{
    int pass = scanf("%d", input);

    // Clear input
    int i;
    int limit = 0;
    while ((i = getchar()) != '\n' && i != -1)

    // Classifies inputs
    if (pass == 0||pass == -1) return IntInvalidNotInteger;
    if (*input < min) return IntInvalidTooLow;
    if (*input > max) return IntInvalidTooHigh;

    return IntValid;
}

void reset_inputs(MenuInputs *inputs)
{
    inputs->choice = 0;
    inputs->confirm = 0;
    inputs->status = 0;
}
