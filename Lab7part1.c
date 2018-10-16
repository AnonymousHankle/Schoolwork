#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void initialization(int n, char*board);
void printBoard(char*board, int n);
bool move(char*board);
bool positionInBounds(int size, char row, char col);
bool checkLegalInDirection(char*board, int size, char row, char col, 
char colour, int deltaCol, int deltaRow);
bool checkLegal(char*board, int n, char row, char col, 
char colour);
void flip(char*board, int size,char colour, char row, char col);
int checkAvailability(char*board, char*availableMove, int size, char colour);
void computerMove(char*board, char*availableMove, int size, char colour); 
int countScore(char*board, int size, char colour);

int main()
{
    char board[26][26];
    char availableMove[676][3];
    int size = 0;
    bool det = true;
    char row, col, colour;
    int intRow = 0, intCol = 0, moveAvailable = 0;
    printf("Enter the board dimension: ");
    scanf(" %d", &size);
	initialization(size, board);
    printBoard(board, size);
    /**
    printf("Enter the board configuration:\n");
    while (det) {
        det = move(board);
    }
    printBoard(board, size);
    **/
    printf("Computer plays (B/W): ");
    scanf(" %c", &colour);
    while (checkAvailability(board, availableMove, size, 'B') || checkAvailability(board, availableMove, size, 'W')) {
        if (colour == 'B') {
            if (checkAvailability(board, availableMove, size, 'B') == 0) {
                printf("B player has no valid move. \n");
                if (checkAvailability(board, availableMove, size, 'W') == 0) {
                    break;
                }
            } else {
                computerMove(board, availableMove, size, colour);
            }
            if (checkAvailability(board, availableMove, size, 'W') == 0) {
                printf("W player has no valid move. \n");
                if (checkAvailability(board, availableMove, size, 'B') == 0) {
                    break;
                }
            } else {
                printf("Enter move for colour W (RowCol): ");
                scanf(" %c%c", &row, &col);
                if (!(checkLegal(board, size, row, col, 'W') && positionInBounds(size, row, col))) {
                    printf("Invalid move.\n");
                    break;
                }
                flip(board, size, 'B', row, col);
            }
        } else if (colour == 'W') {
            }
            if (checkAvailability(board, availableMove, size, 'B') == 0) {
                if (checkAvailability(board, availableMove, size, 'W') == 0) {
                    break;
                }
                printf("B player has no valid move. \n");
            } else {
                printf("Enter move for colour B (RowCol): ");
                scanf(" %c%c", &row, &col);
                if (!(checkLegal(board, size, row, col, 'B') && positionInBounds(size, row, col))) {
                    printf("Invalid move.\n");
                    break;
                }
                flip(board, size, 'B', row, col);
                printBoard(board, size);
            }
            if (checkAvailability(board, availableMove, size, 'W') == 0) {
                if (checkAvailability(board, availableMove, size, 'B') == 0) {
                    break;
                }
                printf("W player has no valid move. \n");
            } else {
                computerMove(board, availableMove, size, colour);
            }
        }
            if (countScore(board, size, 'W') > countScore(board, size, 'B')) {
                printf("W player wins. \n");
            } else if (countScore(board, size, 'W') < countScore(board, size, 'B')) {
                printf("B player wins. \n");
            } else {
                printf("Draw!\n");
            }
    
    
    /**
        printf("Available move for W: \n");
        moveAvailable = checkAvailability(board, availableMove, size, 'W');
        int i = 0;
        while (i < moveAvailable) {
            printf("%c%c\n",availableMove[i][0], availableMove[i][1]);
            i = i + 1;
        }
        printf("Available move for B: \n");
        moveAvailable = checkAvailability(board, availableMove, size, 'B');
        i = 0;
        while (i < moveAvailable) {
            printf("%c%c\n",availableMove[i][0], availableMove[i][1]);
            i = i + 1;
        }
        **/
        /**
        char colour;
        printf("Enter a move: \n");
        scanf(" %c", &colour);
        scanf("%c", &row);
        scanf("%c",&col);
        intRow = row - 'a';
        intCol = col - 'a';
        det = checkLegal(board, size,row, col, colour);
        if (det == true && positionInBounds(size,row,col)) {
            board[intRow][intCol] = colour;
            flip(board,size,colour,row,col);
            printBoard(board,size);
        } else {
            printf("Invalid Move.\n");
            printBoard(board,size);
        }
        **/
	return 0;
}

/**
 * @brief Initial a 26 by 26 array representing the board
 * @param n dimention of board
 */
void initialization(int n, char*board) {
    int row = 0, col = 0;
    while (row < n) {
        while (col < n) {
            *(board + row * 26 + col) = 'U';
            col = col + 1;
        }
        row = row + 1;
        col = 0;
    }
    // Initialize starting tiles
    *(board + ((n / 2) - 1) * 26 + (n / 2) - 1) = 'W';
    *(board + (n / 2) * 26 + (n / 2) - 1) = 'B';
    *(board + ((n / 2) - 1) * 26 + (n / 2)) = 'B';
    *(board + (n / 2) * 26 + (n / 2)) = 'W'; 
}

/**
 * @brief scan three inputs from user representing colour, row, column of the move respectively
 * @param board pointer of the start of the array
 * @return whether three inputs are '!!!'
 */
bool move(char*board) {
    char colour, row, column;
    scanf(" %c", &colour);
    scanf("%c", &row);
    scanf("%c",&column);
    int intRow = 0, intColumn = 0;
    intRow = row - 'a';
    intColumn = column - 'a';
    *(board + intRow * 26 + intColumn) = colour;
    return (!(colour == '!' && row == '!' && column == '!'));
}

/**
 * @brief 
 * @param board pointer of the start the array 
 * @param n size of thhe board
 */
void printBoard(char*board, int n) {
    int row = 0, col = 0;
    printf("  ");
    while (col < n) {
        printf("%c", 'a' + col);
        col = col + 1;
    }
    while (row < n) {
        col = 0;
        printf("\n");
        printf("%c ", 'a' + row);
        while (col < n) {
            printf("%c", *(board + row * 26 + col));
            col = col + 1;
        }
        row = row + 1;
    }
    printf("\n");
}

/**
 * @brief Check whether a move is within the boundary of the board
 * @param size size of the board
 * @param row row of the move
 * @param col column of the move
 * @return whether it is in the boundary of the board
 */
bool positionInBounds(int size, char row, char col){
    int intRow = 0, intColumn = 0;
    intRow = row - 'a';
    intColumn = col - 'a'; 
    return (intRow < size && intColumn < size && intRow >= 0 && intColumn >= 0);
    
}

/**
 * @brief Check whether a move is legal
 * @param board pointer of the address of start of array
 * @param size size of the array
 * @param row row of the move
 * @param col column of the move
 * @param colour colour of the tile
 * @return whether the move is legal
 */
bool checkLegalInDirection(char*board, int n, char row, char col, 
char colour, int deltaCol, int deltaRow) {
    char curTile;
    int intRow = 0, intCol = 0, counter = 0;
    // Checking the straight line direction 
    if ((deltaCol == 0 || deltaRow == 0) && deltaCol != deltaRow ) {
        if (deltaCol == 0) {
            do {
                row = row + deltaRow;
                intRow = row - 'a';
                intCol = col - 'a';
                curTile = *(board + intRow * 26 + intCol);
                counter = counter + 1;
                if (curTile == colour && counter == 1) {
                    return false;
                }
                if (curTile == 'U') {
                    return false;
                }
            } while ((curTile != colour) && positionInBounds(n, row, col));
            return curTile == colour;
        }
        if (deltaRow == 0) {
            do {
                col = col + deltaCol;
                intCol = col - 'a';
                intRow = row - 'a';
                curTile = *(board + intRow * 26 + intCol);
                counter = counter + 1;
                if (curTile == colour && counter == 1) {
                    return false;
                }
                if (curTile == 'U') {
                    return false;
                }
            } while ((curTile != colour) && positionInBounds(n, row, col));
        return curTile == colour;
        }
        
    }
    //  Checking the diagonal direction
    else if (!(deltaCol == 0 && deltaRow == 0)) {
        do {
            col = col + deltaCol;
            row = row + deltaRow;
            intRow = row - 'a';
            intCol = col - 'a';
            curTile = *(board + intRow * 26 + intCol);
            counter = counter + 1;
            if (curTile == colour && counter == 1)  {
                return false;
            }
            if (curTile == 'U') {
                return false;
            }
        } while ((curTile != colour) && positionInBounds(n, row, col));
        return curTile == colour;
    }
    else if (deltaCol == 0 && deltaRow == 0) {
        return false;
    }
    
}

bool checkLegal(char*board, int size, char row, char col, 
char colour) {
    int deltaCol = -1, deltaRow = -1;
    int intRow = 0, intCol = 0;
    bool det = false;
    while (deltaRow <= 1) {
                deltaCol = -1;
                while (deltaCol <= 1) {
                    intRow = row - 'a';
                    intCol = col - 'a';
                    det = checkLegalInDirection(board, size, row, col, colour, deltaCol, deltaRow);
                    if (det == true) {
                        return true;
                    }
                    deltaCol = deltaCol + 1;
                }
                deltaRow = deltaRow + 1;
            }
        return false;
}

void flip(char*board, int size,char colour, char row, char col) {
    int deltaCol = -1, deltaRow = -1;
    int intRow = row - 'a', intCol = col - 'a';
    char tempCol = col, tempRow = row;
    bool det = false;
    while (deltaRow <= 1) {
                deltaCol = -1;
                while (deltaCol <= 1) {
                    tempCol = col;
                    tempRow = row;
                    det = checkLegalInDirection(board, size, row, col, colour, deltaCol, deltaRow);
                    if (det == true) {
                        do {
                            *(board + intRow * 26 + intCol) = colour;
                            tempRow = tempRow + deltaRow;
                            tempCol = tempCol + deltaCol;
                            intRow = tempRow - 'a';
                            intCol = tempCol - 'a';
                        } while ((*(board + intRow * 26 + intCol) != colour) && positionInBounds(size, row, col));
                    }
                    deltaCol = deltaCol + 1;
                }
                deltaRow = deltaRow + 1;
            }
}

int checkAvailability(char*board, char*availableMove, int size, char colour) {
    char row = 'a', col = 'a';
    int deltaRow, deltaCol, intRow, intCol;
    bool det;
    int move = 0;
    while (positionInBounds(size, row, col)) {
        while (positionInBounds(size, row, col)) {
            deltaRow = -1;
            while (deltaRow <= 1) {
                deltaCol = -1;
                while (deltaCol <= 1) {
                    intRow = row - 'a';
                    intCol = col - 'a';
                    det = checkLegalInDirection(board, size, row, col, colour, deltaCol, deltaRow);
                    if (det == true && *(board + intRow * 26 + intCol) == 'U') {
                        *(availableMove + move * 3) = row;
                        *(availableMove + move * 3 + 1) = col;
                        move = move + 1;
                        break;
                    }
                    if (det == true) {
                        break;
                    }
                    deltaCol = deltaCol + 1;
                }
                if (det == true) {
                    break;
                }
                deltaRow = deltaRow + 1;
            }
            col = col + 1;
        }
        row = row + 1;
        col = 'a';
    }
    return move;
}

void computerMove(char*board, char*availableMove, int size, char colour) {
    char copyBoard[26][26];
    int scoreBoard[676];
    int intRow, intCol, i = 0;;
    // Make a copy of the original board
    for (intRow = 0; intRow < 26; intRow++) {
        for (intCol = 0; intCol < 26; intCol++) {
            copyBoard[intRow][intCol] = *(board + intRow * 26 + intCol);
        }
    }
    // Initial the scoreBoard
    for (intRow = 0; intRow < 676; intRow++) {
        scoreBoard[i] = 0;
    }
    int maxScore = 0;
    i = 0;
    // Obtain available move list and return numbers of valid moves
    int move = checkAvailability(board, availableMove, size, colour);
    // Go through all available moves
    while (i < move) {
        // Flip candidates on test board
        flip(copyBoard, size, colour, *(availableMove + i * 3), *(availableMove + i * 3 + 1));
        // Record the score into array
        scoreBoard[i] = countScore(copyBoard, size, colour) - countScore(board, size, colour);
        // Record the maximum score
        if (scoreBoard[i] > maxScore) {
            maxScore = scoreBoard[i];
        }
        i = i + 1;
        // Recover the test board to original state
        for (intRow = 0; intRow < 26; intRow++) {
            for (intCol = 0; intCol < 26; intCol++) {
                copyBoard[intRow][intCol] = *(board + intRow * 26 + intCol);
            }
        }
    }
    i = 0;
    // Search position of max score in the array
    while (scoreBoard[i] != maxScore) {
        i = i + 1;
    }
    // Flip the max score tile
    printf("Computer places %c at %c%c. \n", colour, *(availableMove + i * 3), *(availableMove + i * 3 + 1));
    flip(board, size, colour, *(availableMove + i * 3), *(availableMove + i * 3 + 1));
    printBoard(board, size);
}

int countScore(char*board, int size, char colour) {
    int i, n, score = 0;
    for (i = 0; i < size; i++) {
        for (n = 0; n < size; n++) {
            if (*(board + i * 26 + n) ==  colour) {
                score = score + 1;
            }
        }
    }
    return score;
}