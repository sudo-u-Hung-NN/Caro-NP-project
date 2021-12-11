#include <stdio.h>
#include <stdlib.h>
#include "player.c"

#define SIZE 10 //Board size

#define ROW_A 0
#define ROW_B 1
#define ROW_C 2
#define ROW_D 3
#define ROW_E 4
#define ROW_F 5
#define ROW_G 6
#define ROW_H 7
#define ROW_I 8
#define ROW_J 9

#define ROLE_X 'X'
#define ROLE_O 'O'

typedef struct Game
{
    int id;
    char board[SIZE][SIZE];
    Player *player1;
    Player *player2;
    int firstMove;
} Game;

void initGameBoard(Game *game) {
    for(int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            game->board[i][j] = '.';
        }
    }
}

Game* initGame(Player *player1, Player *player2) {
    Game *game = (Game*) malloc(sizeof(Game));
    if (game == NULL) {
        printf("Can't allocate!\n");
        exit(0);
    }
    initGameBoard(game);
    game->firstMove = 1;
    game->player1 = player1;
    game->player2 = player2;
    return game;
}

void loadGame(Game* game, char role, int row, int col){
    game->board[row][col] = role;
}

void loadGameScreen(Game *game) {
    printf("    0   1   2   3   4   5   6   7   8   9\n");
    printf("  -----------------------------------------\n");
    char row = 65;
    for(int i=0; i<SIZE; i++) {
        printf("%c ",row++);
        for (int j=0; j<SIZE; j++) {
            printf("| %c ",game->board[i][j]);
        }
        printf("|\n  -----------------------------------------\n");
    }
}

//Check entered cordination valid or invalid
//1 for valid, 0 for invalid
int isValid(Game* game, int row, int col) {
    return (game->board[row][col] == '.') && (row<SIZE) 
                && (col<SIZE) && (row>=0) && (col>=0);
}

int checkWin(Game* game, int row, int col) {
    int check = 0, rowTmp = row, colTmp;

    // check horizontal
    while (game->board[rowTmp][col] == game->board[row][col]) {
        check++;
        rowTmp++;
    }
    rowTmp = row - 1;
    while (game->board[rowTmp][col] == game->board[row][col]) {
        check++;
        rowTmp--;
    }
    if (check > 4) return 1;
    check = 0; colTmp = col;

    // check vertical
    while(game->board[row][colTmp] == game->board[row][col]) {
        check++;
        colTmp++;
    }
    colTmp = col - 1;
    while(game->board[row][colTmp] == game->board[row][col]) {
        check++;
        colTmp--;
    }
    if (check > 4) return 1;

    // check left cross
    rowTmp = row; colTmp = col; check = 0;
    while (game->board[row][col] == game->board[rowTmp][colTmp]) {
        check++;
        rowTmp++;
        colTmp++;
    }
    rowTmp = row - 1; colTmp = col - 1;
    while (game->board[row][col] == game->board[rowTmp][colTmp]) {
        check++;
        rowTmp--;
        colTmp--;
    }
    if (check > 4) return 1;

    // check right cross
    rowTmp = row; colTmp = col; check = 0;
    while (game->board[row][col] == game->board[rowTmp][colTmp]) {
        check++;
        rowTmp++;
        colTmp--;
    }
    rowTmp = row - 1; colTmp = col + 1;
    while (game->board[row][col] == game->board[rowTmp][colTmp]) {
        check++;
        rowTmp--;
        colTmp++;
    }
    if (check > 4) return 1;

    return 0;
	}

//Start game
void play(Game* game) {
    initGameBoard(game);
    loadGameScreen(game);
    char move[3];
    int row, col;
    int step = 0;
    while(step<=100) {
        do
        {
            printf("Enter %s's move: ", game->player1->name);
            scanf("%s", move);
            row = (int)move[0]-65;
            col = (int)move[1]-48;
        } while (!isValid(game, row, col));
        step++;
        loadGame(game, ROLE_X, row, col);
        loadGameScreen(game);
        if (checkWin(game, row, col))
        {
            game->firstMove = 2;
            game->player1->score+=3;
            game->player2->score--;
            printf("%s won!\n", game->player1->name);
            return;
        }
        
        do
        {
            printf("Enter %s's move: ", game->player2->name);
            scanf("%s", move);
            row = (int)move[0]-65;
            col = (int)move[1]-48;
        } while (!isValid(game, row, col));
        step++;
        loadGame(game, ROLE_O, row, col);
        loadGameScreen(game);
        if (checkWin(game, row, col))
        {
            game->firstMove = 1;
            game->player2->score+=3;
            game->player1->score--;
            printf("%s won!\n", game->player2->name);
            return;
        }
    }
    printf("Game draw!\n");
    game->player1->score++;
    game->player2->score++;
    game->firstMove = 1;
}

void rematch(Game* game) {
    if(game->firstMove == 1) {
        play(game);
    }
    else
    {
        Player* tmp = game->player1;
        game->player1 = game->player2;
        game->player2 = tmp;
        play(game);
    }
    
}