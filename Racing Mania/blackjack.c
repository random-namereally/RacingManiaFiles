#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "GameHeaders.h"


void roll_player_dice(int *playertotal){
    roller player = {rand() % DECK_SIZE + 1};
    printf("You rolled: %d \n", player.roll);
    if(player.roll == 11 && *playertotal + player.roll > 21){
        printf("To prevent busting your ace is converted to 1 \n");
        *playertotal += 1;
    }else{
        *playertotal += player.roll;
    }
}

void roll_dealer_dice(int *dealertotal){
    roller dealer = {rand() % DECK_SIZE + 1};
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
        scanf(" %1c", &playerchoice);
        while (getchar() != '\n');
    if(playerchoice == '1'){
        roll_player_dice(&score->playertotal);
        if(score->playertotal == 21){
                playerchoice = '2';
                break;
        }
        if(score->playertotal > 21){
                playerchoice = '2';
                break;
        }
        print_player_points(*score);
    }else if(playerchoice == '2'){
        break;
    }else{
        printf("\nPlease enter a valid input \n");
    }
}
}

void make_dealer_choice(BJscore *score){
    while(score->dealertotal < 17){
        roll_dealer_dice(&score->dealertotal);
        if(score->dealertotal == 21){
                break;
        }
        if(score->dealertotal > 21){
                break;
        }
    }
}

void compare_player_dealer_total(BJscore *score, GameData *gamedata){
    if(score->playertotal > 21){
        printf("The Player has lost \n");
        printf("-%d Mood, %d Cash\n", MOOD_PENALTY, PENALTY);
        update_trainer_stat(&gamedata->trainer, NumCash, PENALTY);
        update_racer_stat(&gamedata->trainee, NumMood, -MOOD_PENALTY);
    }else if(score->playertotal == 21){
        printf("The Player has won");
        printf("%d Mood, %d Cash\n", MOOD_GAIN, PRIZE);
        update_trainer_stat(&gamedata->trainer, NumCash, PRIZE);
        update_racer_stat(&gamedata->trainee, NumMood, MOOD_GAIN);
    }else if(score->dealertotal > 21){
        printf("The Dealer has lost");
        update_trainer_stat(&gamedata->trainer, NumCash, PRIZE);
        update_racer_stat(&gamedata->trainee, NumMood, MOOD_GAIN);
    }else if(score->dealertotal == 21){
        printf("The Dealer has won");
        printf("-%d Mood, %d Cash\n", MOOD_PENALTY, PENALTY);
        update_trainer_stat(&gamedata->trainer, NumCash, PENALTY);
        update_racer_stat(&gamedata->trainee, NumMood, -MOOD_PENALTY);
    }else if(score->playertotal > score->dealertotal){
        printf("the Player has won\n");
        printf("%d Mood, %d Cash\n", MOOD_GAIN, PRIZE);
        update_trainer_stat(&gamedata->trainer, NumCash, PRIZE);
        update_racer_stat(&gamedata->trainee, NumMood, MOOD_GAIN);
    }else if(score->playertotal == score->dealertotal){
        printf("The match ends in a draw\n");
    }else{
        printf("The Dealer has won\n");
        printf("-%d Mood, %d Cash\n", MOOD_PENALTY, PENALTY);
        update_trainer_stat(&gamedata->trainer, NumCash, PENALTY);
        update_racer_stat(&gamedata->trainee, NumMood, -MOOD_PENALTY);
}
}
