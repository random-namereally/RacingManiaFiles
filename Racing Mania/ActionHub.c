#include<stdio.h>
#include<stdlib.h>
#include"GameHeaders.h"
#include"ActionHub.h"

int overview_menu(Trainer trainer)
{
    int input;

    printf("=== Actions Menu ===\n\n");
    printf("Imagine game here\n");
    printf("\npress 99 to exit\n");

    while (1)
    {
        if (scanf("%d", &input) != 1) {
            printf("Type a number vro ToT\n");
            while (getchar() != '\n');
            continue;
    }

        switch (input)
        {
            case 1: //training_menu_main(); break;
            case 2: break;
            case 99: printf("Exiting game now"); exit(0);
            default: printf("End of demo get out\n");
        }


    }


}


