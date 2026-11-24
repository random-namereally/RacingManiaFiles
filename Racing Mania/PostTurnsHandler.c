#include "GameHeaders.h"

int main_post_turn_handler(GameData *gamedata)
{

//run_events(GameData *gamedata)


// while (event gives no event)
//rand eventhandle(); something that continues running until it hits an event
// one of the events is just /no event/ to prevent loop
// endwhile
increment_turn(&gamedata->date);

//check if goal met

//srand



return SceneActionHub;
}

static void run_mandatory_events(GameData *gamedata)
{

}

static void run_random_event(GameData *gamedata)
{

}

static void run_events(GameData *gamedata)
{
    run_mandatory_events(gamedata);
    run_random_event(gamedata);
}



