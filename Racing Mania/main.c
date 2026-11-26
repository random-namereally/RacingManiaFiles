#include "GameHeaders.h"

int main ()
{
    GameData gamedata;
    rand_seed();
    initialize_game(&gamedata);


  int current_scene = SceneStartMenu;
  while(1)
  {
    switch (current_scene)
    {
    case SceneStartMenu:            current_scene = main_start_menu         (&gamedata); break;
    case SceneStartCareer:          current_scene = main_start_career_menu  (&gamedata); break;
    //case SceneLoadCareer:         current_scene = main_load_career_menu   (&gamedata); break;
    //case SceneViewLeaderboard:    current_scene = main_leaderboard_menu   (&gamedata); break;
    case SceneDebug:                current_scene = main_debug_menu         (&gamedata); break;
    case SceneBlackjack:            current_scene = main_blackjack          (&gamedata); break;
    case SceneError:                exit(1);                                             break;
    case SceneExitGame:             clear_screen(); printf("Thanks for playing!\n Press Enter to Quit\n"); getchar(); exit(0); break;
    case SceneActionHub:            current_scene = main_action_hub_menu    (&gamedata); break;
    case SceneTrainingHub:          current_scene = main_training           (&gamedata); break;
    //case SceneEnding:             current_scene = ending_screen           (&gamedata); break;
    default:                        exit(1);                                             break;
    }
  }

}
