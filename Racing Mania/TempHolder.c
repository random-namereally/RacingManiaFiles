#include "GameHeaders.h"

// Defines corresponding name for inputs available for the userq
typedef enum
{
    TEMP,
    choice1,
    Error,
} CHOICES;

//Declaration of single file functions
static void display_menu (int min, int max);
static void get_input(int min, int max, MenuInputs *input);
static int execute (int choice, GameData *gamedata);
static void err_msg(int min, int max, int status);

int main_example_menu(GameData *gamedata)
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
    return execute(input.choice, gamedata);

    //Out of bounds catcher
    return SceneError;
}

// Displays example menu
static void display_menu(int min, int max)
{


    printf("==================================================\n");

    printf("                Menu name      \n");

    printf("==================================================\n");

    printf("1. menu choice\n");

    printf("Enter selection (%d-%d): ", min, max);

}

// Gets input for the menu with validation. WARNING: INTEGER INPUTS ONLY
static void get_input(int min, int max, MenuInputs *input)
{
    do
    {
        input->status = input_integer(min , max,&input->choice);
        err_msg(min, max, input->status);
        printf("\033[2J\033[H");
        display_menu(min, max);
        if (input->status == IntEOF) return;
    }
    while (input->status != IntValid);
}

// Executes validated choice
static int execute (int choice, GameData *gamedata)
{
    switch (choice)
    {
        case TEMP:  /* return Temp */
        case Error: printf("\n\n[Error: End of menu. Exiting program]");                        return SceneError;
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]");    return SceneError;
    }
}

//Prints message based on error number given
static void err_msg(int min, int max, int status)
{


    if (status==IntValid) {return;}
    printf("\033[A");
    switch (status)
    {
    case IntInvalidTooHigh:       printf("[ERROR: Input must be lower than %d!]", max);  break;
    case IntInvalidTooLow:        printf("[ERROR: Input must be higher than %d!]", min); break;
    case IntInvalidNotInteger:    printf("[ERROR: Input must be a whole number!]");      break;
    case IntEOF:                  printf("[ERROR: End of input.]");                      break;
    default:                      printf("[ERROR: Unknown input.]");                     break;
    }

    fflush(stdout);
    int c; while ((c = getchar()) != '\n' && c != EOF);
}


//unimplemented code, not part of template
int main_load_career_menu(GameData *gamedata){}
int main_leaderboard_menu(GameData *gamedata){}
int main_options_menu(){}

