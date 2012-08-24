//
//  main.c
//  Tic-Tac-Toe
//
//  Created by Mohammad El-Abid on 8/19/12.
//  Copyright (c) 2012 Mohammad El-Abid. All rights reserved.
//

#include <stdio.h>

#define BLANK 0
#define TIE 1
#define X 3
#define O 5

char board[3][3];

void clearBoard()
{
  char i, j;
  for (i = 0; i < 3; i++)
    for (j = 0; j < 3; j++)
      board[i][j] = 0;
}

void clearGetChar()
{
    // getchar() gives you one character at a time.
    // so 123 whould need to use getchar() three times.
    // however, when the user selects a spot they type
    // in "1\n" so we need to clear the upto the \n
    // so we don't get it in the next userInput()
    char last = getchar();
    while( last != '\n' ) // until we reach the \n
        last = getchar(); // load the next character
}

char markerFor(char x, char y)
{
    // load the current 'mark' (X, O, BLANK) of this position
    char mark = board[x][y];
    
    // if it is X or O, return with their character.
    if ( mark == X )
        return 'X';
    else if ( mark == O )
        return 'O';
    else
    {
        // if it isn't X or Y, we need to find out the
        // numerical value of this position.
        
        // We now that each row holds 3 and that x starts
        // at zero, so for the first row x * 3 = 0 and
        // the 2nd row x * 3 = 3.
        
        // The y is just an offset within that X, so the
        // middle spot (5) is in the second row (x * 3) = 3
        // and in the second spot, which in an array index
        // is only 1, so we end up with four. Since we want
        // to count up from one instead of zero, we add one.
        
        char num = (x * 3) + y + 1;
        
        // Because we want to display this character, we have
        // to return it's position in the ASCII table. Since
        // all chars are numbers (index in ASCII table) and
        // numbers 0-9 are ASCII (but 10 is not, it's 1 and 0)
        // and sequential in the table, we can just add to the
        // value of '0' or add it to '1' and drop the +1 above. 
        return '0' + num;
    }
}

void displayBoard()
{
    char i;
    for ( i = 0; i < 3; i++ ) // loop over the rows
    {
        // assign a pointer so we can write the code quicker
        // this is the "x | y | z" format
        printf("%c | %c | %c\n", markerFor(i, 0), markerFor(i, 1), markerFor(i, 2));
        // if we're not in the last row, output a border
        if ( i != 2 )
            printf("--+---+--\n");
    }
}

char* nameFor(char marker)
{
    if ( marker == X )
        return "X";
    else if ( marker == O )
        return "O";
    else if ( marker == BLANK )
        return "blank";
    else if ( marker == TIE )
        return "tie";
    else
        return "???";
}

void userInput(char marker)
{
    // C does not have a boolean type, so we'll use a char with 0 and 1
    char played = 0;
    // until they have picked a valid spot
    while ( played == 0)
    {
        // we're going to tell the players whoes move it is
        printf("%s, it's your move.\n", nameFor(marker));
        // show them the board
        displayBoard();
        // and ask them where the want to go.
        printf("\nI'll take spot: ");
        
        // we subtract by '0' to get the integral value
        // we then remove one because our index starts at 0
        char spot = getchar() - '0' - 1;
        // because there are three spots in a row and we're
        // starting at zero (so 3rd spot is (2/3) = 0) we
        // can simply divide by 3 to get the x coordinate.
        char x = (spot / 3);
        // the y coordinate is going to be the reminader of
        // spots not used in the x cordinate. So we'll use
        // the modulas operator to give us the remainder.
        char y = (spot % 3);
        
        /*
        // getchar() gives you one character at a time.
        // so 123 whould need to use getchar() three times.
        // however, when the user selects a spot they type
        // in "1\n" so we need to clear the upto the \n
        // so we don't get it in the next userInput()
        char last = getchar();
        while( last != '\n' ) // until we reach the \n
            last = getchar(); // load the next character
         */
        clearGetChar();
        
        // now, before we attempt to access the array, we need
        // to make sure that the x and y coordinates are in an
        // acceptable range, 0-3. Then before we make the move
        // we need to make sure nothing is there. Otherwise
        // it's an invalid move.
        if ( x < 3 && x >= 0 && y < 3 && y >= 0 && board[x][y] == BLANK )
        {
            board[x][y] = marker;
            played = 1; // set to "true" to brake the loop
        }
        else
            printf("\nInvalid move, please try again.\n");
    }
}

char winner()
{
    // first lets check the rows of the board, left to right
    char i;
    for ( i = 0; i < 3; i++ )
        // if the first one isn't blank and all of them are
        // the same makrer
        if ( (board[i][0] != BLANK) && (board[i][0] == board[i][1]) && (board[i][1] == board[i][2]) )
            return board[i][0]; // return the marker

    // now lets check the columns, top to bottom
    for ( i = 0; i < 3; i++ )
        // we'll use the same strategy
        if ( (board[0][i] != BLANK) && (board[0][i] == board[1][i]) && (board[1][i] == board[2][i]) )
            return board[0][i];
    
    // now for the diagonals
    // we'll start from top left to bottom right
    if( (board[0][0] != BLANK) && (board[0][0] == board[1][1]) && (board[1][1] == board[2][2]) )
        return board[1][1];
    
    // and bottom left to top right
    if ( (board[2][0] != BLANK) && (board[2][0] == board[1][1]) && (board[1][1] == board[0][2]))
        return board[1][1];
    
    // make sure we haven't used the entire board yet
    char count = 0;
    for ( i = 0; i < 3; i++ )
    {
        char j;
        for ( j = 0; j < 3; j++ )
        {
            if ( board[i][j] != BLANK )
                count++;
        }
    }
    if ( count >= 9 )
        return TIE;
            
    
    // if we haven't reached a winner yet, return 0 for 'false'
    return 0;
}

int main(int argc, const char * argv[])
{
    char playing = 'y';
    char player = X;
    
    while( playing == 'y' )
    {
        clearBoard(); // ensure the board is BLANK
    
        while ( winner() == 0 ) // while there isn't a winner
        {
            userInput(player); // ask a player to play
            player = (player == X) ? O : X; // switch players
        }
        
        char result = winner(); // get the winner
        if ( result == TIE ) // if the winner was "TIE"
            printf("Ouch, no winners here.\n");
        else // X or O won
            printf("Congratulations %s, you're the winner!\n\n", nameFor(result));
        
        displayBoard(); // show them their board
        
        printf("Want to play again? (y/n) ");
        playing = getchar(); // we're looping on this being 'y' so anything else quits
        clearGetChar();
    }
}