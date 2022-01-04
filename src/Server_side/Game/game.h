#ifndef GAME_H
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include "sys/mman.h"

#include "../Users/user.h"
#include "../../Utils/message.h"
#include "../../Utils/logger.h"

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

typedef struct Game Game;
typedef struct Player Player;
typedef struct Spectator Spectator;

struct Spectator {
    Game *current_game;
    User *user;
    Spectator *next;
};

typedef struct Player
{
    char role; // 'X' or 'Y'
    int score;
    const User *user;
    Game *current_game;
    int draw;
} Player;


typedef struct Game {
    int id;
    char board[SIZE][SIZE];
    Player *player1;
    Player *player2;
    int number_spectator;
    Spectator *spectator_head;
    char turn; // 'X' or 'Y'
    int num_move;
} Game;


typedef struct NodeGame {
    int playing;
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


/**
 * @brief Check if the move at row and col is valid
 * @param game 
 * @param row 
 * @param col 
 * @return int 
 */
int isValid(Game *game, int row, int col);


/**
 * @brief Check if the move at row and col ends the game
 * @param game 
 * @param row 
 * @param col 
 * @return int 
 */
int checkWin(Game *game, int row, int col);


/**
 * @brief Check if there are no more space on the board
 * @param game 
 * @return int 
 */
int checkTie(Game *game);


/**
 * @brief Place the move 
 * @param game 
 * @param role 
 * @param row 
 * @param col 
 */
void loadGame(Game *game, char role, int row, int col);


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


/**
 * @brief Insert new spectator into link list
 * @param current_user 
 * @param current_game 
 * @return Spectator* 
 */
Spectator *insert_Spectator(User *current_user, Game* current_game);


/**
 * @brief If the spectator use squit, remove spectator from the list
 * @param current_game 
 * @param current_user 
 * @return Spectator* 
 */
Spectator *remove_Spectator(Game* current_game, User *current_user);


/**
 * @brief The game is over, free entire spectator list
 * @param current_game 
 * @return Spectator* 
 */
Spectator *free_Spectator_List(Game* current_game);

#endif