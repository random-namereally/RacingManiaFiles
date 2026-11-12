#ifndef GAME_STATE_H
#define GAME_STATE_H

// Game version for flair
#define GAME_VERSION "v0.1"

// When pulling or pushing data you should use this so it's easier to read, rather than numbers which can work but may me illegible.
typedef enum
{
    NumCurrentEnergy,
    NumMaxEnergy,
    NumMood,
    NumSpeed,
    NumStamina,
    NumPower,
    NumGuts,
    NumWit,
    NumSpeedMult,
    NumStaminaMult,
    NumPowerMult,
    NumGutsMult,
    NumWitMult,
    NumFrontrunnerAffinity,
    NumPacechaserAffinity,
    NumLatesurgerAffinity,
    NumEndcloserAffinity,
    NumDirtAffinity,
    NumTurfAffinity,
    NumSprintAffinity,
    NumMileAffinity,
    NumMediumAffinity,
    NumLongAffinity,
    NumPopularity,
    NumFans,
    NumCash,
    NumDebt,
    NumDebtLimit,
    NumCreditScore,
}Pass;

typedef enum
{
    IntValid,
    IntInvalidNotInteger,
    IntInvalidTooLow,
    IntInvalidTooHigh,
    IntInvalidExceededLimit,
    IntInvalidOther,
    IntSet,

}InputValidity;

typedef struct
 {
    // Name of racer racer
    char name[50];

    int current_energy;
    int max_energy;
    int mood;

    int speed;
    int stamina;
    int power;
    int guts;
    int wit;

    float speed_multiplier;
    float stamina_multiplier;
    float power_multiplier;
    float guts_multiplier;
    float wit_multiplier;

    int frontrunner_affinity;
    int pacechaser_affinity;
    int latesurger_affinity;
    int endcloser_affinity;

    int dirt_affinity;
    int turf_affinity;

    int sprint_affinity;
    int mile_affinity;
    int medium_affinity;
    int long_affinity;

    int popularity;
    int fans;
    int display_fans;
} Racer;

typedef struct
 {
    char name[50];

    int cash;
    int debt;
    int debt_limit;
    int credit_score;

 } Trainer;

typedef struct {
    int turn;
    int biweek;
    int month;
    int season;
    int year;
} Date;

typedef struct {
    int length;
    int ground;
    int weather;
    char name[50];
    char elevation[1000]; // Note: Each index is 2.5 meters
    char curve[1000];

} Track;

typedef struct {
    int choice;
    int confirm;
    int status;
} MenuInputs;

void initialize_game(Racer *racer, Trainer *trainer, Date *date);
void increment_turn(Date *date);

void update_racer_stat(Racer *racer, Pass stat_type, int modifier); //update_racer_stat(&racer, stat_type, modifier);
void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier); //update_trainer_stat(&trainer, stat_type, modifier);
void update_racer_name(Racer *racer, char* input); //update_racer_name(&racer, input);
void update_trainer_name(Trainer *trainer, char* input);

int input_integer(int min, int max, int *input);
void reset_inputs(MenuInputs *inputs);

#endif
