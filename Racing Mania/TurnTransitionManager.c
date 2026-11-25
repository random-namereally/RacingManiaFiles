#include "GameHeaders.h"

int main_post_turn_handler(GameData *gamedata)
{
increment_turn(&gamedata->date);

//run_events(GameData *gamedata) //TODO: make event structs

//check if goal met

return SceneActionHub;
}

static void run_mandatory_events(GameData *gamedata)
{
    // Does all eligible events

    /*for (int i = 0; i<100;i++) //100 is arbitrary
    {
        if (!mandatory[i].id) continue; // Reject if id shows 0 meaning empty
        if (!eligible(gamedata, i)) continue; // Reject if event is not eligible

        // If event can run
        process_event(gamedata,i) // Processes event
    }
    */
}

static void run_random_event(GameData *gamedata)
{
    /* while (1)
    {
        Note: "blank event" is in the random pool

        int i = rand()%100;
        if (!random[i].id) continue; // Reject if id shows 0 meaning empty
        if (!eligible(gamedata, i)) continue; // Reject if event is not eligible

        // If event can run
        process_event(gamedata,i) // Processes event

        break; // After event is done, break out of function
    }
    */

}

static void run_events(GameData *gamedata)
{
    run_mandatory_events(gamedata);
    run_random_event(gamedata);
}



