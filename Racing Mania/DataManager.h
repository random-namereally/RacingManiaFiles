#ifndef GAME_STATE_H
#define GAME_STATE_H

// Game version for flair
#define GAME_VERSION "v0.1"

typedef enum { //This essentially is an enum for ease of understanding in how the goto_scene works.
    SceneStartMenu,
    SceneStartCareer,
    SceneLoadCareer,
    SceneViewLeaderboard,
    SceneDebug,
    SceneAction_hub,
    SceneEnding,
    SceneError,
} GameState;

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
    char elevation[1000]; // Note: Each index is 2.5 meters
    char curve[1000]; // Curve relative to previous meter, local curve.
    char left_width[1000]; // how wide from the center to the left each part of a track is
    char right_width[1000]; // how wide from the center to the right each part of a track is
} TrackMapData; //VERY HEAVY only one must be loaded at a time. 100 of these is 3mb

typedef struct {
    int length;
    int ground;
    int prestige; //Open<G3<G2<G1 from lowest to highest
    int stamina_check;//1-3 from bad to meh to fit
    int power_check;//1-3 from bad to meh to fit
    int fan_requirement;
    int fan_reward;
    int race_requirement; //Used to lookup if player has won a different race so 2 will go to the 2nd race in the special racelist
    char name[50];
} TrackMetaData; // Lighter data that all a player needs to see

typedef struct {

    float meters_ran;
    float meters_left;
    float progress_percent;

    float left_distance;
    float dright_distance;

    float current_angle;
    float max_angle_change;

    float current_velocity;
    float max_velocity;

    float current_stamina;
    float max_stamina;

    float current_acceleration;
    float max_acc_change;

    float early_stamina_cost;
    float early_power_boost;

    float spurt_penalty_reduction; //Reduces Exhaustion penalty if in spurt
    float spurt_velocity_boost; //scales with speed
    float spurt_max_velocity_boost; //scales with speed
    float spurt_max_acc_boost; //scales with speed

    float challenge_velocity_boost;
    float challenge_acc_boost;
} RaceRacerData;

typedef struct {
    int choice;
    char* name[50];
    int confirm;
    int status;
} MenuInputs;

typedef struct {
Racer trainee;
Trainer trainer;
Date date;
Racer rival[50];
RaceRacerData racer[20];
TrackMapData trackmapdata;
TrackMetaData trackmetadata[30];
int rain_chance;
} GameData; //All data that needs to be funneled out of the game.

typedef struct {
RaceRacerData racer[20];
TrackMapData trackmapdata;
int condition;
} RaceSimData; //Local to Races only

void initialize_game(GameData *gamedata);
void increment_turn(Date *date);

void update_racer_stat(Racer *racer, Pass stat_type, int modifier); //update_racer_stat(&racer, stat_type, modifier);
void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier); //update_trainer_stat(&trainer, stat_type, modifier);
void update_racer_name(Racer *racer, char* input); //update_racer_name(&racer, input);
void update_trainer_name(Trainer *trainer, char* input);



void reset_inputs(MenuInputs *inputs);
int input_integer(int min, int max, int *input);
//int input_character(*input);
void generic_err_msg(int min, int max, int *status);

#endif
