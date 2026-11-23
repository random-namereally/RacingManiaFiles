#include"GameHeaders.h"

// Initializes all values needed for game startup (WIP)
void initialize_game(GameData *gamedata)
{
    gamedata->trainee = (Racer) // My hands bled without complex literals or whatever the tutorial said, this looks cleaner too
    {
        .name = "Error: No name",
        .is_trainee_named = 0,

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
        .name = "Error: No name",
        .is_trainer_named = 0,
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
        .year = 1,
    };


    strncpy(gamedata->date.char_biweek, "Early", NAMESIZE - 1);
    gamedata->date.char_biweek[NAMESIZE - 1] = '\0';

    strncpy(gamedata->date.char_month, "Jan", NAMESIZE - 1);
    gamedata->date.char_month[NAMESIZE - 1] = '\0';

    strncpy(gamedata->date.char_season, "Winter", NAMESIZE - 1);
    gamedata->date.char_season[NAMESIZE - 1] = '\0';

    strncpy(gamedata->date.char_year, "Junior", NAMESIZE - 1);
    gamedata->date.char_season[NAMESIZE - 1] = '\0';
}


void increment_turn(Date *date)
{
    date->turn++;

    int t = date->turn;

    date->biweek = ((t - 1) % 2) + 1; // 1 to 2

    date->month  = (((t - 1) % 24) / 2) + 1; // 1 to 12

    int m = date->month;

    date->season = (( m - 1) / 3) + 1; // 1 to 4

    date->year   = ((t - 1) / 24) + 1; // 1 to 3


    // String initialization
    const char *biweeks[] = {"ERROR", "Early", "Late", "     "};
    const char *months[] = {"ERROR", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec", "   "};
    const char *seasons[] = {"ERROR ", "Winter", "Spring", "Summer", "Fall  ", "      "};
    const char *year[] = {"ERROR  ", "Junior ", "Classic", "Senior ", "     "};

    // Update date displays
    strncpy(date->char_biweek, biweeks[date->biweek], NAMESIZE - 1);
    date->char_biweek[NAMESIZE - 1] = '\0';

    strncpy(date->char_month, months[date->month], NAMESIZE - 1);
    date->char_month[NAMESIZE - 1] = '\0';

    strncpy(date->char_season, seasons[date->season], NAMESIZE - 1);
    date->char_season[NAMESIZE - 1] = '\0';

    strncpy(date->char_year, year[date->year], NAMESIZE - 1);
    date->char_year[NAMESIZE - 1] = '\0';

}

static int clamp(int value, int low, int high)
    { return value < low ? // Is value less than low?
            low : value > high ? // If true return lowerbound, if not check if value higher than high
                high : value;  // If true return high, if not return initial value
    }

void update_racer_stat(Racer *racer, Pass stat_type, float modifier)
{
    int rounded = round_up( modifier);

    switch (stat_type)
    {
        // racer well-being
        case NumCurrentEnergy: racer->current_energy += clamp(racer->current_energy + modifier, 0, racer->max_energy); break;
        case NumMaxEnergy: racer->max_energy += modifier; break;
        case NumMood: racer->mood = clamp(racer->mood + modifier, 0, 7);  break;

        // Racing stats
        case NumSpeed: racer->speed += rounded; break;
        case NumStamina: racer->stamina += rounded; break;
        case NumPower: racer->power += rounded; break;
        case NumGuts: racer->guts += rounded; break;
        case NumWit: racer->wit += rounded; break;

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
        case NumPopularity: racer->popularity += rounded; break;
        case NumFans: racer->fans += rounded; break;

        //Error
        default: break;
    }
}

void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier)
// update_trainer_stat(&trainer, NumCash, +1)
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

void update_racer_name(Racer *racer, const char *input)
{
    strncpy(racer->name, input, sizeof(racer->name) - 1);
    racer->name[sizeof(racer->name) - 1] = '\0';
}

void update_trainer_name(Trainer *trainer, const char *input)
{
    strncpy(trainer->name, input, sizeof(trainer->name) - 1);
    trainer->name[sizeof(trainer->name) - 1] = '\0';
}


// Technically not robust, but we will move to raylib anyway so who cares //floats crashes it but raylib vrochacho
int input_integer(int min, int max, int *input)
{
    int pass = scanf("%d", input);

    // Clear input
    int i;
    while ((i = getchar()) != '\n' && i != -1);

    // Classifies inputs
    if (pass == EOF) return IntEOF;
    if (pass == 0)   return IntInvalidNotInteger;
    if (*input < min) return IntInvalidTooLow;
    if (*input > max) return IntInvalidTooHigh;

    return IntValid;
}

int input_character(char *input)
{
    // 1. Initialization of function
    // Note: NAMESIZE is a DEFINED at 51
    char temp[NAMESIZE]={0}; // Temporary holder of input
    int truncated = 0, empty = 0; // Classifies inputs for custom confirm handling

    if (fgets(temp, sizeof(temp), stdin) == NULL) return CharEOF; // Gets input from user

    // 2. Alter input to standard. Ie no leading or trailing spaces
    // with a terminator at the very end of the string

    // a. Truncate check and flush if triggered
    if(strchr(temp, '\n')==0)
    {
        int c; while ((c = getchar()) != '\n' && c != EOF); // Flushes stdin of uncaptured data
        truncated++; // This like sets truncated to true
    }


    // b. Removes leading spaces

        // isspace handles most non-printing characters
        // Unsigned char is due to possible emoji use (Can our code even show it?)
        while(isspace((unsigned char)temp[0])||(unsigned char)temp[0] == 0xA0 )
        {
           memmove(temp, temp+1, strlen(temp));
        }

    // c. Replaces first trailing space with terminator

        int i = strlen(temp)-1;
        while (i>=0 && (isspace((unsigned char)temp[i])||(unsigned char)temp[i] == 0xA0)) //So like emojis kills stuff with no unsigned char, I was thinking since Ascii is defnitely not complete so there must be more and this is like whatchacallit beyond that so i wondered how c handles it and yeaah it sucks
        {i--;} temp[i+1]='\0'; // Same shtick as earlier, removes trailing spaces

    // z. actually in the wrong function ignore for now.
    /* strcpy(input, "Great Taste Kopik O");
        input[strlen("Great Taste Kopik O")] = '\0'; */

    // d. if string is empty place warning
    if (strlen(temp)==0) empty++; //Sets empty to true


    strncpy(input, temp, NAMESIZE); // Places temp into input after cleaning and classification

    // Final Verdict
    if (truncated + empty == 2) {return CharTruncatedAndEmpty;} // If the string is truncated yet empty
    if (truncated == 1) {return CharTruncated;} // If the string is truncated but has character
    if (empty == 1) {return CharEmpty;} // If the string has nothing inside except for terminator
    return CharValid; // If no flags are triggered
}


void reset_inputs(MenuInputs *inputs)
{
    inputs->choice = 0;
    inputs->name[0] = '\0';
    inputs->type = -1;
    inputs->confirm = 0;
    inputs->status = 0;
}

int round_up(float input)
{
    return (input >= 0) ? (int)ceilf(input) : (int)floorf(input);
}
