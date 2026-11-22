#include "training.h"
#include "GameHeaders.h"

int main_training(GameData *gamedata){
    make_training_choice();
    getchar();
    return SceneStartMenu;
}
