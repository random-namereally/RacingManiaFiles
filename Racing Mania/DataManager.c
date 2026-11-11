#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"DataManager.h"


// Initializes all values needed for game startup (WIP)
void initialize_game(Racer *racer, Trainer *trainer, Date *date)
{
    *racer = (Racer)
    {
        .name = "Magnolia Inam O",

        .current_energy = 100,
        .max_energy = 100,
        .mood = 6,

        .display_speed = 50,
        .display_stamina = 50,
        .display_power = 50,
        .display_guts = 50,
        .display_wit = 50,

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
        .display_fans = 0,
    };

    *trainer = (Trainer)
    {
        .display_cash = 0,
        .display_debt = 0,
        .display_debt_limit = 0,
        .display_credit_score = 0,
        .cash = 0,
        .debt = 0,
        .debt_limit = 0,
        .credit_score = 0,
    };

    *date = (Date)
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

        //Racing stat display
        case NumDisplaySpeed: racer->display_speed += modifier; break;
        case NumDisplayStamina: racer->display_stamina += modifier; break;
        case NumDisplayPower: racer->display_power += modifier; break;
        case NumDisplayGuts: racer->display_guts += modifier; break;
        case NumDisplayWit: racer->display_wit += modifier; break;

        // Racing stats
        case NumSpeed: racer->speed += modifier; racer->display_speed = racer->speed; break;
        case NumStamina: racer->stamina += modifier; racer->display_stamina = racer->stamina; break;
        case NumPower: racer->power += modifier; racer->display_power = racer->power; break;
        case NumGuts: racer->guts += modifier; racer->display_guts = racer->guts; break;
        case NumWit: racer->wit += modifier; racer->display_wit = racer->wit; break;

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
        case NumFans: racer->fans += modifier; racer->display_fans = racer->fans; break;
        case NumDisplayFans: racer->display_fans += modifier; break;

        //Error
        default: break;
    }
}

void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier)
{
    switch (stat_type)
    {

        // Trainer finance display
        case NumDisplayCash: trainer->display_cash += modifier; break;
        case NumDisplayDebt: trainer->display_debt += modifier; break;
        case NumDisplayDebtLimit: trainer->display_debt_limit += modifier; break;
        case NumDisplayCreditScore: trainer->display_credit_score += modifier; break;

        // Trainer finance
        case NumCash: trainer->cash += modifier; trainer->display_cash = trainer->cash; break;
        case NumDebt: trainer->debt += modifier; trainer->display_debt = trainer->debt; break;
        case NumDebtLimit: trainer->debt_limit += modifier; trainer->display_debt_limit = trainer->debt_limit; break;
        case NumCreditScore: trainer->credit_score += modifier; trainer->display_credit_score = trainer->credit_score; break;

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

int get_racer_stat(Racer *racer, Pass stat_type)
{
    switch (stat_type)
    {
        // racer well-being
        case NumCurrentEnergy: return racer->current_energy;
        case NumMaxEnergy: return racer->max_energy;
        case NumMood: return racer->mood;

        // Display Racing stats
        case NumDisplaySpeed: return racer->display_speed;
        case NumDisplayStamina: return racer->display_stamina;
        case NumDisplayPower: return racer->display_power;
        case NumDisplayGuts: return racer->display_guts;
        case NumDisplayWit: return racer->display_wit;

        // Racing stats
        case NumSpeed: return racer->speed;
        case NumStamina: return racer->stamina;
        case NumPower: return racer->power;
        case NumGuts: return racer->guts;
        case NumWit: return racer->wit;

        // Multipliers
        case NumSpeedMult: return racer->speed_multiplier;
        case NumStaminaMult: return racer->stamina_multiplier;
        case NumPowerMult: return racer->power_multiplier;
        case NumGutsMult: return racer->guts_multiplier;
        case NumWitMult: return racer->wit_multiplier;

        // Affinities
        case NumFrontrunnerAffinity: return racer->frontrunner_affinity;
        case NumPacechaserAffinity: return racer->pacechaser_affinity;
        case NumLatesurgerAffinity: return racer->latesurger_affinity;
        case NumEndcloserAffinity: return racer->endcloser_affinity;

        case NumDirtAffinity: return racer->dirt_affinity;
        case NumTurfAffinity: return racer->turf_affinity;

        case NumSprintAffinity: return racer->sprint_affinity;
        case NumMileAffinity: return racer->mile_affinity;
        case NumMediumAffinity: return racer->medium_affinity;
        case NumLongAffinity: return racer->long_affinity;

        case NumPopularity: return racer->popularity;
        case NumFans: return racer->fans;
        case NumDisplayFans: return racer->display_fans;
        // Error
        default: printf("Error: Out of scope"); return -1;
    }
}

char* get_racer_name(Racer *racer)
{
    return racer->name;
}

int get_trainer_stat(Trainer *trainer, Pass stat_type)
{
    switch (stat_type)
    {
        // Trainer finance display
        case NumDisplayCash: return trainer->display_cash;
        case NumDisplayDebt: return trainer->display_debt;
        case NumDisplayDebtLimit: return trainer->display_debt_limit;
        case NumDisplayCreditScore: return trainer->display_credit_score;

        // Trainer finance
        case NumCash: return trainer->cash;
        case NumDebt: return trainer->debt;
        case NumDebtLimit: return trainer->debt_limit;
        case NumCreditScore: return trainer->credit_score;
        // Error
        default: printf("Error: Out of scope"); return -1;
    }
}

char* get_trainer_name(Trainer *trainer)
{
    return trainer->name;
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
