#include "GameHeaders.h"
#include "DataManager.h"
#include "Events.h"

void winter_events(GameData *gamedata){
    Racer *trainee = &gamedata->trainee;
    Trainer *trainer = &gamedata->trainer;
    if(gamedata->date.season == WINTER){
    int eventroll = {rand() % 5 + 1};
    switch(eventroll){
    case 1:
        printf("Low temperatures causes your trainee to catch a cold \n");
        update_racer_stat(trainee, NumStamina, -LOSE_STAT_SMALL);
        update_racer_stat(trainee, NumMood, -LOSE_STAT_SMALL);
        printf("-%d Stamina, -%d Speed \n", LOSE_STAT_SMALL);
        break;
    case 2:
        printf("Your trainee makes a snowman \n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_SMALL);
        printf("+%d Mood \n", GAIN_MOOD_SMALL);
        break;
    case 3:
        if(trainer->NumCash >= LOSE_CASH_BIG){
        printf("You buy your trainee new winter clothes \n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_BIG);
        update_racer_stat(trainer, NumCash, -LOSE_CASH_BIG);
        printf("+%d Mood, -%d Cash \n", GAIN_MOOD_BIG, LOSE_CASH_BIG);
        }else{
        printf("You try to buy your trainee new winter clothes but don't have enough cash\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 4:
        printf("Your Trainee suffers from frostbite \n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        update_racer_stat(trainee, NumSpeed, -LOSE_STAT_BIG);
        printf("-%d Mood, -%d Speed\n", LOSE_MOOD_BIG, LOSE_STAT_BIG);
        break;
    case 5"
        printf("The Trainee feels motivated to train harder to hit their goals");
        update_racer_stat(trainee, NumSpeed, GAIN_STAT_SMALL);
        update_racer_stat(trainee, NumGuts, GAIN_STAT_SMALL);
        update_racer_stat(trainee, NumWit, GAIN_STAT_SMALL);
        update_racer_stat(trainee, NumPower, GAIN_STAT_SMALL);
        printf("%d Speed, %d Guts, %d Wits, %d Power \n", GAIN_STAT_SMALL, GAIN_STAT_SMALL, GAIN_STAT_SMALL, GAIN_STAT_SMALL);
        break;
    }
}
}

void spring_events(GameData *gamedata){
    int eventroll = {rand() % 5 + 1};
    if(gamedata->date.season == SPRING){
    switch(eventroll){
    case 1:
        printf("The Trainee studies racing tactics on their spare time\n");
        update_racer_stat(trainee, NumWit, GAIN_STAT_SMALL);
        printf("+%d Wit \n", GAIN_STAT_SMALL);
        break;
    case 2:
        printf("Your trainee gives up on their new year's resolution \n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_SMALL);
        printf("-%d Mood \n", LOSE_MOOD_SMALL);
        break;
    case 3:
        if(trainer->NumCash >= LOSE_CASH_BIG){
        printf("You buy your trainee new spring clothes \n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_BIG);
        update_racer_stat(trainer, NumCash, -LOSE_CASH_BIG);
        printf("+%d Mood, -%d Cash \n", GAIN_MOOD_BIG, LOSE_CASH_BIG);
        }else{
        printf("You try to buy your trainee new spring clothes but don't have enough cash\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 4:
        if(trainer->NumCash >= LOSE_CASH_BIG){
        printf("Your Trainee Loses a Bet in a Casino\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        update_racer_stat(trainee, NumCash, -LOSE_CASH_BIG);
        printf("-%d Mood, -%d Cash\n", LOSE_MOOD_BIG, LOSE_CASH_BIG);
        }else{
        printf("Your Trainee goes to a casino but lacks cash to bet\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_SMALL);
        printf("-%d Mood \n", LOSE_MOOD_SMALL);
        }
        break;
    case 5"
        printf("The Trainee sleeps in instead of training");
        update_racer_stat(trainee, NumMood, GAIN_STAT_SMALL);
        update_racer_stat(trainee, NumGuts, -LOSE_STAT_SMALL);
        printf("%d Mood, -%d Guts \n", GAIN_STAT_SMALL, LOSE_STAT_SMALL);
        break;
    }
}
}


void summer_events(GameData *gamedata){
    int eventroll = {rand() % 5 + 1};
    if(gamedata->date.season == SUMMER){
    switch(eventroll){
    case 1:
        printf("The Trainee consumes cold treats\n");
        if(trainer->NumCash >= LOSE_CASH_SMALL){
        update_racer_stat(trainee, NumMood, GAIN_MOOD_SMALL);
        update_racer_stat(trainee, NumMood, LOSE_CASH_SMALL);
        printf("+%d Mood, -%d\n", GAIN_MOOD_SMALL, LOSE_CASH_SMALL);
        }else{
        printf("The Trainee craved cold treats but the cash was not there\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_SMALL);
        printf("-%d Mood \n", LOSE_MOOD_SMALL);
        }
        break;
    case 2:
        printf("Your trainee gets sunburned \n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_SMALL);
        printf("-%d Mood \n", LOSE_MOOD_SMALL);
        break;
    case 3:
        if(trainer->NumCash >= LOSE_CASH_BIG){
        printf("You buy your trainee new summer clothes \n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_BIG);
        update_racer_stat(trainer, NumCash, -LOSE_CASH_BIG);
        printf("+%d Mood, -%d Cash \n", GAIN_MOOD_BIG, LOSE_CASH_BIG);
        }else{
        printf("You try to buy your trainee new summer clothes but don't have enough cash\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 4:
        printf("Your Trainee goes to the Beach n");
        if(trainer->NumCash >= LOSE_CASH_BIG){
        update_racer_stat(trainee, NumMood, GAIN_MOOD_BIG);
        update_racer_stat(trainee, NumCash, -LOSE_CASH_BIG);
        printf("+%d Mood, -%d Cash\n", GAIN_MOOD_BIG, LOSE_CASH_BIG);
        }else{
        printf("The Trainee was midway through their beach get away planning but had to cancel due to lack of cash\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 5"
        printf("The Trainee Overheats on the track");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_SMALL);
        update_racer_stat(trainee, NumGuts, -LOSE_STAT_SMALL);
        printf("-%d Mood, -%d Stamina \n", LOSE_MOOD_SMALL, LOSE_STAT_SMALL);
        break;
    }
}
}


void fall_events(GameData *gamedata){
    int eventroll = {rand() % 5 + 1};
    if(gamedata->date.season == FALL){
    switch(eventroll){
    case 1:
        if(trainer->NumCash >= LOSE_CASH_SMALL){
        printf("The Trainee consumes specialty fall treats\n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_SMALL);
        update_racer_stat(trainee, NumMood, -LOSE_CASH_SMALL);
        printf("+%d Mood -%d\n", GAIN_MOOD_SMALL, LOSE_CASH_SMALL);
        }else{
        printf("The Trainee tried buying fall treats but realized their wallet was empty\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 2:
        if(trainer->NumCash >= LOSE_CASH_SMALL){
        printf("Your trainee attends a party \n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_SMALL);
        update_racer_stat(trainee, NumMood, LOSE_CASH_SMALL);
        printf("+%d Mood -%d\n", GAIN_MOOD_SMALL, LOSE_CASH_SMALL);
        }else{
        printf("The Trainee misses a party they were invited in due to lack of cash\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 3:
        if(trainer->NumCash >= LOSE_CASH_BIG){
        printf("You buy your trainee new fall clothes \n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_BIG);
        update_racer_stat(trainer, NumCash, -LOSE_CASH_BIG);
        printf("+%d Mood, -%d Cash \n", GAIN_MOOD_BIG, LOSE_CASH_BIG);
        }else{
        printf("You try to buy your trainee new fall clothes but don't have enough cash\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 4:
        if(trainer->NumCash >= LOSE_CASH_BIG){
        printf("Your Trainee goes leaf peeping n");
        update_racer_stat(trainee, NumMood, GAIN_MOOD_SMALL);
        update_racer_stat(trainee, NumGuts, GAIN_STAT_SMALL);
        update_racer_stat(trainee, NumCash, -LOSE_CASH_BIG);
        printf("+%d Mood, +%d Guts -%d Cash\n", GAIN_MOOD_SMALL, GAIN_STAT_SMALL LOSE_CASH_BIG);
        }else{
        printf("the Trainee wanted to go leaf peeping but don't have enough cash\n");
        update_racer_stat(trainee, NumMood, -LOSE_MOOD_BIG);
        printf("-%d Mood \n", LOSE_MOOD_BIG);
        }
        break;
    case 5"
        printf("The Trainee works hard for their goal");
        update_racer_stat(trainee, NumGuts, GAIN_STAT_BIG);
        update_racer_stat(trainee, NumPower, GAIN_STAT_SMALL);
        printf("+%d Guts, +%d Power \n", GAIN_STAT_BIG, GAIN_STAT_SMALL);
        break;
    }
}
}

