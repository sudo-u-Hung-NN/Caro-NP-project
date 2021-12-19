#ifndef CLIENT_HELPER_H
#define CLIENT_HELPER_H

#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>

#include "../Utils/types.h"
#include "../Utils/message.h"


#define NUM_TRANSITION 18
#define NUM_TRANSLATE 9

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5500
#define BUFF_SIZE 1024

/**
 * @brief This function is called whenever user create a command
 * @param recv_command 
 */
void apply_transition(msg_type recv_command);


/**
 * @brief This function translate Server's message into comprehensive sentences
 * @param server_reply 
 * @return char* 
 */
char *translate(char *server_reply);


/**
 * @brief This function handle the client_sock.
 * Client sock is used for trivial communication
 * @param client_sock 
 */
void *client_sock_handler(void *client_sock);


/**
 * @brief This function handle the client_chat_sock.
 * Client game sock is used for game's infor communication, i.e. Game board, Movement
 * @param client_chat_sock 
 */
void *client_chat_sock_handler(void *client_chat_sock);



#endif