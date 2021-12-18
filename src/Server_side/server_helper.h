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

#define PORT 5500
#define BACKLOG 20
#define BUFF_SIZE 1024


extern NodeUser *root;


/* Handler process signal*/
void sig_chld(int signo);

/**
* Receive and serve client
* [IN] sockfd: socket descriptor that connects to client 	
*/
void serve(int sockfd);


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
 * 4. Game
 * ================================================================================================
 */


/** Utils
 * @brief Process sign up on socket that connects to client.
 * This function is defined in "src/Server_side/Functions/sign_in_up.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 * @return User*
 */
User* process_sign_up(int conn_sock, message *msg);


/**
 * @brief Process login on socket that connects to client.
 * This function is defined in "src/Server_side/Functions/sign_in_up.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 * @return User*
 */
User* process_sign_in(int conn_sock,  message *msg);


/**
 * @brief This function set new name to the user.
 * This function is defined in "src/Server_side/Functions/setname.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 * @param current_user 
 */
void process_setname(int conn_sock, message *msg, User* current_user);


/**
 * @brief This function displays all online players.
 * This function is defined in "src/Server_side/Functions/list.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 */
void process_listp(int conn_sock, message *msg);


/**
 * @brief This function shows all current games.
 * This function is defined in "src/Server_side/Functions/list.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 */
void process_listg(int conn_sock, message *msg);



/** History
 * @brief This function shows the current user his own history.
 * This function is defined in "src/Server_side/Functions/hist.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 * @param current_user 
 */
void process_hist(int conn_sock, message *msg, User* current_user);


/**
 * @brief This function shows the current user a nother player's history.
 * This function is defined in "src/Server_side/Functions/hist.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 */
void process_histp(int conn_sock, message *msg);


/**
 * @brief This function shows the rankings.
 * This function is defined is "src/Server_side/Functions/hist.c"
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 */
void process_hista(int conn_sock, message *msg);


#endif