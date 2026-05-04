#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
int TTTinput(char arr[3][3], int pos, char team) {
    // Hard-coded because a tic-tac-toe box always only is a 3x3
    //har arr[3][3];
    int count = 0;

    switch(pos) {
        case 1:
            arr[0][0] = team;
            break;
        case 2:
            arr[0][1] = team;
            break;
        case 3:
            arr[0][2] = team;
            break;
        case 4:
            arr[1][0] = team;
            break;
        case 5:
            arr[1][1] = team;
            break;
        case 6:
            arr[1][2] = team;
            break;
        case 7:
            arr[2][0] = team;
            break;
        case 8:
            arr[2][1] = team;
            break;
        case 9:
            arr[2][2] = team;
            break;
        default:
            return -1;
    }



    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!(inputarr[i][j] == 'X') || !(inputarr[i][j] == 'O'))
                inputarr[i][j] = count;
                count++;
        }
    }

    inputarr = arr;

    return 1;
}
*/

//int TTTinput()

int main(void) {
    // Initialize Tic-tac-toe 2D array & other variables
    int intsquare[9];
    int truesquare[9];
    //char charsquare[9];
    //int turn = 1;
    //int count = 1;
    

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
    /*
    for (int i = 0; i < 9; i++) {
        if ((i % 3) == 0) {
            printf(" \n");   
        }
        printf(" %d", truesquare[i]); 
    }
    */
    //printf(" \n");

    // Loop until turn 10 (or 9 if you insist)
    for (int turn = 1; turn < 10; turn++) {
        // If turn is odd (x)
        if ((turn % 2) != 0) {
            int input;
            // Get input from player
            printf("\nPick your position (Player X): ");
            scanf("%d", &input);
            // Plug input into method
            truesquare[input] = 1;
            
        }
        
        // If turn is even (O)
        if ((turn % 2) == 0) {
            int input;
            // Get input from player
            printf("\nPick your position (Player O): ");
            scanf("%d", &input);
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