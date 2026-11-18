#include "GameHeaders.h"




// Defines corresponding name for inputs available for the user
typedef enum
{
    TEMP,
    StartCareer,
    LoadCareer,
    ViewLeaderboard,
    Debug,
    Blackjack,
    ExitGame,
    Error,
} CHOICES;

//Declaration of single file functions
static void display_menu ();
static void get_input(int min, int max, MenuInputs *input);
static int execute (int *choice, GameData *gamedata);
static void err_msg(int min, int max, int *status);

int main_start_menu(GameData *gamedata)
{
    //Initializes variables of the menu
    int min = 1, max = 5;

    //Initializes variables used for input validation
    MenuInputs input;
    reset_inputs(&input);

    //Clears previous screen then prints the menu
    printf("\033[2J\033[H");
    display_menu (min, max);

    //Input Validation and Execution
    get_input(min, max, &input);
    return execute(&input.choice, gamedata);

    // Out of bounds catcher
    return SceneError;
}

// Displays example menu
static void display_menu(int min, int max)
{


    printf("==================================================\n");

    printf("                RACING MANIA      \n");

    printf("==================================================\n");

    printf("1. Start New Career\n");

    printf("2. Load Ongoing Career\n");

    printf("3. View Leaderboard\n");

    printf("4. Debug and options\n");

    printf("5. Blackjack\n");

    printf("5. Quit Game                                   %s\n", GAME_VERSION);

    printf("--------------------------------------------------\n");
    printf("Enter selection (%d-%d): ", min, max);

}

// Gets input for the menu with validation. WARNING: INTEGER INPUTS ONLY
static void get_input(int min, int max, MenuInputs *input)
{
    do
    {
        input->status = input_integer(min,max,&input->choice);
        err_msg(min, max, &input->status);
        printf("\033[2J\033[H");
        display_menu(min, max);
    }
    while (input->status != IntValid);
}

// Executes validated choice
static int execute (int *choice, GameData *gamedata)
{
    switch (*choice)
    {
        case StartCareer:       return SceneStartCareer;
        case LoadCareer:        return SceneLoadCareer;
        case ViewLeaderboard:   return SceneViewLeaderboard;
        case Debug:             return SceneDebug;
        case Blackjack:         return SceneBlackjack;
        case ExitGame:      printf("\033[2J\033[HThanks for playing!\n"); exit(0);               break;
        case Error: printf("\n\n[Error: End of menu. Exiting program]"); exit(1);
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]"); break;
    }
}

//Prints message based on error number given
static void err_msg(int min, int max, int *status)
{

    if (*status==IntValid) {return;}
    printf("\033[A");
    if (*status==IntInvalidTooHigh) {printf("[ERROR: Input must be lower than %d!]", max);}
    if (*status==IntInvalidTooLow) {printf("[ERROR: Input must be higher than %d!]", min);}
    if (*status==IntInvalidNotInteger) {printf("[ERROR: Input must be a whole number!]");}
    if (*status==IntInvalidExceededLimit) {printf("[ERROR: Input crashed input buffer!]");}
    while (getchar() != '\n');
}
