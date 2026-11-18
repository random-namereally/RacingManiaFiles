#include "GameHeaders.h"

// Defines corresponding name for inputs available for the userq
typedef enum
{
    TEMP,
    NameTrainee,
    NameTrainer,
    StartMenu,
    Error,

} CHOICES;

//Declaration of single file functions
static void display_menu (int min, int max, int is_trainer_named, int is_trainee_named);
static void get_input(int min, int max, int is_trainer_named, int is_trainee_named, MenuInputs *input);
static int execute (int *choice, GameData *gamedata);
static void err_msg(int min, int max, int *status);
//void name_trainee();
void name_trainer();

int main_start_career_menu(GameData *gamedata)
{
    //Initializes variables of the menu
    int min = 1, max = 5, is_trainer_named = 0, is_trainee_named = 0;

    //Initializes variables used for input validation
    MenuInputs input;
    reset_inputs(&input);

    //Clears previous screen then prints the menu
    printf("\033[2J\033[H");
    display_menu (min, max, is_trainer_named, is_trainee_named);

    //Input Validation and Execution
    get_input(min, max, is_trainer_named, is_trainee_named, &input);
    return execute(&input.choice, gamedata);

    //Out of bounds catcher
    return SceneError;
}

// Displays example menu
static void display_menu(int min, int max, int istrainernamed, int istraineenamed)
{


    printf("==================================================\n");

    printf("                START CAREER      \n");

    printf("==================================================\n");

    printf("1. Choose trainee name"); if(istraineenamed==1) {printf(" [done]");}

    printf("\n2. Choose trainer name"); if(istrainernamed==1) {printf(" [done]");}

    printf("\n3. Go back to main menu\n");

    printf("Enter selection (%d-%d): ", min, max);

}

// Gets input for the menu with validation. WARNING: INTEGER INPUTS ONLY
static void get_input(int min, int max, int is_trainer_named, int is_trainee_named, MenuInputs *input)
{
    do
    {
        input->status = input_integer(min , max,&input->choice);
        err_msg(min, max, &input->status);
        printf("\033[2J\033[H");
        display_menu(min, max, is_trainer_named, is_trainee_named);
    }
    while (input->status != IntValid);
}

// Executes validated choice
static int execute (int *choice, GameData *gamedata)
{
    switch (*choice)
    {
        case NameTrainee:    //name_trainee(); return SceneStartCareer;                                       break;
        case NameTrainer:    name_trainer(); return SceneStartCareer;                                      break;
        case StartMenu:      return SceneStartMenu;                                     break;
        case Error: printf("\n\n[Error: End of menu. Exiting program]"); exit(1);
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]");break;
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

// void name_trainee(char input, int *istraineenamed)
//{
    //while (input.confirm==0){
    //input_character(*input);
    //confirm_character(*input);
    //update_trainee_name(Racer racer, char *input)
    //}

    //if(input.confirm==1) istraineenamed=1;

//}

void name_trainer()
{
    //update_trainer_name(Trainer *trainer, char *input)
}
