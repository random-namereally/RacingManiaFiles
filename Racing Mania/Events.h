#include "GameHeaders.h"
#include "DataManager.h"

#ifndef EVENTS_H
#define EVENTS_H
//Stub for now, but will be filled so dont delete

#define GAIN_STAT_SMALL 1

#define GAIN_STAT_BIG 2

#define LOSE_STAT_SMALL 1

#define LOSE_STAT_BIG 2

#define GAIN_CASH_SMALL 10

#define GAIN_CASH_BIG 20

#define LOSE_CASH_SMALL 10

#define LOSE_CASH_BIG 20

#define GAIN_MOOD_SMALL 1

#define GAIN_MOOD_BIG 2

#define LOSE_MOOD_SMALL 1

#define LOSE_MOOD_BIG 2

#define WINTER 1

#define SPRING 2

#define SUMMER 3

#define FALL 4

//checks if it is winter and makes a roll for the event
void winter_events(GameData *gamedata);

//checks if it is spring and makes a roll for the event
void spring_events(GameData *gamedata);

//checks if it is summer and makes a roll for the event
void summer_events(GameData *gamedata);

//checks if it is fall and makes a roll for the event
void fall_events(GameData *gamedata);

#endif
