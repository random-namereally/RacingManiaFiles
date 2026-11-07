#ifndef GAME_STATE_H
#define GAME_STATE_H


// When pulling or pushing data you should use this so it's easier to read, rather than numbers which can work but may me illegible.
typedef enum
{
    num_current_energy,
    num_max_energy,
    num_mood,
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
}Pass;

typedef struct
 {
    // Name of trainee trainee
    char name[50];

    int current_energy;
    int max_energy;
    int mood;

    int speed;
    int stamina;
    int power;
    int guts;
    int wit;

    int speed_multiplier;
    int stamina_multiplier;
    int power_multiplier;
    int guts_multiplier;
    int wit_multiplier;

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
} Player;

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

void initialize_game(Player *trainee, Date *date);
void increment_turn(Date *date);

void update_trainee_stat(Player *trainee, Pass stat_type, int modifier);
void update_trainee_name(Player *trainee, char* input);

int get_trainee_stat(Player *trainee, Pass stat_type);
char* get_trainee_name(Player *trainee);

#endif
