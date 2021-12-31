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


#define NUM_TRANSITION 20
#define NUM_TRANSLATE 41
#define NUM_CHATSTORE 20
#define NUM_SCREENLINE 50

#define SERVER_ADDR "127.0.0.1"      // Testing address
#define SERVER_PORT 5500
#define BUFF_SIZE 1024
#define SIZE 10 //Board size


/**
 * @brief Get the Status Name 
 * @param status 
 * @return char* 
 */
char *getStatusName(sts_type status);


/**
 * @brief This function perform transition when sending message
 * @param command 
 */
void send_command(msg_type command);


/**
 * @brief This function perform transition when receive message
 * @param command 
 */
void recv_command(msg_type command);


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
void *client_listener_handler(void *client_sock);


/**
 * @brief This function handle the client_chat_sock.
 * Client game sock is used for game's infor communication, i.e. Game board, Movement
 * @param client_chat_sock 
 */
void *client_speaker_handler(void *client_chat_sock);


/**
 * @brief This function store chat into ChatScreen
 * @param buff 
 */
void store_chat(char* buff);


/**
 * @brief This function displays chat screen.
 */
void display_chatscreen();


#endif