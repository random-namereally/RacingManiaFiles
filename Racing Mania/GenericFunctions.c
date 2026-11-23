#include "GameHeaders.h"

// Nothing on the stdout or stdin on our way out
// Also for pausing

MenuInputs input;


void getflush()
{
    //Hygiene o algo
    fflush(stdout);
    int c; while ((c = getchar()) != '\n' && c != EOF);
}

//Clears screen
void clear_screen()
{
    printf("\033[2J\033[H");
}

// Solana look at this function pointer... took me some tries... it's hard to understand
int std_get_int(int min, int max, MenuInputs *input, void (*display)(int, int), void (*status_msg)(int, int, int))
{
    while (1)
    {
        input->status = input_integer(min, max, &input->choice);

        // Valid means get out of this
        if (input->status == IntValid) return IntValid;
        if (input->status == CharValid) return CharValid;

        // EOF handler
        if (input->status == IntEOF) return IntEOF;
        if (input->status == CharEOF) return CharEOF;

        // Print error
        status_msg(min, max, input->status);
        display(min, max);
    }



}

//Prints message based on error number given
void std_status_msg(int min, int max, int status)
{
    if (status==IntValid||status==CharValid) {return;}

    printf("\033[A");

        switch (status)
        {
        case IntInvalidTooHigh:         printf("[ERROR: Input must be lower than %d!]", max);               break;
        case IntInvalidTooLow:          printf("[ERROR: Input must be higher than %d!]", min);              break;
        case IntInvalidNotInteger:      printf("[ERROR: Input must be a whole number!]");                   break;
        case IntEOF:                    printf("[ERROR: End of input.]");                                   break;
        case CharTruncatedAndEmpty:     printf("[Warning: Input was truncated for being longer than %d characters and empty!]", NAMESIZE-1);                  break;
        case CharTruncated:             printf("[Warning: Input was truncated for being longer than %d characters]", NAMESIZE-1);       break;
        case CharEmpty:                 printf("[Warning: Input was empty!]");                          break;
        case CharEOF:                   printf("[ERROR: End of input.]");                                   break;
        default:                        printf("[ERROR: Unknown input.]");                                  break;
        }

    getflush();
}

void std_header(const char *header) {
    printf("==================================================\n");
    printf("                %s      \n", header);
    printf("==================================================\n");
}

void std_prompt(const char *prompt, int min, int max) {
    if (min!=0||max!=0) {printf("Enter %s(%d-%d): ", prompt, min, max);}
    else if (min == 0 && max == 0) {printf("Enter %s: ", prompt);}
    else {printf("Error: neither character or integer selector go to function prompt()"); exit(1);}

}

void std_overview(GameData *gamedata)
{
    printf("Energy: %d/%d                   Turn 1    Year 1\n", gamedata->trainee.current_energy, gamedata->trainee.max_energy);
    printf("Mood: Happy                       Early Jan Winter\n\n");

    printf("GOAL: (3 turns) Reach 100 speed\n");
    printf("Spe: %d    Sta: %d    Pow: %d    Guts: %d   Wit: %d\n",
           gamedata->trainee.speed, gamedata->trainee.stamina, gamedata->trainee.power, gamedata->trainee.guts, gamedata->trainee.wit);
    printf("--------------------------------------------------\n");

}


