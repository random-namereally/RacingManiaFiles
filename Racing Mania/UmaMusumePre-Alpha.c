#include <stdio.h>

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

int main ()
{
    Uma Jane = {"Jane Uma", 100, 5, 50, 50, 50, 50, 50};

    printf("=== Welcome Torena to UmaMusume! ===  *pre-alpha*\n\n");

    printf("The trainee uma under your care is Jane Uma,\n you must train them for... 72 turns!\n\n");

    printf("Jane Uma: Neigh and horse noises o algo\n\n");

    printf("Press start to play the game."); scanf("%c");

    printf("\033[2J\033[H");

    printf("printf(=== Welcome Torena to UmaMusume! ===  *pre-alpha*\n\n);");

}
