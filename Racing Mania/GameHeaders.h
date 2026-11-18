#ifndef GAMEHEADERS_H
#define GAMEHEADERS_H

/*
Hello GOATS, place your needed headers here so each file only uses "game_headers.h", for simpler coding.

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
    //#include <bool.h>



// User-defined headers
//  #include "header_name.h"     // Hello this is a brief of what header encapsulates

    #include "DataManager.h"        // Central Hub for all game data. Includes Data validation.
    #include "StartMenu.h"          // Starting menu of the game
    #include "TempHolder.h"         // Holding functions with no functionality or native file just yet.
    #include "StartCareer.h"        // For specifications of new career
    #include "Debug.h"
    #include "blackjack.h"

#endif
