#include "GameHeaders.h"
#include "Events.h"

//Stub for events
void event_decider(GameData *gamedata){
    int eventroll = {rand() % 5 + 1};
    if(gamedata->date.season == 1){
    switch(eventroll){
    case 1:
        printf("Low temperatures causes your trainee to catch a cold \n");
        update_racer_stat(trainee, NumStamina, -10);
        update_racer_stat(trainee, NumMood, -1);
        printf("-1 Stamina, -10 Speed \n");
        break;
    case 2:
        printf("Your trainee plays makes a snowman \n");
        update_racer_stat(trainee, NumMood, 1);
        printf("+1 Mood \n");
        break;
    case 3:
        printf("You buy your trainee new winter clothes \n");
        update_racer_stat(trainee, NumMood, 2);
        update_racer_stat(trainer, NumCash, -20);
        printf("+2 Mood, -20 Cash \n");
        break;
    case 4:
        printf("Your Trainee suffers from frostbite \n");
        update_racer_stat(trainee, NumMood, -2);
        update_racer_stat(trainee, NumSpeed, -2);
        printf("-2 Mood, -2 Speed\n");
        break;
    case 5"
        printf("The Trainee feels motivated to train harder to hit their goals");
        update_racer_stat(trainee, NumSpeed, 1);
        update_racer_stat(trainee, NumGuts, 1);
        update_racer_stat(trainee, NumWit, 1);
        update_racer_stat(trainee, NumPower, 1);
        break;
    }
    }else if(gamedata->date.season == 2){

}
}
