#include "GameHeaders.h"




// Defines corresponding name for inputs available for the user
typedef enum
{
    TEMP,
    StartCareer,
    LoadCareer,
    ViewHighscore,
    Debug,
    ExitGame,
    Error,
} CHOICES;

//Declaration of single file functions
static void display_menu ();
static void get_input(int min, int max, MenuInputs *input);
static void execute (int *choice);
static void print_error(int min, int max, int *status);

void main_start_menu()
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
    execute(&input.choice);

    //Player must be out of the menu by then.
    input.choice = Error;
    execute(&input.choice);
}

// Displays example menu
static void display_menu(int min, int max)
{


    printf("==================================================\n");

    printf("                RACING MANIA      \n");

    printf("==================================================\n");

    printf("1. Start New Career\n");

    printf("2. Load Ongoing Career\n");

    printf("3. View Highscores\n");

    printf("4. Options\n");

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
        print_error(min, max, &input->status);
        printf("\033[2J\033[H");
        display_menu(min, max);
    }
    while (input->status != IntValid);
}

// Executes validated choice
static void execute (int *choice)
{
    switch (*choice)
    {
        case StartCareer:   main_start_career_menu();                                   break;
        case LoadCareer:    main_load_career_menu();                                    break;
        case ViewHighscore: main_highscore_menu();                                      break;
        case Debug:         main_debug_menu();                                        break;
        case ExitGame:      printf("\033[2J\033[HThanks for playing!\n"); exit(0);               break;
        case Error: printf("\n\n[Error: End of menu. Exiting program]"); exit(1);
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]"); break;
    }
}

//Prints message based on error number given
static void print_error(int min, int max, int *status)
{

    if (*status==IntValid) {return;}
    printf("\033[A");
    if (*status==IntInvalidTooHigh) {printf("[ERROR: Input must be lower than %d!]", max);}
    if (*status==IntInvalidTooLow) {printf("[ERROR: Input must be higher than %d!]", min);}
    if (*status==IntInvalidNotInteger) {printf("[ERROR: Input must be a whole number!]");}
    if (*status==IntInvalidExceededLimit) {printf("[ERROR: Input crashed input buffer!]");}
    while (getchar() != '\n');
}
