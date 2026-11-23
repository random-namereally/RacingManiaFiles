#include "GameHeaders.h"

// Defines corresponding name for inputs available for the userq
typedef enum
{
    TEMP,
    choice1,
} CHOICES;

//Declaration of single file functions
static int execute (int choice, GameData *gamedata);
static void display (int min, int max, GameData *gamedata);

int main_example_menu(GameData *gamedata)
{
    //Initializes variables of the menu
    int min = 1, max = 1;

    //Initializes variables used for input validation
    MenuInputs input;
    reset_inputs(&input);

    //Clears previous screen then prints the menu
    printf("\033[2J\033[H");
    display (min, max, gamedata);

    //Input Validation and Execution
    std_get_int(min, max, &input, gamedata, display, std_status_msg);
    return execute(input.choice, gamedata);
}


// Executes validated choice
static int execute (int choice, GameData *gamedata)
{
    switch (choice)
    {
        case choice1:  return SceneTemplate;
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]");    return SceneError;
    }
}

static void display (int min, int max, GameData *gamedata)
{
    std_header("Example Menu");

    printf("1. menu choice\n");

    std_prompt("Integer", min, max);
}


