#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Constants for player X, player O, and blank.
const char X = 'X', O = 'O', B = ' ';

// A board object contains the entire current state of a game.
// It contains the cells, the player whose turn it is, the row and column that
// the current player chooses, and the number of moves made in total.
struct board {
    char cells[3][3];
    char player;
    int row, column;
    int moves;
};

// Given X or O, return the other player.
// Otherwise returns B.
char other(char player) {
    //return player == X ? O : X;
    if(player == X){
        return O;
    }else if(player == O){
        return X;
    }else{
        return B;
    }
}

// Create a blank board, with X to move first, and no moves made.
struct board newBoard() {
    struct board b = {
        .cells = {{B, B, B},
                  {B, B, B},
                  {B, B, B}},
        .player = X,
        .row = -1,
        .column = -1,
        .moves = 0
    };
    return b;
}

// Prepare to make a move by converting a string such as "a2" to a row and
// column, or set them to -1 if the string is invalid, or the cell isn't blank.
struct board position(struct board b, char *text) {
    if(strlen(text) != 2){
        b.row = -1;
        b.column = -1;
        return b;
    }

    switch(text[0]){
        case 'a':
            b.row = 0;
            break;
        case 'b':
            b.row = 1;
            break;
        case 'c':
            b.row = 2;
            break;
        default:
            b.row = -1;
            b.column = -1;
    }
    switch(text[1]){
        case '1':
            b.column = 0;
            break;
        case '2':
            b.column = 1;
            break;
        case '3':
            b.column = 2;
            break;
        default:
            b.row = -1;
            b.column = -1;
    }

    if(b.row != -1 && b.cells[b.row][b.column] != B){
        b.row = -1;
        b.column = -1;
    }

    return b;
}

// Make the move which has been prepared, assuming it has already been checked
// that it is valid.
struct board move(struct board b) {
    b.cells[b.row][b.column] = b.player;
    b.player = other(b.player);
    b.moves++;
    return b;
}

// Check whether x, y, z form a winning line for the given player.
bool line(char p, char x, char y, char z) {
    return (p == x) && (p == y) && (p == z);
}

// Check whether or not the player who has just moved has won.
bool won(struct board b) {
    if(b.row == -1){
        return false;
    }

    bool result = false;
    result = result || line(other(b.player),
                            b.cells[b.row][0],
                            b.cells[b.row][1],
                            b.cells[b.row][2]);
    result = result || line(other(b.player),
                            b.cells[0][b.column],
                            b.cells[1][b.column],
                            b.cells[2][b.column]);

    result = result || line(other(b.player),
                            b.cells[0][0],
                            b.cells[1][1],
                            b.cells[2][2]);
    result = result || line(other(b.player),
                            b.cells[2][0],
                            b.cells[1][1],
                            b.cells[0][2]);
    return result;
}

// Display the board.
void display(struct board b) {
    printf("  1   2   3\n");
    for(int i = 0; i < 3; i++){
        printf("%c ", (i+'a'));
        for(int j = 0; j < 3; j++){
            printf("%c", b.cells[i][j]);
            if(j == 2){
                printf("\n");
            }else{
                printf(" | ");
            }
        }
        if(i == 2){
            printf("\n");
        }else{
            printf(" ---+---+---\n");
        }
    }
}

// Checks if the board is full
// If !won(b) && full(b), a draw has occured
bool full(struct board b){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(b.cells[i][j] == B){
                return false;
            }
        }
    }
    return true;
}



// TODO: finish this function
// Play the game interactively between two human players who take turns.
void play() {
    struct board b = newBoard();
    char input[3];

    while(!won(b) && !full(b)){
        display(b);
        b.row = -1;
        while(b.row == -1){
            printf("%c> ", b.player);
            scanf("%2c", input);
            // dirty hack to clear input buffer
            while(getchar() != '\n');
            b = position(b, input);
        }
        b = move(b);
    }

    if(won(b)){
        printf("%c has won!\n", other(b.player));
    }else{
        printf("The game ended in a draw\n");
    }
}

//-----------------------------------------------------------------------------
// Testing and running: nothing after this point needs to be changed.
//-----------------------------------------------------------------------------

// Structure for testing containing the count of the number of tests,
// whether the test passed, and the current error message.
struct testing {
   int passed, failed;
   char message[100];
};

// Check that two chars are equal
struct testing eqc(struct testing t, char actual, char expected) {
    if (actual == expected) { t.passed++; return t; }
    t.failed++;
    if (t.failed > 1) return t;
    int n = t.passed + 1;
    sprintf(t.message, "Test %d gives %c not %c", n, actual, expected);
    return t;
}

// Check that two ints are equal
struct testing eqi(struct testing t, int actual, int expected) {
    if (actual == expected) { t.passed++; return t; }
    t.failed++;
    if (t.failed > 1) return t;
    int n = t.passed + 1;
    sprintf(t.message, "Test %d gives %d not %d", n, actual, expected);
    return t;
}

void test() {
    struct testing t;
    t.passed = t.failed = 0;
    struct board b;

    // Tests 1 and 2 (other player)
    t = eqc(t, other(X), O);
    t = eqc(t, other(O), X);

    // Tests 3 to 7 (new board)
    b = newBoard();
    t = eqc(t, b.cells[0][0], B);
    t = eqc(t, b.cells[1][1], B);
    t = eqc(t, b.cells[2][2], B);
    t = eqi(t, b.player, X);
    t = eqi(t, b.moves, 0);

    // Tests 8 to 17 (valid positions)
    b = position(b, "a1");
    t = eqi(t, b.row, 0);
    t = eqi(t, b.column, 0);
    b = position(b, "a2");
    t = eqi(t, b.row, 0);
    t = eqi(t, b.column, 1);
    b = position(b, "a3");
    t = eqi(t, b.row, 0);
    t = eqi(t, b.column, 2);
    b = position(b, "b2");
    t = eqi(t, b.row, 1);
    t = eqi(t, b.column, 1);
    b = position(b, "c3");
    t = eqi(t, b.row, 2);
    t = eqi(t, b.column, 2);

    // Tests 18 to 25 (invalid positions)
    b = position(b, "d2");
    t = eqi(t, b.row, -1);
    b = position(b, "b0");
    t = eqi(t, b.row, -1);
    b = position(b, "b4");
    t = eqi(t, b.row, -1);
    b = position(b, "2b");
    t = eqi(t, b.row, -1);
    b = position(b, "b2x");
    t = eqi(t, b.row, -1);
    b = position(b, "b");
    t = eqi(t, b.row, -1);
    b = position(b, "");
    t = eqi(t, b.row, -1);
    b = position(b, "c3");
    b = move(b);
    b = position(b, "c3");
    t = eqi(t, b.row, -1);

    // Tests 26 to 31 (moves)
    b = newBoard();
    b = position(b, "b2");
    b = move(b);
    t = eqc(t, b.cells[1][1], X);
    t = eqc(t, b.player, O);
    t = eqi(t, b.moves, 1);
    b = position(b, "a1");
    b = move(b);
    t = eqc(t, b.cells[0][0], O);
    t = eqc(t, b.player, X);
    t = eqi(t, b.moves, 2);

    // Tests 32 to 41 (winning lines)
    t = eqi(t, line(X, X, X, X), true);
    t = eqi(t, line(O, O, O, O), true);
    t = eqi(t, line(X, O, O, O), false);
    t = eqi(t, line(O, X, X, X), false);
    t = eqi(t, line(X, X, X, O), false);
    t = eqi(t, line(X, X, B, X), false);
    t = eqi(t, line(X, B, X, X), false);
    t = eqi(t, line(X, B, X, B), false);
    t = eqi(t, line(X, B, B, B), false);
    t = eqi(t, line(O, B, O, B), false);

    // Tests 42 to 47 (a full game)
    b = newBoard();
    t = eqi(t, won(b), false);
    b = position(b, "b2");
    b = move(b);
    t = eqi(t, won(b), false);
    b = position(b, "a2");
    b = move(b);
    t = eqi(t, won(b), false);
    b = position(b, "c3");
    b = move(b);
    t = eqi(t, won(b), false);
    b = position(b, "a3");
    b = move(b);
    t = eqi(t, won(b), false);
    b = position(b, "a1");
    b = move(b);
    t = eqi(t, won(b), true);

    // Tests 48 to 50 (other winning plays)
    b = newBoard();
    b = position(b, "b2");
    b = move(b);
    b = position(b, "a1");
    b = move(b);
    b = position(b, "c1");
    b = move(b);
    b = position(b, "a2");
    b = move(b);
    b = position(b, "a3");
    b = move(b);
    t = eqi(t, won(b), true);
    b = newBoard();
    b = position(b, "a1");
    b = move(b);
    b = position(b, "c2");
    b = move(b);
    b = position(b, "b1");
    b = move(b);
    b = position(b, "c1");
    b = move(b);
    b = position(b, "b3");
    b = move(b);
    b = position(b, "c3");
    b = move(b);
    t = eqi(t, won(b), true);
    b = newBoard();
    b = position(b, "b3");
    b = move(b);
    b = position(b, "a1");
    b = move(b);
    b = position(b, "c3");
    b = move(b);
    b = position(b, "b1");
    b = move(b);
    b = position(b, "a3");
    b = move(b);
    t = eqi(t, won(b), true);

    printf("Tests passed: %d\n", t.passed);
    if (t.failed > 0) printf("Tests failed: %d\n", t.failed);
    if (t.failed > 0) printf("First failure: %s\n", t.message);
}

int main(int n, char *args[n]) {
    if (n >= 2 && strcmp(args[1], "-t") == 0) test();
    else play();
}
