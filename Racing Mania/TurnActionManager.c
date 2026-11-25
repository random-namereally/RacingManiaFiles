#include "GameHeaders.h"

#define RESTGREAT 100
#define RESTGOOD 70
#define RESTNEUTRAL 50
#define RESTBAD 30
#define RESTAWFUL 10

//Cumulative
#define CHANCERESTGREAT 25
#define CHANCERESTGOOD 250
#define CHANCERESTNEUTRAL 875
#define CHANCERESTBAD 975

void rest_handler(GameData *gamedata);
static int roll_rest();
static void draw_rest (Racer *trainee, int energy_gained);
static void draw_rest_header (int energy_gained);
static void draw_rest_flavour (const char *name, int energy_gained);


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
            rest_handler(gamedata);
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
    TurnTransition(gamedata);
    return;
}

void rest_handler(GameData *gamedata)
{
    // Roll for what kind of energy gained
    int energy_gained = roll_rest();

    // Update stat
    update_racer_stat(&gamedata->trainee, NumCurrentEnergy, energy_gained);

    // Draw it
    draw_rest(&gamedata->trainee, energy_gained);

    // Prompt confirmation
    getflush();

}

static int roll_rest() {
    int roll = (rand() % 1000) + 1; // Generates from 1 to 1000

    // An if-else stack is very much necessary here!
    if      (roll <= CHANCERESTGREAT)   {return RESTGREAT;}     // 1-25 2.5%
    else if (roll <= CHANCERESTGOOD)    {return RESTGOOD;}      // 26-250 2.5%
    else if (roll <= CHANCERESTNEUTRAL) {return RESTNEUTRAL;}
    else if (roll <= CHANCERESTBAD)     {return RESTBAD;}
    else                                {return RESTAWFUL;}
}

static void draw_rest (Racer *trainee, int energy_gained)
{
    printf("\033[2J\033[H");

    draw_rest_header (energy_gained);

    draw_rest_flavour (trainee->name, energy_gained);

    std_prompt("any key to continue", 0, 0);
}

static void draw_rest_header (int energy_gained)
{
    switch (energy_gained)
    {
        case RESTGREAT:
            std_header("An Umazing Vacation");
            break;
        case RESTGOOD:
            std_header("A Refreshing Rest");
            break;
        case RESTNEUTRAL:
            std_header("A Normal Rest");
            break;
        case RESTBAD:
            std_header("A Troubled Rest");
            break;
        case RESTAWFUL:
            std_header("An Umawful Laze");
            break;
    }
}

static void draw_rest_flavour (const char *name, int energy_gained)
{
    switch (energy_gained)
    {
        case RESTGREAT:
            printf("%s's relaxation rid them of all their fatigue and,\nleft them revujenated in body and soul!\n", name);
            printf("Energy: +100  Mood: +1\n");
            break;
        case RESTGOOD:
            printf("%s's relaxation replenished their stores and ready for the world!\n", name);
            printf("Energy: +70\n");
            break;
        case RESTNEUTRAL:
            printf("%s relaxed nicely and woke up energized\n", name);
            printf("Energy: +50\n");
            break;
        case RESTBAD:
            printf("%s tried to relax but but couldn't do so completely\n", name);
            printf("Energy: +30\n");
            break;
        case RESTAWFUL:
            printf("%s relaxed too hard, destroying their sleep schedule and leaving them winded!\n", name);
            printf("Energy: +10  Mood: -1  Afflicted: Night Owl\n");
            break;
    }
}
