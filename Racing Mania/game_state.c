#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include"game_state.h"


// Initializes all values needed for game startup (WIP)
void initialize_game(Player *athlete, Date *date)
{
    *athlete = (Player)
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
        .long_affinity = 3
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

void update_trainee_stat(Player *trainee, Pass stat_type, int modifier)
{
    switch (stat_type)
    {
        // trainee well-being
        case num_current_energy: trainee->current_energy += modifier; break;
        case num_max_energy: trainee->max_energy += modifier; break;
        case num_mood: trainee->mood += modifier; break;

        // Racing stats
        case num_speed: trainee->speed += modifier; break;
        case num_stamina: trainee->stamina += modifier; break;
        case num_power: trainee->power += modifier; break;
        case num_guts: trainee->guts += modifier; break;
        case num_wit: trainee->wit += modifier; break;

        // Multipliers
        case num_speed_mult: trainee->speed_multiplier += modifier; break;
        case num_stamina_mult: trainee->stamina_multiplier += modifier; break;
        case num_power_mult: trainee->power_multiplier += modifier; break;
        case num_guts_mult: trainee->guts_multiplier += modifier; break;
        case num_wit_mult: trainee->wit_multiplier += modifier; break;

        // Affinities
        case num_frontrunner_affinity: trainee->frontrunner_affinity += modifier; break;
        case num_pacechaser_affinity: trainee->pacechaser_affinity += modifier; break;
        case num_latesurger_affinity: trainee->latesurger_affinity += modifier; break;
        case num_endcloser_affinity: trainee->endcloser_affinity += modifier; break;

        case num_dirt_affinity: trainee->dirt_affinity += modifier; break;
        case num_turf_affinity: trainee->turf_affinity += modifier; break;

        case num_sprint_affinity: trainee->sprint_affinity += modifier; break;
        case num_mile_affinity: trainee->mile_affinity += modifier; break;
        case num_medium_affinity: trainee->medium_affinity += modifier; break;
        case num_long_affinity: trainee->long_affinity += modifier; break;

        //Error
        default: break;
    }
}

void update_trainee_name(Player *trainee, char *input)
{
    strcpy(trainee->name, input);
}
int get_trainee_stat(Player *trainee, Pass stat_type)
{
    switch (stat_type)
    {
        // trainee well-being
        case num_current_energy:return trainee->current_energy;
        case num_max_energy:return trainee->max_energy;
        case num_mood:return trainee->mood;

        // Racing stats
        case num_speed:return trainee->speed;
        case num_stamina:return trainee->stamina;
        case num_power:return trainee->power;
        case num_guts:return trainee->guts;
        case num_wit: return trainee->wit;

        // Multipliers
        case num_speed_mult: return trainee->speed_multiplier;
        case num_stamina_mult: return trainee->stamina_multiplier;
        case num_power_mult: return trainee->power_multiplier;
        case num_guts_mult: return trainee->guts_multiplier;
        case num_wit_mult: return trainee->wit_multiplier;

        // Affinities
        case num_frontrunner_affinity: return trainee->frontrunner_affinity;
        case num_pacechaser_affinity: return trainee->pacechaser_affinity;
        case num_latesurger_affinity: return trainee->latesurger_affinity;
        case num_endcloser_affinity: return trainee->endcloser_affinity;

        case num_dirt_affinity: return trainee->dirt_affinity;
        case num_turf_affinity: return trainee->turf_affinity;

        case num_sprint_affinity: return trainee->sprint_affinity;
        case num_mile_affinity: return trainee->mile_affinity;
        case num_medium_affinity: return trainee->medium_affinity;
        case num_long_affinity: return trainee->long_affinity;

        // Error
        default: return -1;
    }
}

char* get_trainee_name(Player *trainee)
{
    return trainee->name;
}
