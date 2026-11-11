#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define deck_size 11

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

//showing current points for dealer and player
void print_points(BJscore);

//makes player choose between hit or stand
void make_player_choice(BJscore *score);

int main(){
    rand_seed();
    BJscore score = initialize_bj_score();

    roll_dealer_dice(&score.dealertotal);
    roll_player_dice(&score.playertotal);
    roll_dealer_dice(&score.dealertotal);
    make_player_choice(&score);
    print_points(score);
}

void roll_player_dice(int *playertotal){
    roller player = {rand() % deck_size + 1};
    printf("You rolled: %d \n", player.roll);
    *playertotal += player.roll;
}

void roll_dealer_dice(int *dealertotal){
    roller dealer = {rand() % deck_size + 1};
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

void make_player_choice(BJscore *score){
    char playerchoice = '0';
    printf("HIT, STAND \n");
    printf("1 = HIT, 2 = STAND \n");
    while(1){
        scanf(" %c", &playerchoice);
    if(playerchoice == '1'){
        roll_player_dice(&score->playertotal);
        break;
    }else if(playerchoice == '2'){
        break;
    }else{
        printf("Please enter a valid input \n");
        scanf(" %c", &playerchoice);
    }
}
}
