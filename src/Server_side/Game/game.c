#include "game.h"

extern int total_game;


void initGameBoard(Game *game)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            game->board[i][j] = '.';
        }
    }
}


Game *initGame(Player *player1, Player *player2)
{
    // Game *game = (Game *)malloc(sizeof(Game));
    Game* game = (Game *) mmap(NULL, sizeof(Game), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (game == NULL) {
        printf("Can't allocate!\n");
        exit(0);
    }
    initGameBoard(game);
    game->id = total_game;
    game->turn = 'X';
    game->player1 = player1;
    game->player2 = player2;

    game->number_spectator = 0;
    game->num_move = 0;

    total_game += 1;
    return game;
}


void loadGame(Game *game, char role, int row, int col) {
    game->board[row][col] = role;
}


//Check entered cordination valid or invalid
//1 for valid, 0 for invalid
int isValid(Game *game, int row, int col)
{
    return (game->board[row][col] == '.') && (row < SIZE) && (col < SIZE) && (row >= 0) && (col >= 0);
}


int checkWin(Game *game, int row, int col)
{
    int check = 0, rowTmp = row, colTmp;

    // check horizontal
    while (game->board[rowTmp][col] == game->board[row][col])
    {
        check++;
        rowTmp++;
    }
    rowTmp = row - 1;
    while (game->board[rowTmp][col] == game->board[row][col])
    {
        check++;
        rowTmp--;
    }
    if (check > 4)
        return 1;
    check = 0;
    colTmp = col;

    // check vertical
    while (game->board[row][colTmp] == game->board[row][col])
    {
        check++;
        colTmp++;
    }
    colTmp = col - 1;
    while (game->board[row][colTmp] == game->board[row][col])
    {
        check++;
        colTmp--;
    }
    if (check > 4)
        return 1;

    // check left cross
    rowTmp = row;
    colTmp = col;
    check = 0;
    while (game->board[row][col] == game->board[rowTmp][colTmp])
    {
        check++;
        rowTmp++;
        colTmp++;
    }
    rowTmp = row - 1;
    colTmp = col - 1;
    while (game->board[row][col] == game->board[rowTmp][colTmp])
    {
        check++;
        rowTmp--;
        colTmp--;
    }
    if (check > 4)
        return 1;

    // check right cross
    rowTmp = row;
    colTmp = col;
    check = 0;
    while (game->board[row][col] == game->board[rowTmp][colTmp])
    {
        check++;
        rowTmp++;
        colTmp--;
    }
    rowTmp = row - 1;
    colTmp = col + 1;
    while (game->board[row][col] == game->board[rowTmp][colTmp])
    {
        check++;
        rowTmp--;
        colTmp++;
    }
    if (check > 4)
        return 1;

    return 0;
}


int checkTie(Game *game) {
    if (game->num_move == SIZE * SIZE) {
        return 1;
    } else {
        return 0;
    }
}


void get_move(Game *game, char *move, int *row, int *col) {
    do {
        scanf("%s", move);
        *row = (int)move[0] - 65;
        *col = (int)move[1] - 48;
    } while (!isValid(game, *row, *col));
}


// void game_rematch(Game *game)
// {
//     if (game->turn == 'X') {
//         game_play(game);
//     }
//     else
//     {
//         Player *tmp = game->player1;
//         game->player1 = game->player2;
//         game->player2 = tmp;
//         game_play(game);
//     }
// }