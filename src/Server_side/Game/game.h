#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "sys/mman.h"

#include "../Users/user.h"
#include "../../Utils/logger.h"

#define MAX_SPECTATOR 10
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
    char role; // 'X' or 'Y'
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
    int number_spectator;
    User *spectators[MAX_SPECTATOR];
    char turn; // 'X' or 'Y'
} Game;


typedef struct NodeGame {
    Game* game;
    struct NodeGame *left;
    struct NodeGame *right;
} NodeGame;


/**
 * @brief This function creates a user-cored Player
 * @param user 
 * @param role either 'X' or 'O'
 * @return Player* 
 */
Player* initPlayer(const User *user, char role);


/**
 * @brief This function creates a game with 2 players
 * @param player1 
 * @param player2 
 * @return Game* 
 */
Game* initGame(Player *player1, Player *player2);


int isValid(Game *game, int row, int col);

int checkWin(Game *game, int row, int col);

void loadGame(Game *game, char role, int row, int col);


/**
 * @brief This function starts the game
 * @param game 
 */
void game_play(Game* game);


/**
 * @brief This function renders the board
 * @param game 
 */
char* loadGameScreen(Game *game);


/**
 * @brief This function calls back 2 players for another game
 * @param game 
 */
void game_rematch(Game* game);


/**
 * @brief Insert a game into game tree
 * @param game_root 
 * @param game 
 * @return NodeGame* game_root
 */
NodeGame *insert_NodeGame(NodeGame *game_root, Game *game);


/**
 * @brief This function search a game by id
 * @param game_root 
 * @param id 
 * @return NodeGame* game_root
 */
NodeGame *search_NodeGame_byId(NodeGame *game_root, int id);


/**
 * @brief This function close a game and delete it out of the game tree
 * @param game_root 
 * @param id 
 * @return NodeGame* game_root
 */
NodeGame* close_NodeGame_byId(NodeGame* game_root, int id);


#endif