#ifndef GAMEHEADERS_H
#define GAMEHEADERS_H

/*
Hello GOATS, place your needed headers here so each file only uses "GameHeaders.h", for simpler coding.

Format for user-defined headers as such:

#include "header_name.h" // Hello this is a brief what header encapsulates

Deeper explanations can be inside the header itself. Thank you!

*/

// Standard library headers
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>
    #include <math.h>
    #include <ctype.h>
    #include <stdbool.h>

// User-defined headers

    #include "DataManager.h"        // Central Hub for all game data. Includes Data validation.
    #include "GenericFunctions.h"
    #include "blackjack.h"

// Menus
int main_blackjack(GameData *gamedata);

int main_action_hub_menu(GameData *gamedata);

int main_start_career_menu(GameData *gamedata);
int main_load_career_menu(GameData *gamedata);
int main_leaderboard_menu(GameData *gamedata);
int main_debug_menu(GameData *gamedata);

int main_start_menu(GameData *gamedata);

int main_example_menu(GameData *gamedata);





#endif
