//For some reason, this code fails to work occasionally on C++, creating NUL signs. Please run it on https://www.onlinegdb.com/online_c++_debugger if this issue persists
//This is a project designed to accurately find the best possible move in a game of tic-tac-toe
#include <iostream>
using namespace std;

struct Move
{
    int row;
    int col;
};

char player = 'x';
char opponent = 'o';
//because the turn is not switching in this program, we must distinguish x and o

bool isMovesLeft(char space[3][3])
//boolean to check if there are moves left on the grid
{
    for (int i = 0; i<3; i++)
        //exact same code as seen in the game, where i is the row, which spans from 0-2, and j is the column.
        for (int j = 0; j<3; j++)
            if (space[i][j]=='_')
                //If there is a blank space left, then there are moves, thus this is a TRUE boolean.
                return true;
    //if there are no moves left:
    return false;

}



int evaluate(char space[3][3])
{
    // Checking for the status of the game; evaluation of the board
    for (int i = 0; i<3; i++)
        //giving the row number a value of 'i'
    {
        if((space[i][0]==space[i][1] && space[i][0]==space[i][2]) || (space[0][i]==space[1][i] && space[0][i]==space[2][i]))
        //checks for a vertical/horizontal tie, exact same boolean as seen in
        {
            //we only need to check for one row/column because this is assuming that they are all equal
            if (space[i][0]==player)
                //Essentially if the player has a winning space:
                return +10;
            //+10 meaning that their move will lead to a win
            //if the opponent is going to win
            else if (space[i][0]==opponent)
                //it is not good for the player
                return -10;
            {
                if (space[0][i]==player)
                    //same thing as above, but for horizontal wins
                    return +10;
                else if (space[0][i]==opponent)
                    return -10;
            }
        }
    }


    // Checking status of diagonal spaces
    if((space[0][0]==space[1][1] && space[1][1]==space[2][2]) || (space [0][2]==space[1][1] && space[1][1]==space[2][0]))
    {
        if (space[0][0]==player)
            //same thing as above, [0][0] is the first space in a diagonal tie
            return +10;
        else if (space[0][0]==opponent)
            return -10;
    }

    {
        if (space[0][2]==player)
            //first space in another diagonal tie
            return +10;
        else if (space[0][2]==opponent)
            return -10;
    }

    // Else if none of them have won then return 0
    return 0;
}

//the minimax function is already built in. It analyses the entire game board, and checks for every possible combination of the game.
//It can then give min and max values, and will be able to output the best possible move for you.
//in this case, the maximizer is 'x' and the minimizer is 'o'
int minimax(char space[3][3], int depth, bool isMax)
{
    int score = evaluate(space);
    //evaluates the entire board, and gives a total score

    //If the Maximizer wins
    //return the score
    if (score == 10)
        return score;

    // If Minimizer wins
    //Return the score
    if (score == -10)
        return score;

    // If it is a tie
    //return a score of 0, making it neater
    if (isMovesLeft(space)==false)
        return 0;

    // If the current player moving is 'x' (maximizer)
    if (isMax)
    {
        int best = -1000;
        // Check all squares in the grid
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if any square is empty
                if (space[i][j]=='_')
                {
                    //make a move to see the outcome
                    space[i][j] = player;

                    // Use minimax to choose
                    // the max value
                    best = max( best,
                                minimax(space, depth+1, !isMax) );

                    // Undo the previous move
                    space[i][j] = '_';
                }
            }
        }
        //gives the best possible outcome to the user
        return best;
    }

        // If this minimizer's move
    else
    {
        int best = 1000;

        // Check all possible squares, same as above
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Check if any square is empty
                if (space[i][j]=='_')
                {
                    // Make a move
                    space[i][j] = opponent;

                    // Use minimax to choose
                    // the min value
                    best = min(best,
                               minimax(space, depth+1, !isMax));

                    // Undo the previous move
                    space[i][j] = '_';
                }
            }
        }
        //give the best possible outcome
        return best;
    }
}

// This will return the best possible move for the user
Move findBestMove(char space[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;

    // Check all squares, evaluate each empty square using the minimax algorithm for
    // any empty squares. Return to the user the square with the best possible value

    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Check if any squares are empty first
            if (space[i][j]=='_')
            {
                // Then make a move, similar to above
                space[i][j] = player;

                // Evaluate the move
                int moveVal = minimax(space, 0, false);

                // Undo the move
                space[i][j] = '_';

                // If the current move has a higher value than the best possible value, then update the best value to match the current move, as well as the [i]
                // and [j] values
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }

    printf("The value of the best Move is : %d\n\n",
           bestVal);
    //then give the user the value of the best-case move

    return bestMove;
}

// Driver code
int main()
{
    cout<<"Please input the value ('x', 'o', or '_' at each space) \n";
    //ask the user for the value at each space of their board, which will then be checked to be used in the char space [3][3]
    char space1;
    printf("What was the value of space 1?: ");
    scanf("%s", &space1);
    printf("Space 1 reads: %s\n", &space1);
    (space1 != NULL);
    char space2;
    printf("What was the value of space 2?: ");
    scanf("%s", &space2);
    printf("Space 2 reads: %s\n", &space2);
    (space2 != NULL);
    char space3;
    printf("What was the value of space 3?: ");
    scanf("%s", &space3);
    printf("Space 3 reads: %s\n", &space3);
    (space3 != NULL);
    char space4;
    printf("What was the value of space 4?: ");
    scanf("%s", &space4);
    printf("Space 4 reads: %s\n", &space4);
    (space4 != NULL);
    char space5;
    printf("What was the value of space 5?: ");
    scanf("%s", &space5);
    printf("Space 5 reads: %s\n", &space5);
    (space5 != NULL);
    char space6;
    printf("What was the value of space 6?: ");
    scanf("%s", &space6);
    printf("Space 6 reads: %s\n", &space6);
    (space6 != NULL);
    char space7;
    printf("What was the value of space 7?: ");
    scanf("%s", &space7);
    printf("Space 7 reads: %s\n", &space7);
    (space7 != NULL);
    char space8;
    printf("What was the value of space 8?: ");
    scanf("%s", &space8);
    printf("Space 8 reads: %s\n", &space8);
    (space8 != NULL);
    char space9;
    printf("What was the value of space 9?: ");
    scanf("%s", &space9);
    printf("Space 9 reads: %s\n", &space9);
    (space9 != NULL);

    char space[3][3]={{space1, space2, space3},
                      {space4, space5, space6},
                      {space7, space8, space9}};
    //each space on the array above is gathered from the user's input. Any inputs which lead to no possible moves will give a negative output

    cout<< "     |     |     \n";
    cout<< "  "<<space[0][0]<<"  |  " <<space[0][1]<<   "  |  "<<space[0][2]<<"  \n";
    cout<< "_____|_____|_____\n";
    cout<< "     |     |     \n";
    cout<< "  "<<space[1][0]<<"  |  " <<space[1][1]<<   "  |  "<<space[1][2]<<"  \n";
    cout<< "_____|_____|_____\n";
    cout<< "     |     |     \n";
    cout<< "  "<<space[2][0]<<"  |  " <<space[2][1]<<   "  |  "<<space[2][2]<<"  \n";
    cout<< "     |     |     \n";
    cout<< "                 \n";
    cout<< "                 \n";
    
    //I also want to display the full grid to let the user check if they have the right game


    Move bestMove = findBestMove(space);
    //use findBestMove to give the user the optimal move
    printf("The Optimal Move is :\n\n");
    printf("ROW: %d COL: %d\n\n", bestMove.row,
           bestMove.col );
    return 0;
}
