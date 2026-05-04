#include <stdio.h>
#include <stdlib.h>
#include <string.h>


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
/*
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!(inputarr[i][j] == 'X') || !(inputarr[i][j] == 'O'))
                inputarr[i][j] = count;
                count++;
        }
    }

    inputarr = arr;
*/
    return 1;
}



int main(void) {
    // Initialize Tic-tac-toe 2D array & other variables
    int intsquare[3][3];
    char charsquare[3][3];
    //int turn = 1;
    int count = 1;
    

    // Fill TTT array
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            intsquare[i][j] = count;
            count++;
        }
    }

    // Print it to test it/start
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %d", intsquare[i][j]);

        }
        printf(" \n");
    }

    // Loop until turn 10 (or 9 if you insist)
    for (int turn = 1; turn < 10; turn++) {
        // If turn is odd:
            // P1 (X) turn
        if ((turn % 2) != 0) {
            //printf("%d", turn);
            int input;
            // Get input from player
            printf("Pick your position (Player X): ");
            scanf("%d", &input);
            // Plug input into method
            TTTinput(charsquare, input, 'X');
            
        }
        
        // If turn is even
            // P2 (O) turn
        if ((turn % 2) == 0) {
            int input;
            //printf("%d", turn);
            // Get input from player
            printf("Pick your position (Player O): ");
            scanf("%d", &input);
            // Plug input into method
            TTTinput(charsquare, input, 'O');
            
        }

        // Test print code for char square
        
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                printf("%d", charsquare[i][j]);

            }
            printf(" \n");
        }
        
        // Print the Tic Tac Toe square
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (!(charsquare[i][j] == 'X') || !(charsquare[i][j] == 'O')) {
                    printf("%d", intsquare[i][j]);
                } else {
                    printf("%c", charsquare[i][j]);
                }
                
            }
        printf(" \n");
        }

        // Check if there's 3 in a row
            // PX WINS!!!
    }

        

        
    
    return 0;
}