#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define deck 11

typedef struct{
    int roll;
    }roller;
void rolldice(int *, int *);
int main(){
    srand((unsigned int)time(NULL));
    int playertotal = 0;
    int dealertotal = 0;
    rolldice(&dealertotal, &playertotal);
    rolldice(&dealertotal, &playertotal);
    if(dealertotal <= 19){

    }else
{

}
}
//for rolling the dice
void rolldice(int *dealertotal, int *playertotal)
{
    roller dealer = {rand() % deck + 1};
    roller player = {rand() % deck + 1};
    printf("Dealer rolled: %d \n", dealer.roll);
    printf("You rolled: %d \n", player.roll);
    *playertotal += player.roll;
    *dealertotal += dealer.roll;
    printf("Dealer points: %d \n", *dealertotal);
    printf("Player points: %d \n", *playertotal);
    printf("HOLD, RAISE, PUSH, FOLD \n");
}
