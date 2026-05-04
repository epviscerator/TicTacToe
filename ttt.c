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
            // Get input from player
            do {
                printf("\nPick your position (Player X): ");
                scanf("%d", &input);
                
                if ((input > 9)) {
                    printf("\nInvalid input! Choose a number between 1-8! (Too high!)");
                    printf("\n Number Chosen: %d", input);
                    continue;
                }
                else if ((input < 0)) {
                    printf("\nInvalid input! Choose a number between 1-8! (Too low!)");
                    printf("\n Number Chosen: %d", input);
                }
                else if ((truesquare[input] == 1) && (truesquare[input] == 2)) {
                    printf("\nThat spot's taken!");
                }
                
            } while ((input < 0) && (input > 9) && (truesquare[input] != 1) && (truesquare[input] != 2));
                
            // Plug input into method
            truesquare[input] = 1;
            
        }
        
        // If turn is even (O)
        if ((turn % 2) == 0) {
            int input;
            // Get input from player
            
            do {
                printf("\nPick your position (Player X): ");
                scanf("%d", &input);

                if ((truesquare[input] == 1) && (truesquare[input] == 2)) {
                    printf("\nThat spot's taken!");
                }
                else if ((input > 9)) {
                    printf("\nInvalid input! Choose a number between 1-8! (Too high!)");
                    printf("\n Number Chosen: %d", input);
                }
                else if ((input < 0)) {
                    printf("\nInvalid input! Choose a number between 1-8! (Too low!)");
                    printf("\n Number Chosen: %d", input);
                }

            } while ((truesquare[input] != 1) && (truesquare[input] != 2) && (input < 0) && (input > 9));
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
            
    }
        
        // Test print code for true square
        for (int i = 0; i < 9; i++) {
            if ((i % 3) == 0) {
                printf(" \n");   
            }
            printf("%d ", truesquare[i]);
        
        // Check if there's 3 in a row
            // PX WINS!!!
    }

        

        
    
    return 0;
}