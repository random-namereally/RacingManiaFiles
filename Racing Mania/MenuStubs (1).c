#include "GameHeaders.h"

// check this code


// Shared screen: prints a title and waits until the user picks "1"
static int simple_back_menu(const char *title)
{
    int choice = 0, status;

    do
    {
        printf("\033[2J\033[H");
        printf("==================================================\n");
        printf("                %s\n", title);
        printf("==================================================\n");
        printf("1. Back to main menu\n");
        printf("--------------------------------------------------\n");
        printf("Enter selection (1-1): ");

        status = input_integer(1, 1, &choice);
        if (status == IntEOF) return SceneStartMenu;
    }
    while (status != IntValid);

    return SceneStartMenu;
}

int main_debug_menu(GameData *gamedata)
{
    (void)gamedata;                 // unused for now
    return simple_back_menu("DEBUG MENU");
}

int main_leaderboard_menu(GameData *gamedata)
{
    (void)gamedata;                 // unused for now
    return simple_back_menu("HIGH SCORES");
}
