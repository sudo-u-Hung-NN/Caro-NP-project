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

#define PORT 5500
#define BACKLOG 20
#define BUFF_SIZE 1024

char *uppercase(char* input);

/* Handler process signal*/
void sig_chld(int signo);

/*
* Receive and echo message to client
* [IN] sockfd: socket descriptor that connects to client 	
*/
void echo(int sockfd);


#endif