#ifndef GAMELOGIC_H
#define GAMELOGIC_H

typedef struct
 {
    char name[50];

    int energy;
    int mood;

    int speed;
    int stamina;
    int power;
    int guts;
    int wit;
} Uma;

typedef struct {
    int turn;
    int biweek;
    int month;
    int season;
    int year;
} Date;

void game_intro_1 ();
void overview_menu(Uma uma);
void training_menu_main();

#endif // GAMELOGIC_H
