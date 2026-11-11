/*DEPRECATED SINGLE FILE FOR THE MINIGAME, DELETE ONCE THE ACTUAL MAIN FOR RACING MANIA IS CREATED
AND LINKED WITH THE BLACKJACK MINIGAME*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define deck 11

typedef struct{
    int roll;
    }roller;

typedef struct{
    int playertotal;
    int dealertotal;
    }BJscore;
/*
//for rolling the dice
void rolldice(int *dealertotal, int *playertotal);
*/
void roll_dealer_dice(int *dealertotal);

//for rolling the player's dice
void roll_player_dice(int *playertotal);

//seeding random
void rand_seed(void);

//initializing blackjack score to zero
BJscore initialize_bj_score(void);

//showing current points for dealer and player
void print_points(BJscore);

int main(){
    rand_seed();
    BJscore score = initialize_bj_score();
/*
    rolldice(&score.dealertotal, &score.playertotal);
    rolldice(&score.dealertotal, &score.playertotal);
*/
    roll_dealer_dice(&score.dealertotal);
    roll_player_dice(&score.playertotal);
    print_points(score);
}

/*
void rolldice(int *dealertotal, int *playertotal)
{
    roller dealer = {rand() % deck + 1};
    roller player = {rand() % deck + 1};
    printf("Dealer rolled: %d \n", dealer.roll);
    printf("You rolled: %d \n", player.roll);
    *playertotal += player.roll;
    *dealertotal += dealer.roll;
    printf("HOLD, RAISE, PUSH, FOLD \n");
}
*/

void roll_player_dice(int *playertotal){
    roller player = {rand() % deck + 1};
    printf("You rolled: %d \n", player.roll);
    *playertotal += player.roll;
    printf("HOLD, RAISE, PUSH, FOLD \n");
}

void roll_dealer_dice(int *dealertotal){
    roller dealer = {rand() % deck + 1};
    printf("Dealer rolled: %d \n", dealer.roll);
    *dealertotal += dealer.roll;
}

void rand_seed(void){
    srand((unsigned int)time(NULL));
}

BJscore initialize_bj_score(void){
    BJscore score;
    score.playertotal = 0;
    score.dealertotal = 0;
    return score;
}

void print_points(BJscore score){
    printf("Dealer points: %d \n", score.dealertotal);
    printf("Player points: %d \n", score.playertotal);
}

