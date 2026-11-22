#include "GameHeaders.h"
#include "GenericFunctions.h"

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
int std_get_int(int min, int max, MenuInputs *input, (*display)(int, int), (*status_msg)(int, int, int))
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
void std_status_msg(int min, int max, int status, int type)
{
    if (status==IntValid||status==CharValid) {return;}

    printf("\033[A");

        switch (status)
        {
        case IntInvalidTooHigh:         printf("[ERROR: Input must be lower than %d!]", max);               break;
        case IntInvalidTooLow:          printf("[ERROR: Input must be higher than %d!]", min);              break;
        case IntInvalidNotInteger:      printf("[ERROR: Input must be a whole number!]");                   break;
        case IntEOF:                    printf("[ERROR: End of input.]");                                   break;
        case CharTruncatedAndEmpty:     printf("[ERROR: Input was truncated and empty!]");                  break;
        case CharTruncated:             printf("[ERROR: Input must be at most %d characters!]", max);       break;
        case CharEmpty:                 printf("[ERROR: Input cannot be empty!]");                          break;
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
    if (min==0||max==0) {printf("Enter %s: ", prompt);}

}


