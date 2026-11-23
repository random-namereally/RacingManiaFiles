#include "GameHeaders.h"

// Defines corresponding name for inputs available for the userq
typedef enum
{
    TEMP,
    Training,
    Resting,
    Infirmary,
    Recreation,
    Racing,
    MainMenu,
} CHOICES;

//Declaration of single file functions
static int execute (int choice, GameData *gamedata);
static void display (int min, int max, GameData *gamedata);

int main_action_hub_menu(GameData *gamedata)
{
    //Initializes variables of the menu
    int min = 1, max = 6;

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
        case Training:  return SceneTemplate;
        case Resting:  return SceneTemplate;
        case Infirmary:  return SceneTemplate;
        case Recreation:  return SceneTemplate;
        case Racing:  return SceneTemplate;
        case MainMenu:  return SceneTemplate;
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]");    return SceneError;
    }
}

static void display (int min, int max, GameData *gamedata)
{
    std_header("Action Hub");

    std_overview(gamedata);

    printf("Where to go:\n");
    printf("1. Training\n");
    printf("2. Rest\n");
    printf("3. Infirmary\n");
    printf("4. Recreation\n");
    printf("5. Race\n");
    printf("6. Main Menu\n");

    std_prompt("Integer", min, max);
}
