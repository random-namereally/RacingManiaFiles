#ifndef DATAMANAGER_H
#define DATAMANAGER_H

// Game version for flair
#define GAME_VERSION "v0.2"
#define NAMESIZE 51

typedef enum { //This essentially is an enum for ease of understanding in how the goto_scene works.
    SceneStartMenu,
    SceneStartCareer,
    SceneLoadCareer,
    SceneViewLeaderboard,
    SceneDebug,
    SceneBlackjack,
    SceneActionHub,
    SceneTrainingHub,
    SceneEnding,
    SceneError,
    SceneExitGame,
    SceneTemplate,
} GameState;

typedef enum
{
  Entered,
  NotEntered,
  Mandatory,
  Blocked,
  WasEntered,
  Wasmandatory,
} RaceEligibilityStatus;

typedef enum
{
    IsCharacter,
    IsInteger,
} IsWhat;

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
    // Trainer stats
    NumCash,
    NumDebt,
    NumDebtLimit,
    NumCreditScore,
}Pass;

// Start of input structs and enums

    // Status of  input
    typedef enum
    {
        IntValid = 10,
        IntInvalidNotInteger = 11,
        IntInvalidTooLow = 12,
        IntInvalidTooHigh = 13,
        IntEOF = 19,
        CharValid = 20,
        CharTruncatedAndEmpty = 21,
        CharTruncated = 22,
        CharEmpty = 23,
        CharEOF = 29,
    }InputStatus;

    typedef enum
    {
        InputInt = 1,
        InputChar = 2,
    }InputType;

    typedef struct {
        int choice;
        char name[NAMESIZE];
        int confirm;
        InputType type;
        InputStatus status;
    } MenuInputs;

// End of input structs and enums

typedef struct
 {
    // Name of racer racer
    char name[NAMESIZE];
    int is_trainee_named;

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
} Racer;

typedef struct
 {
    char name[NAMESIZE];
    int is_trainer_named;

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
    char char_biweek[NAMESIZE];
    char char_month[NAMESIZE];
    char char_season[NAMESIZE];
    char char_year[NAMESIZE];
} Date;

// Start of Track and race data structs

    typedef struct { // These are the instructions for making the track
        int id;
        int elevation[2][30]; // format for all of this is
        int curve[2][30];
        int left_width[2][30];
        int right_width[2][30];
    } TrackMapData;

    typedef struct { // These are the data for each track which may be used outside of a race
        int id;
        int length;
        int ground;
        int prestige; //Open<G3<G2<G1 from lowest to highest
        int stamina_check;//1-3 from bad to meh to fit
        int power_check;//1-3 from bad to meh to fit
        int fan_requirement;
        int fan_reward;
        int race_requirement; //Used to lookup if player has won a different race so 2 will go to the 2nd race in the special racelist
        char name[NAMESIZE];
        int scheduled_turn;   // turn it happens in (so we know where to place it)
        int entered;          // If player is in the race (Entered, Not Entered, Mandatory, Blocked, Was Entered, Was mandatory)
    } TrackMetaData; // Lighter data that all a player needs to see

    typedef struct { // Data of each racer in a race

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

    typedef struct { // This is the track itself once loaded
        int id;
        int elevation[2500]; // format for all of this is
        int curve[2500];
        int left_width[2500];
        int right_width[2500];
    } TrackSimData;

    typedef struct {
        RaceRacerData racer[20];
        TrackSimData tracksimdata;
        int condition;
    } RaceSimData; //Local to Races only

// End of track and race data structs

// GAMEDATA an important struct holding all the most important data of the game

typedef struct {
    Racer trainee;
    Trainer trainer;
    Date date;
    Racer rival[50];
    RaceRacerData racer[20];
    TrackMetaData trackmetadata[30];
    int rain_chance;
} GameData; //All data that needs to be funneled out of the game.

// DIAGNOSTICS empty rn, probably holds diagnostic data, implement lest

typedef struct {
    int addmemberlater;
} Diagnostics;

// Function declarations

// Game functions
void initialize_game(GameData *gamedata); // God-initialize struct for anything needed to be initialized at the start of the game
void increment_turn(Date *date); // Increments turn by 1 and updates all date data

// Stat updaters
void update_racer_stat(Racer *racer, Pass stat_type, float modifier); //update_racer_stat(&racer, stat_type, modifier);
void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier); //update_trainer_stat(&trainer, stat_type, modifier);
void update_racer_name(Racer *racer, const char* input); //update_racer_name(&racer, input);
void update_trainer_name(Trainer *trainer, const char* input);

// Inpit handlers
void reset_inputs(MenuInputs *inputs);
int input_integer(int min, int max, int *input);
int input_character(char *input);
int round_up(float input);

#endif
