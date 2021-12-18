#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "../Users/user.h"

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


typedef struct Player
{
    int id;
    int score;
    const User *user;
    int draw;
} Player;


typedef struct Game
{
    int id;
    char board[SIZE][SIZE];
    Player *player1;
    Player *player2;
    int firstMove;
} Game;


/**
 * @brief This function creates a user-cored Player
 * @param user 
 * @return Player* 
 */
Player* initPlayer(const User *user);


/**
 * @brief This function creates a game with 2 players
 * @param player1 
 * @param player2 
 * @param game_id 
 * @return Game* 
 */
Game* initGame(Player *player1, Player *player2, int game_id);


/**
 * @brief This function starts the game
 * @param game 
 */
void play(Game* game);


/**
 * @brief This function renders the board
 * @param game 
 */
void loadGameScreen(Game *game);


/**
 * @brief This function calls back 2 players for another game
 * @param game 
 */
void rematch(Game* game);

#endif