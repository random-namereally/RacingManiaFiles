#include "GameHeaders.h"

// Defines corresponding name for inputs available for the userq
typedef enum
{
    TEMP,
    StartMenu,
    NameTrainee,
    NameTrainer,
    StartGame,
    Error,

} CHOICES;

//Declaration of single file functions
static void display_menu (int min, int max, int is_trainer_named, int is_trainee_named, int mode);
static void get_input(int min, int max, int is_trainer_named, int is_trainee_named, MenuInputs *input);
static int execute (MenuInputs *input, GameData *gamedata, int can_start);
static void err_msg(int min, int max, int status);
static void name_trainee(MenuInputs *input, Racer *trainee);
static void name_trainer(MenuInputs *input, Trainer *trainer);
static int game_requirements(Racer *trainee, Trainer *trainer);

int main_start_career_menu(GameData *gamedata)
{
    //Initializes variables of the menu
    int min = 1, max = 4;

    //Initializes variables used for input validation
    MenuInputs input;
    reset_inputs(&input);

    //Update requirement
    int can_start=game_requirements(&gamedata->trainee, &gamedata->trainer);

    //Clears previous screen then prints the menu
    printf("\033[2J\033[H");
    display_menu (min, max, gamedata->trainer.is_trainer_named, gamedata->trainee.is_trainee_named, 1);

    //Input Validation and Execution
    get_input(min, max, gamedata->trainer.is_trainer_named, gamedata->trainee.is_trainee_named, &input);
    return execute(&input, gamedata, can_start);

    //Out of bounds catcher
    return SceneError;
}

// Displays example menu
static void display_menu(int min, int max, int is_trainer_named, int is_trainee_named, int mode)
{

switch (mode)
{
case 1:
    printf("==================================================\n");

    printf("                START CAREER      \n");

    printf("==================================================\n");

    printf("1. Go back to main menu");

    printf("\n2. Choose trainee name"); if(is_trainee_named==1) {printf(" [done]");}

    printf("\n3. Choose trainer name"); if(is_trainer_named==1) {printf(" [done]");}

    printf("\n4. Start Game"); if(is_trainee_named+is_trainer_named!=2) {printf(" [Finish setup first]");}
    printf("\n--------------------------------------------------");
    printf("\nEnter selection (%d-%d): ", min, max);
break;

case 2:
    printf("\033[2J\033[H");

    printf("==================================================\n");

    printf("                NAME SELECT      \n");

    printf("==================================================\n");

    printf("Enter name: ");
break;
}



}

// Gets input for the menu with validation. WARNING: INTEGER INPUTS ONLY
static void get_input(int min, int max, int is_trainer_named, int is_trainee_named, MenuInputs *input)
{
    do
    {
        input->status = input_integer(min , max,&input->choice);
        err_msg(min, max, input->status);
        printf("\033[2J\033[H");
        display_menu(min, max, is_trainer_named, is_trainee_named, 1);
        if (input->status == IntEOF) return;
    }
    while (input->status != IntValid);
}

// Executes validated choice
static int execute (MenuInputs *input, GameData *gamedata, int can_start)
{

    switch (input->choice)
    {
        case StartMenu:      return SceneStartMenu;
        case NameTrainee:    name_trainee(input, &gamedata->trainee); return SceneStartCareer;
        case NameTrainer:    name_trainer(input, &gamedata->trainer); return SceneStartCareer;
        case StartGame:
                            if(can_start==true){return SceneActionHub;}

                            printf("\n\nFinish Setup Dawg"); int c; while ((c = getchar()) != '\n' && c != EOF); return SceneStartCareer;

        case Error: printf("\n\n[Error: End of menu. Exiting program]"); return SceneError;
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]"); return SceneError;
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


static void name_trainee(MenuInputs *input, Racer *trainee)
{
    while (input->confirm==0)
    {
    display_menu(0, 0, 0, 0, 2);

    input_character(input->name); //Gets input from user, cleans then flags

    //name_adjust(input->name, 1); // Adjusts name, give placeholder

    printf("The name of your uma is %s", input->name); // Placeholder from debug lmao
    fflush(stdout);
    int c; while ((c = getchar()) != '\n' && c != EOF);
//    confirm_character(input->name, pass); //
    update_racer_name(trainee, input->name);

input->confirm = 1;                        // temporary: until confirm is done
    }
    trainee->is_trainee_named=1;

    reset_inputs(input); // Reset inputs for reuse

}

static void name_trainer(MenuInputs *input, Trainer *trainer)
{
    while (input->confirm==0)
    {
    display_menu(0,0,0,0, 2);

    input_character(input->name); //Gets input from user, cleans then flags

//  name_adjust(input->name, 2); // Adjusts name, give placeholder

    printf("The name of your trainer is %s ", input->name);
    fflush(stdout);
    int c; while ((c = getchar()) != '\n' && c != EOF);
//    confirm_character(input->name, pass); //
    update_trainer_name(trainer, input->name);
input->confirm = 1;                        // temporary: until confirm is done type shi
    }

    trainer->is_trainer_named=1;

    reset_inputs(input); // Reset inputs for reuse
}


// Does a simple check if they have filled all data
static int game_requirements(Racer *trainee, Trainer *trainer)
{
    if(trainee->is_trainee_named==false) return false;
    if(trainer->is_trainer_named==false) return false;
    return true;
}

