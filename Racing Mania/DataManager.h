#ifndef GAME_STATE_H
#define GAME_STATE_H

// Game version for flair
#define GAME_VERSION "v1.0"

// When pulling or pushing data you should use this so it's easier to read, rather than numbers which can work but may me illegible.
typedef enum
{
    num_current_energy,
    num_max_energy,
    num_mood,
    num_display_speed,
    num_display_stamina,
    num_display_power,
    num_display_guts,
    num_display_wit,
    num_speed,
    num_stamina,
    num_power,
    num_guts,
    num_wit,
    num_speed_mult,
    num_stamina_mult,
    num_power_mult,
    num_guts_mult,
    num_wit_mult,
    num_frontrunner_affinity,
    num_pacechaser_affinity,
    num_latesurger_affinity,
    num_endcloser_affinity,
    num_dirt_affinity,
    num_turf_affinity,
    num_sprint_affinity,
    num_mile_affinity,
    num_medium_affinity,
    num_long_affinity,
    num_popularity,
    num_fans,
    num_display_fans,
    num_display_cash,
    num_display_debt,
    num_display_debt_limit,
    num_display_credit_score,
    num_cash,
    num_debt,
    num_debt_limit,
    num_credit_score,
}Pass;

typedef enum
{
    int_valid,
    int_invalid_not_number,
    int_invalid_too_low,
    int_invalid_too_high,
    int_invalid_other,

}InputValidity;

typedef struct
 {
    // Name of racer racer
    char name[50];

    int current_energy;
    int max_energy;
    int mood;

    int display_speed;
    int display_stamina;
    int display_power;
    int display_guts;
    int display_wit;

    float speed;
    float stamina;
    float power;
    float guts;
    float wit;

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
    float display_fans;
} Racer;

typedef struct
 {
    char name[50];

    int display_cash;
    int display_debt;
    int display_debt_limit;
    int display_credit_score;

    float cash;
    float debt;
    float debt_limit;
    float credit_score;

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

void update_racer_stat(Racer *racer, Pass stat_type, int modifier);
void update_trainer_stat(Trainer *trainer, Pass stat_type, int modifier);
void update_racer_name(Racer *racer, char* input);
void update_trainer_name(Trainer *trainer, char* input);

int get_racer_stat(Racer *racer, Pass stat_type);
char* get_racer_name(Racer *racer);

int get_trainer_stat(Trainer *trainer, Pass stat_type);
char* get_trainer_name(Trainer *trainer);

int input_integer(int min, int max, int *input);
void reset_inputs(MenuInputs *inputs);

#endif
