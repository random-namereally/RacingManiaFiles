#include "GameHeaders.h"

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

static int execute (int choice, GameData *gamedata);
static void display(int min, int max, GameData *gamedata);

int main_start_menu(GameData *gamedata)
{
    int min = 1, max = 6;
    MenuInputs input;
    reset_inputs(&input);

    clear_screen();
    display(min, max, gamedata);

    int status = std_get_int(min, max, &input, gamedata, display, std_status_msg);
    if (status == IntEOF) return SceneError;

    return execute(input.choice, gamedata);
}

static void display(int min, int max, GameData *gamedata)
{
    std_header("RACING MANIA");



    printf("1. Start New Career\n");
    printf("2. Load Ongoing Career\n");
    printf("3. View Leaderboard\n");
    printf("4. Debug and options\n");
    printf("5. Blackjack\n");
    printf("6. Quit Game                                   %s\n", GAME_VERSION);

    std_prompt("selection", min, max);
}

static int execute (int choice, GameData *gamedata)
{
    switch (choice)
    {
        case StartCareer:                                                                       return SceneStartCareer;
        case LoadCareer:                                                                        return SceneLoadCareer;
        case ViewLeaderboard:                                                                   return SceneViewLeaderboard;
        case Debug:                                                                             return SceneDebug;
        case Blackjack:                                                                         return SceneBlackjack;
        case ExitGame:                                                                          return SceneExitGame;
        default: printf("\n\n[Error: No code to execute. Check execute() or min and max?]");    return SceneError;
    }
}
