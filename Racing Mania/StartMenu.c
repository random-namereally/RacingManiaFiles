#include "GameHeaders.h"

void main_start_menu()
{
    MenuInputs input;
    reset_inputs(&input);

    game_intro_1 ();

    do
    {
        printf("\033[2J\033[H");
        display_start_menu();
        input.status = input_integer(1,2,&input.choice);
    }
    while (input.status != int_valid);
}

void game_intro_1 ()
{

    printf("=== Welcome Torena to UmaMusume! ===  *pre-alpha*\n\n");

    printf("The trainee uma under your care is Jane Uma,\n you must train them for... 72 turns!\n\n");

    printf("Jane Uma: Neigh and horse noises o algo\n\n");

    printf("Press start to play the game."); scanf("%c");

    printf("\033[2J\033[H");
}

void display_start_menu ()
{


        printf("==================================================\n");

        printf("                RACING MANIA      \n");

        printf("==================================================\n");

        printf("1. Start New Career\n");

        printf("2. Load Ongoing Career\n");

        printf("3. View Highscores\n");

        printf("4. Options\n");

        printf("5. Quit Game                                    %s\n", GAME_VERSION);

        printf("--------------------------------------------------\n");
        printf("Enter selection (1-4): ");
}

