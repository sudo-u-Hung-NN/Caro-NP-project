#ifndef SERVER_HELPER_H
#define SERVER_HELPER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/wait.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include "string.h"
#include "ctype.h"
#include "stdlib.h"

#include "../Utils/message.h"
#include "../Utils/logger.h"
#include "./Users/user.h"
#include "./Game/game.h"


#define PORT 5500
#define BACKLOG 20
#define BUFF_SIZE 1024


extern NodeUser *root;


/* Handler process signal*/
void sig_chld(int signo);

/**
* Receive and serve client
* [IN] sockfd: socket descriptor that connects to client 
* [IN] conn_chat_sock: socket descriptor that also connects to client	
*/
void serve(int sockfd, int conn_chat_sock);


/**
 * ================================================================================================
 *                                          FUNCTIONS
 * 1. Utils
 * 1.1. process_sign_up()
 * 1.2. process_sign_in()
 * 1.3. process_setname()
 * 1.4. process_listp()
 * 1.5. process_listg()
 * 
 * 4. Game
 * 4.1. process_chat()
 * 4.2. process_play()
 * 4.3. process_accept()
 * 4.4. process_deny()
 * 
 * 
 * 2. History
 * 2.1. process_hist()
 * 2.2. process_histp()
 * 2.3. process_hista()
 * 
 * 3. Spectate
 * 3.1. process_spec()
 * 3.2. process_squit()
 * 3.3. process_schat()
 * 
 * ================================================================================================
 */


/** Utils
 * @brief Process sign up on socket that connects to client.
 * This function is defined in "src/Server_side/Functions/sign_in_up.c"
 * @param msg the requested message from client
 * @param client_sock the sock used for trivial communication
 * @param client_game_sock the sock used for game communication only
 * @return User*
 */
User* process_sign_up(message *msg, int client_sock, int client_game_sock);


/**
 * @brief Process login on socket that connects to client.
 * This function is defined in "src/Server_side/Functions/sign_in_up.c"
 * @param msg the requested message from client
 * @param client_sock the sock used for trivial communication
 * @param client_game_sock the sock used for game communication only
 * @return User*
 */
User* process_sign_in(message *msg, int client_sock, int client_game_sock);


/**
 * @brief This function set new name to the user.
 * This function is defined in "src/Server_side/Functions/setname.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_setname(message *msg, User* current_user);


/**
 * @brief This function displays all online players.
 * This function is defined in "src/Server_side/Functions/list.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_listp(message *msg, User* current_user);


/**
 * @brief This function shows all current games.
 * This function is defined in "src/Server_side/Functions/list.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_listg(message *msg, User* current_user);



/** History
 * @brief This function shows the current user his own history.
 * This function is defined in "src/Server_side/Functions/hist.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_hist(message *msg, User* current_user);


/**
 * @brief This function shows the current user a nother player's history.
 * This function is defined in "src/Server_side/Functions/hist.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_histp(message *msg, User* current_user);


/**
 * @brief This function shows the rankings.
 * This function is defined is "src/Server_side/Functions/hist.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_hista(message *msg, User* current_user);



/** Game
 * @brief This function process play protocol, create new game room
 * @param msg the requested message from client
 * @param current_user the current user
 * @return Game* 
 */
Game* process_play(message *msg, User* current_user);

void process_go(message *msg, User* current_user, Game* game);

void process_draw(message *msg, User* current_user, Game* game);

void process_rematch(message *msg, User* current_user);



/** Spec
 * @brief This function help spectate a game
 * @param msg the requested message from client
 * @param current_user the current user
 * @return Game* 
 */
Game * process_spec(message *msg, User* current_user);

void process_schat(message *msg, User* current_user, Game* game);

void process_squit(message *msg, User* current_user, Game* game);


/** Norm
 * @brief This function send chat message
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_chat(message *msg, User* current_user);

void process_return(message *msg, User* current_user);

void process_cancel(message *msg, User* current_user);

void process_quit(message *msg, User* current_user);

#endif