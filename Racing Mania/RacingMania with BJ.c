#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

typedef struct {
    char name[50];

    int energy;
    int mood;

    int speed;
    int stamina;
    int power;
    int guts;
    int wit;
} Uma;

void game_intro_1 ();
void training_menu_main(Uma uma);

int main ()
{
    Uma Jane = {"Jane Uma", 100, 5, 50, 50, 50, 50, 50};

    game_intro_1();
    training_menu_main(Jane);
}

void game_intro_1 ()
{

    printf("=== Welcome Torena to UmaMusume! ===  *pre-alpha*\n\n");

    printf("The trainee uma under your care is Jane Uma,\n you must train them for... 72 turns!\n\n");

    printf("Jane Uma: Neigh and horse noises o algo\n\n");

    printf("Press start to play the game."); scanf("%c");

    printf("\033[2J\033[H");


}

void training_menu_main(Uma uma)
{
    int input;

    printf("=== Training Menu ===\n\n");
    printf("Imagine game here\n");
    printf("\npress 1 to exit\n");

    while (1)
    {
        if (scanf("%d", &input) != 1) 
        {
            printf("Type a number vro ToT\n");
            while (getchar() != '\n');
            continue;
        }

        switch (input)
        {
            case 1: printf("Exiting game now"); exit(0);
            default: printf("End of demo get out\n");
        }


    }


}
