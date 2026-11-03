#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "gamelogic.h"

int main ()
{
    Uma Jane = {"Jane Uma", 100, 5, 50, 50, 50, 50, 50};

    game_intro_1();
    overview_menu(Jane);
}
