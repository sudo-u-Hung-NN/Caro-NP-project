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

#include "../Utils/types.h"
#include "../Utils/message.h"


#define NUM_TRANSITION 20
#define NUM_TRANSLATE 8

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


#endif