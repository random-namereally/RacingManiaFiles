#include<stdio.h>
#include<stdlib.h>
#include"gamelogic.h"

void game_intro_1 ()
{

    printf("=== Welcome Torena to UmaMusume! ===  *pre-alpha*\n\n");

    printf("The trainee uma under your care is Jane Uma,\n you must train them for... 72 turns!\n\n");

    printf("Jane Uma: Neigh and horse noises o algo\n\n");

    printf("Press start to play the game."); scanf("%c");

    printf("\033[2J\033[H");


}

void overview_menu(Uma uma)
{
    int input;

    printf("=== Actions Menu ===\n\n");
    printf("Imagine game here\n");
    printf("\npress 99 to exit\n");

    while (1)
    {
        if (scanf("%d", &input) != 1) {
            printf("Type a number vro ToT\n");
            while (getchar() != '\n');
            continue;
        }

        switch (input)
        {
            case 1: training_menu_main(); break;
            case 2: break;
            case 99: printf("Exiting game now"); exit(0);
            default: printf("End of demo get out\n");
        }


    }


}

void training_menu_main()
{

}
