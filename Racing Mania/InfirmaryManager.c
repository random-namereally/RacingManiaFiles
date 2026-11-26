#include "GameHeaders.h"

#define INVALID -1
#define CURED 0
#define UNCURED 1



//Cumulative
#define FAILURECHANCE 15


static int is_ill(Racer *trainee);
static int roll_condition(Racer *trainee);
static int roll_cure();
static void draw_result (Racer *trainee, int condition, int result);
static void draw_inf_header (int condition, int result);
static void draw_inf_flavour (const char *name, int condition, int result);

int main_infirmary(GameData *gamedata)
{
    int result = -1; // -1 = Not ill, 0 = Cured, 1 = uncured
    int condition = 0;

    // Check if actually ill
    if (is_ill(&gamedata->trainee))
    {
        // If ill, try to cure
        condition = roll_condition(&gamedata->trainee); // Rolls until it picks a valid condition to cure
        result = roll_cure(); // Rolls if it succeeds
        update_racer_stat(&gamedata->trainee, condition, result); // Update stats to new or old stat
        update_racer_stat(&gamedata->trainee, NumCurrentEnergy, 20); // Gives 20 energy
    }

    // Draw it
    draw_result(&gamedata->trainee, condition, result);

    // Prompt confirmation
    getflush();

}

static int is_ill(Racer *trainee)
{
    // Returns 1 if any of these has 1 meaning the trainee is ill, else return 0
    return (trainee->has_night_owl          ||
            trainee->has_slacker            ||
            trainee->has_slow_metabolism    ||
            trainee->has_migraine           ||
            trainee->has_dry_skin           ||
            trainee->has_practice_poor        );
}

static int roll_cure()
{
    // Returns 1 if uncured, 0 if cured
    int roll = (rand() % 100) + 1; // Generates from 1 to 1000
    return (roll<=FAILURECHANCE);

}

static int roll_condition(Racer *trainee)
{
    while (1)
    {
        int roll = (rand() % 6) + 1; // Generates from 1 to 6
        switch (roll)
        {
            case 1: if (trainee->has_night_owl)         return NumHasNightOwl;          break;
            case 2: if (trainee->has_slacker)           return NumHasSlacker;           break;
            case 3: if (trainee->has_slow_metabolism)   return NumHasSlowMetabolism;    break;
            case 4: if (trainee->has_migraine)          return NumHasMigraine;          break;
            case 5: if (trainee->has_dry_skin)          return NumHasDrySkin;           break;
            case 6: if (trainee->has_practice_poor)     return NumHasPracticePoor;      break;
        }
    }


}

static void draw_result (Racer *trainee, int condition, int result)
{
    clear_screen();

    draw_inf_header (condition, result);

    draw_inf_flavour (trainee->name, condition, result);

    std_prompt("to continue", 0, 0);
}

static void draw_inf_header (int condition, int result)
{
    switch (result)
    {
        case INVALID:
            std_header("Healthy Trainee");
            break;
        case CURED:
            std_header("Umazing Recovery");
            break;
        case UNCURED:
            std_header("The Bad News");
            break;

        default: printf("ERROR IN DRAW_INF_HEADER"); break;
    }
}

static void draw_inf_flavour (const char *name, int condition, int result)
{
    char* charcondition;
    switch (condition)
    {
        case NumHasNightOwl:        charcondition = "Night Owl";            break;
        case NumHasSlacker:         charcondition = "Slacker";              break;
        case NumHasSlowMetabolism:  charcondition = "Slow Metabolism";      break;
        case NumHasMigraine:        charcondition = "Migraine";             break;
        case NumHasDrySkin:         charcondition = "Dry Skin";             break;
        case NumHasPracticePoor:    charcondition = "Practice Poor";        break;
        default:                                                            break;
    }

    switch (result)
    {
        case INVALID:
            printf("%s is healthy!\n", name);
            break;
        case CURED:
            printf("%s had a healthy recovery!\n", name);
            printf("%s was cured\n.", charcondition);
            break;
        case UNCURED:
            printf("%s is still afflicted (-_-|||)\n", name);
            printf("%s was not cured\n", charcondition);
            break;

    }
}
