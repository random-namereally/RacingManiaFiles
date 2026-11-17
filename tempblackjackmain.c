#include "blackjack.h"

int main_blackjack(Gamedata *gamedata){
    rand_seed();
    BJscore score = initialize_bj_score();
    roll_dealer_dice(&score.dealertotal);
    roll_player_dice(&score.playertotal);
    roll_dealer_dice(&score.dealertotal);
    roll_player_dice(&score.playertotal);
    print_player_points(score);
    make_player_choice(&score);
    make_dealer_choice(&score);
    print_player_points(score);
    print_dealer_points(score);
    compare_player_dealer_total(&score);
}
