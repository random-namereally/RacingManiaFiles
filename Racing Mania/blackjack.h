#ifndef BLACKJACK_H
#define BLACKJACK_H

#define DECK_SIZE 11

typedef struct{
    int roll;
    }roller;

typedef struct{
    int playertotal;
    int dealertotal;
    }BJscore;

//for rolling the dealer's dice
void roll_dealer_dice(int *dealertotal);

//for rolling the player's dice
void roll_player_dice(int *playertotal);

//seeding random
void rand_seed(void);

//initializing blackjack score to zero
BJscore initialize_bj_score(void);

//showing current points for player
void print_player_points(BJscore);

//showing current points for dealer
void print_dealer_points(BJscore);

//makes player choose between hit or stand
void make_player_choice(BJscore *score);

#endif
