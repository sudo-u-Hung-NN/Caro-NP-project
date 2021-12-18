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


struct user {
    int id;
    char name[50];
    char account[50];
    char password[50];
};


char *uppercase(char* input);

/* Handler process signal*/
void sig_chld(int signo);

/**
* Receive and serve client
* [IN] sockfd: socket descriptor that connects to client 	
*/
void serve(int sockfd);

/**
 * @brief Process sign up on socket that connects to client
 * @param conn_sock the socket connects to client
 * @param root the root of User tree
 * @return User*
 */
User* process_sign_up(int conn_sock, message *msg);

/**
 * @brief Process login on socket that connects to client
 * @param conn_sock the socket connects to client
 * @return User*
 */
User* process_sign_in(int conn_sock,  message *msg);



#endif