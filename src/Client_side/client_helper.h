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
#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 5500
#define BUFF_SIZE 1024

void apply_transaction(msg_type recv_command, msg_type send_command);



#endif