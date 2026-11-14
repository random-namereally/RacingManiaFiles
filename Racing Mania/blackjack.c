#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"

void roll_player_dice(int *playertotal){
    roller player = {rand() % deck_size + 1};
    printf("You rolled: %d \n", player.roll);
    if(player.roll == 11 && *playertotal + player.roll > 21){
        printf("To prevent busting your ace is converted to 1");
        *playertotal += 1;
    }else{
        *playertotal += player.roll;
    }
}

void roll_dealer_dice(int *dealertotal){
    roller dealer = {rand() % deck_size + 1};
    printf("Dealer rolled: %d \n", dealer.roll);
    if(dealer.roll == 11 && *dealertotal + dealer.roll > 21){
        *dealertotal += 1;
    }else{
        *dealertotal += dealer.roll;
    }
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

void print_player_points(BJscore score){
    printf("Player points: %d \n", score.playertotal);
}

void print_dealer_points(BJscore score){
    printf("Dealer points: %d \n", score.dealertotal);
}
void make_player_choice(BJscore *score){
    char playerchoice = '0';
    printf("HIT, STAND \n");
    printf("1 = HIT, 2 = STAND \n");
    while(1){
        scanf(" %c", &playerchoice);
        while (getchar() != '\n');
    if(playerchoice == '1'){
        roll_player_dice(&score->playertotal);
        break;
    }else if(playerchoice == '2'){
        break;
    }else{
        printf("Please enter a valid input \n");
    }
}
}
