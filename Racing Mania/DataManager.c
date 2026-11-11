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
        case num_current_energy: racer->current_energy += modifier; break;
        case num_max_energy: racer->max_energy += modifier; break;
        case num_mood: racer->mood += modifier; break;

        //Racing stat display
        case num_display_speed: racer->display_speed += modifier; break;
        case num_display_stamina: racer->display_stamina += modifier; break;
        case num_display_power: racer->display_power += modifier; break;
        case num_display_guts: racer->display_guts += modifier; break;
        case num_display_wit: racer->display_wit += modifier; break;

        // Racing stats
        case num_speed: racer->speed += modifier; racer->display_speed = racer->speed; break;
        case num_stamina: racer->stamina += modifier; racer->display_stamina = racer->stamina; break;
        case num_power: racer->power += modifier; racer->display_power = racer->power; break;
        case num_guts: racer->guts += modifier; racer->display_guts = racer->guts; break;
        case num_wit: racer->wit += modifier; racer->display_wit = racer->wit; break;

        // Multipliers
        case num_speed_mult: racer->speed_multiplier += modifier; break;
        case num_stamina_mult: racer->stamina_multiplier += modifier; break;
        case num_power_mult: racer->power_multiplier += modifier; break;
        case num_guts_mult: racer->guts_multiplier += modifier; break;
        case num_wit_mult: racer->wit_multiplier += modifier; break;

        // Affinities
        case num_frontrunner_affinity: racer->frontrunner_affinity += modifier; break;
        case num_pacechaser_affinity: racer->pacechaser_affinity += modifier; break;
        case num_latesurger_affinity: racer->latesurger_affinity += modifier; break;
        case num_endcloser_affinity: racer->endcloser_affinity += modifier; break;

        case num_dirt_affinity: racer->dirt_affinity += modifier; break;
        case num_turf_affinity: racer->turf_affinity += modifier; break;

        case num_sprint_affinity: racer->sprint_affinity += modifier; break;
        case num_mile_affinity: racer->mile_affinity += modifier; break;
        case num_medium_affinity: racer->medium_affinity += modifier; break;
        case num_long_affinity: racer->long_affinity += modifier; break;

        //Miscellaneous
        case num_popularity: racer->popularity += modifier; break;
        case num_fans: racer->fans += modifier; racer->display_fans = racer->fans; break;
        case num_display_fans: racer->display_fans += modifier; break;

        //Error
        default: break;
    }
}

void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier)
{
    switch (stat_type)
    {

        // Trainer finance display
        case num_display_cash: trainer->display_cash += modifier; break;
        case num_display_debt: trainer->display_debt += modifier; break;
        case num_display_debt_limit: trainer->display_debt_limit += modifier; break;
        case num_display_credit_score: trainer->display_credit_score += modifier; break;

        // Trainer finance
        case num_cash: trainer->cash += modifier; trainer->display_cash = trainer->cash; break;
        case num_debt: trainer->debt += modifier; trainer->display_debt = trainer->debt; break;
        case num_debt_limit: trainer->debt_limit += modifier; trainer->display_debt_limit = trainer->debt_limit; break;
        case num_credit_score: trainer->credit_score += modifier; trainer->display_credit_score = trainer->credit_score; break;


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
        case num_current_energy:return racer->current_energy;
        case num_max_energy:return racer->max_energy;
        case num_mood:return racer->mood;

        // Display Racing stats
        case num_display_speed: return racer->display_speed;
        case num_display_stamina: return racer->display_stamina;
        case num_display_power: return racer->display_power;
        case num_display_guts: return racer->display_guts;
        case num_display_wit: return racer->display_wit;

        // Racing stats
        case num_speed:return racer->speed;
        case num_stamina:return racer->stamina;
        case num_power:return racer->power;
        case num_guts:return racer->guts;
        case num_wit: return racer->wit;

        // Multipliers
        case num_speed_mult: return racer->speed_multiplier;
        case num_stamina_mult: return racer->stamina_multiplier;
        case num_power_mult: return racer->power_multiplier;
        case num_guts_mult: return racer->guts_multiplier;
        case num_wit_mult: return racer->wit_multiplier;

        // Affinities
        case num_frontrunner_affinity: return racer->frontrunner_affinity;
        case num_pacechaser_affinity: return racer->pacechaser_affinity;
        case num_latesurger_affinity: return racer->latesurger_affinity;
        case num_endcloser_affinity: return racer->endcloser_affinity;

        case num_dirt_affinity: return racer->dirt_affinity;
        case num_turf_affinity: return racer->turf_affinity;

        case num_sprint_affinity: return racer->sprint_affinity;
        case num_mile_affinity: return racer->mile_affinity;
        case num_medium_affinity: return racer->medium_affinity;
        case num_long_affinity: return racer->long_affinity;

        case num_popularity: return racer->popularity;
        case num_fans: return racer->fans;
        case num_display_fans: return racer->display_fans;

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
        case num_display_cash: return trainer->display_cash;
        case num_display_debt: return trainer->display_debt;
        case num_display_debt_limit: return trainer->display_debt_limit;
        case num_display_credit_score: return trainer->display_credit_score;

        // Trainer finance
        case num_cash: return trainer->cash;
        case num_debt: return trainer->debt;
        case num_debt_limit: return trainer->debt_limit;
        case num_credit_score: return trainer->credit_score;

        // Error
        default: printf("Error: Out of scope"); return -1;
    }
}

char* get_trainer_name(Trainer *trainer)
{
    return trainer->name;
}

int input_integer(int min, int max, int *input)
{

    if (scanf("%d", input) != 1)
    {
        while (getchar() != '\n');
        return int_invalid_not_number;
    }

    while (getchar() != '\n');

    if (*input < min) return int_invalid_too_low;
    if (*input > max) return int_invalid_too_high;

    return int_valid;
}

void reset_inputs(MenuInputs *inputs)
{
    inputs->choice = 0;
    inputs->confirm = 0;
    inputs->status = 0;
}
