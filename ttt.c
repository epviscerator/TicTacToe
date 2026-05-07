#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    // Initialize Tic-tac-toe 2D array & other variables
    int intsquare[9];
    int truesquare[9];
    
    // Fill TTT arrays
    for (int i = 0; i < 9; i++) {
        intsquare[i] = i;
    }
    
    for (int i = 0; i < 9; i++) {
        truesquare[i] = 0; 
    }
    
    // Print it to test it/start
    for (int i = 0; i < 9; i++) {
        if ((i % 3) == 0) {
            printf(" \n");   
        }
        printf(" %d", intsquare[i]);
    }

    printf(" \n");

    // Loop until turn 10 (or 9 if you insist)
    for (int turn = 1; turn < 10; turn++) {
        // If turn is odd (x)
        if ((turn % 2) != 0) {
            int input;
            bool check_high;
            bool check_low;
            bool check_taken;
            bool ultimate_check;
            // Get input from player
            do {
                check_high = 1;
                check_low = 1;
                check_taken = 1;
                ultimate_check = 0;

                printf("\nPick your position (Player X): ");
                scanf("%d", &input);
                
                if ((input > 9)) {
                    printf("\nInvalid input! Choose a number between 0-8! (Too high!)");
                    printf("\n Number Chosen: %d", input);
                    check_high = 0;
                    
                }
                else if ((input < 0)) {
                    printf("\nInvalid input! Choose a number from 0-8! (Too low!)");
                    printf("\n Number Chosen: %d", input);
                    check_low = 0;
                }

                if ((truesquare[input] == 1) || (truesquare[input] == 2)) {
                    printf("\nThat spot's taken!");
                    check_taken = 0;
                }

                if (check_high == 1 && check_low == 1 && check_taken == 1) {
                    ultimate_check = 1;
                } else {
                    
                }
                
            } while (ultimate_check != 1);
                
            // Plug input into method
            truesquare[input] = 1;
            
        }
        
        // If turn is even (O)
        if ((turn % 2) == 0) {
            int input;
            bool check_high;
            bool check_low;
            bool check_taken;
            bool ultimate_check;
            // Get input from player
            do {
                check_high = 1;
                check_low = 1;
                check_taken = 1;
                ultimate_check = 0;

                printf("\nPick your position (Player O): ");
                scanf("%d", &input);
                
                if ((input > 9)) {
                    printf("\nInvalid input! Choose a number between 0-8! (Too high!)");
                    printf("\n Number Chosen: %d", input);
                    check_high = 0;
                    
                }
                else if ((input < 0)) {
                    printf("\nInvalid input! Choose a number from 0-8! (Too low!)");
                    printf("\n Number Chosen: %d", input);
                    check_low = 0;
                }

                if ((truesquare[input] == 1) || (truesquare[input] == 2)) {
                    printf("\nThat spot's taken!");
                    check_taken = 0;
                }

                if (check_high == 1 && check_low == 1 && check_taken == 1) {
                    ultimate_check = 1;
                }
                
            } while (ultimate_check != 1);
            // Plug input into method
            truesquare[input] = 2;
            
        }

        // Print the Tic Tac Toe square   
        for (int i = 0; i < 9; i++) {
            if ((i % 3) == 0) {
                printf(" \n");   
            }
            if (!(truesquare[i] == 1) && !(truesquare[i] == 2)) {
                printf("%d ", intsquare[i]);
            } else {
                if (truesquare[i] == 1) {
                    printf("X ");
                }

                if (truesquare[i] == 2) {
                    printf("O ");
                }
            }
                
        }
        
        printf(" \n");   

        // Check if there's 3 in a row
        // Top row
        if (truesquare[0] == 1 && truesquare[1] == 1 && truesquare[2] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[0] == 2 && truesquare[1] == 2 && truesquare[2] == 2) {
            printf("Victory for Player 2 (O)!!!");
            break;
        }
        // Middle row
        if (truesquare[3] == 1 && truesquare[4] == 1 && truesquare[5] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[3] == 2 && truesquare[4] == 2 && truesquare[5] == 2) {
            printf("Victory for Player 2 (O)!!!");
            break;
        }
        // Bottom row
        if (truesquare[6] == 1 && truesquare[7] == 1 && truesquare[8] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[6] == 2 && truesquare[7] == 2 && truesquare[8] == 2) {
            printf("Victory for Player 2 (O)!!!");
            break;
        }

        // Check if there's 3 in a column
        // Left column
        if (truesquare[0] == 1 && truesquare[3] == 1 && truesquare[6] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[0] == 2 && truesquare[3] == 2 && truesquare[6] == 2) {
            printf("Victory for Player 1 (O)!!!");
            break;
        }
        // Middle column
        if (truesquare[1] == 1 && truesquare[4] == 1 && truesquare[7] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[1] == 2 && truesquare[4] == 2 && truesquare[7] == 2) {
            printf("Victory for Player 1 (O)!!!");
            break;
        }
        // Right column
        if (truesquare[2] == 1 && truesquare[5] == 1 && truesquare[8] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[2] == 2 && truesquare[5] == 2 && truesquare[8] == 2) {
            printf("Victory for Player 1 (O)!!!");
            break;
        }


        // Check if there's 3 in a diagonal
        // Top left to bottom right
        if (truesquare[0] == 1 && truesquare[4] == 1 && truesquare[8] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[0] == 2 && truesquare[4] == 2 && truesquare[8] == 2) {
            printf("Victory for Player 1 (O)!!!");
            break;
        }
        // Top right to bottom left
        if (truesquare[2] == 1 && truesquare[4] == 1 && truesquare[6] == 1) {
            printf("Victory for Player 1 (X)!!!");
            break;
        }
        if (truesquare[2] == 2 && truesquare[4] == 2 && truesquare[6] == 2) {
            printf("Victory for Player 1 (O)!!!");
            break;
        }
      
    }

    return 0;
}