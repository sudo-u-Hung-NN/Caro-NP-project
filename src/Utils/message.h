#ifndef MESS_H
#define MESS_H

#include "types.h"
#include "data.h"
#include "error.h"

#include "stdlib.h"
#include "string.h"
#include "stdio.h"

struct message {
    msg_type command;
    msg_data data;
};

typedef struct message message;

int check_valid(sts_type status, msg_type command);
message *create_msg(char *input, sts_type curr_status);

char *getData(message *msg);
char *getTarget(message *msg);

void displayMessage(message *msg, char* announce);
void help();

#endif