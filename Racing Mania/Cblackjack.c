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

//for rolling the dice
void rolldice(int *, int *);

//seeding random
void rand_seed(void);

//initializing blackjack score to zero
BJscore initialize_bj_score(void);

int main(){
    rand_seed();
    BJscore score = initialize_bj_score();
    rolldice(&score.dealertotal, &score.playertotal);
    rolldice(&score.dealertotal, &score.playertotal);
}

void rolldice(int *dealertotal, int *playertotal)
{
    roller dealer = {rand() % deck + 1};
    roller player = {rand() % deck + 1};
    printf("Dealer rolled: %d \n", dealer.roll);
    printf("You rolled: %d \n", player.roll);
    *playertotal += player.roll;
    *dealertotal += dealer.roll;
    printf("Dealer points: %d \n", *dealertotal);
    printf("Player points: %d \n", *playertotal);
    printf("HOLD, RAISE, PUSH, FOLD \n");
}

void rand_seed(void){
    srand((unsigned int)time(NULL));
}

BJscore initialize_bj_score(){
    BJscore score;
    score.playertotal = 0;
    score.dealertotal = 0;
    return score;
}
