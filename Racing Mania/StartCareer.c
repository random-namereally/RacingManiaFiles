#include "GameHeaders.h"

// Defines corresponding name for inputs available for the userq
typedef enum
{
    TEMP,
    StartMenu,
    NameTrainee,
    NameTrainer,
    StartGame,

} CHOICES;

//Declaration of single file functions
static void display_menu (int min, int max, GameData *gamedata, MenuInputs *input);
static void display_nameselect ();
static void display_confirm(int first_time, int, GameData *gamedata, MenuInputs *input);
static void get_input(int min, int max, GameData *gamedata, MenuInputs *input);
static int execute (MenuInputs *input, GameData *gamedata, int can_start);
static void name_entity(MenuInputs *input, GameData *gamedata, int mode);
static void confirm_name(GameData *gamedata, MenuInputs *input, int mode, int first_time);
static void adjust_empty(char* input, int);
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
    display_menu(min, max, gamedata, &input);

    //Input Validation and Execution
    std_get_int(min, max, &input, gamedata, display_menu, std_status_msg);
    return execute(&input, gamedata, can_start);
}

// Displays example menu
static void display_menu(int min, int max, GameData *gamedata, MenuInputs *input)
{

    std_header("Start Career");

    printf("1. Go back to main menu");

    printf("\n2. Choose trainee name");
            if(gamedata->trainee.is_trainee_named==1) {printf(" [Done]");}
            else printf(" [Required]");

    printf("\n3. Choose trainer name");
            if(gamedata->trainer.is_trainer_named==1) {printf(" [Done]");}
            else {printf(" [Required]");}

    printf("\n4. Start Game");
            if(gamedata->trainee.is_trainee_named+gamedata->trainer.is_trainer_named!=2)
            {printf(" [Locked]");}

    std_prompt("Selection", min, max);
}

static void display_nameselect()
{
    printf("\033[2J\033[H");

    std_header("Name Select");

    std_prompt("name", 0, 0);
}

// Executes validated choice
static int execute (MenuInputs *input, GameData *gamedata, int can_start)
{

    switch (input->choice)
    {
        case StartMenu:      return SceneStartMenu;
        case NameTrainee:    name_entity(input, gamedata, 1); return SceneStartCareer;
        case NameTrainer:    name_entity(input, gamedata, 2); return SceneStartCareer;
        case StartGame:
                            if(can_start==true){return SceneActionHub;}

                            printf("\n\nFinish Setup"); getflush(); return SceneStartCareer;
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]"); return SceneError;
    }
}

static void name_entity(MenuInputs *input, GameData *gamedata, int mode)
{
    int first_time = 1;
    while (input->confirm == 0)
    {
        display_nameselect();

        input->status = input_character(input->name); //Gets input from user, cleans then flags

        std_status_msg(0, 0, input->status);

        if (mode==1)
        {
            adjust_empty(input->name, 1);
            printf("The name of your uma is %s", input->name);
            getflush();
            confirm_name(gamedata, input, 1, first_time);
        }
        else
        {
            adjust_empty(input->name, 2);
            confirm_name(gamedata, input, 2, first_time);
            printf("\n1 [debug] choice=%d confirm=%d\n", input->choice, input->confirm);
            getflush();
        }
        first_time = 0;
        getflush();
    }



    if (mode==1)
    {
        update_racer_name(&gamedata->trainee, input->name);
        gamedata->trainee.is_trainee_named = 1;
    }
    else
    {
        update_trainer_name(&gamedata->trainer, input->name);
        gamedata->trainer.is_trainer_named = 1;
    }

    reset_inputs(input); // Reset inputs for reuse
}

static void adjust_empty(char* input, int mode)
{
    if (strlen(input)!=0) return;

    if (mode==1)
    {
        strcpy(input, "Great Taste Kopik O");
        input[strlen("Great Taste Kopik O")] = '\0';
    }
    if (mode==2)
    {
        strcpy(input, "Torena San");
        input[strlen("Torena San")] = '\0';
    }
}

static void confirm_name(GameData *gamedata, MenuInputs *input, int mode, int first_time)
{
    display_confirm(first_time, 0, gamedata, input);

    std_get_int(1, 2, input, gamedata, display_confirm, std_status_msg);

    if (input->choice == 2)  {input->confirm = 1;}
}

static void display_confirm(int first_time, int, GameData *gamedata, MenuInputs *input)
{
    printf("\033[2J\033[H");

    if (first_time) std_header("Confirm as name");
    else {std_header("Confirm new name");}

    printf("The name is %s\n\n", input->name);

    printf("1. Redo name\n");

    printf("2. Confirm name\n");

    std_prompt("Selection", 1, 2);
}


// Does a simple check if they have filled all data
static int game_requirements(Racer *trainee, Trainer *trainer)
{
    if(trainee->is_trainee_named==false) return false;
    if(trainer->is_trainer_named==false) return false;
    return true;
}

