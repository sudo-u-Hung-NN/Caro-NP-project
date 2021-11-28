#include "../Hsrc/message.h"
#include "../Hsrc/types.h"
#include "../Hsrc/data.h"
#include "../Hsrc/error.h"


#include "stdlib.h"
#include "string.h"
#include "stdio.h"


int check_valid(sts_type status, msg_type command) {
    int index = 0;
    for (; index < MSG_TYPE_LEN; index ++) {
        if (keywords[index].mtype == command) {
            break;
        }
    }

    sts_type *usable_status = keywords[index].usable_in_status;
    int num_usable = keywords[index].num_usable;
    for (int i = 0; i < num_usable; i ++) {
        if (usable_status[i] == status) {
            return 1;
        }
    }
    return 0;
}


msg_type command_char2type(char *command) {
    for (int i = 0; i < MSG_TYPE_LEN; i++) {
        if (strcasecmp(keywords[i].string, command) == 0) {
            return keywords[i].mtype;
        }
    }
    return not_identified;
}


message *create_msg(char *input, sts_type curr_status) {
    message *new_msg = (message *) malloc(sizeof(message));

    char command[25] = "\0", target[TARGET_LEN] = "\0", data[DATA_LEN] = "\0";

    int i = 0, j = 0, k = 0;

    for (; i < strlen(input) && input[i] != ' '; i++) {
        command[i] = input[i];
    }

    msg_type mtype = command_char2type(command);
    int valid = check_valid(curr_status, mtype);

    if (!valid){
        error(ERROR_INVALID_STATUS_COMMAND);
        free(new_msg);
        return NULL;
    }

    switch (mtype)
    {
    case play:
    case go:
    case spec:
    case histp:
    case setname:
    case signin:
    case signpwd:
    case login:
    case logpwd:
        for (j = i + 1; j < TARGET_LEN && input[j] != ' '; j++) {
            target[j - (i+1)] = input[j];
        }
        break;
    case not_identified:
        error(ERROR_COMMAND_NOT_FOUND);
        free(new_msg);
        return NULL;
        break;
    default:
        break;
    }

    if (j == 0) {
        k = i;
    } else {
        k = j;
    }

    for (int p = k + 1; p - (k + 1) < DATA_LEN && input[p] != '\0'; p++) {
        data[p - (k + 1)] = input[p];
    }

    new_msg->command = mtype;
    new_msg->status = curr_status;
    strcpy(new_msg->data.target, target);
    strcpy(new_msg->data.data, data);

    return new_msg;
}


// int main(int argc, char const *argv[])
// {
//     // sts_type s = console;
//     // msg_type m = chat;
//     // int i = check_valid(s, m);
//     // printf("%d\n", i);

//     message *mess = create_msg("CHAT 0x11 choi khong", console);
//     if (mess == NULL) {
//         printf("Message not created");
//     }
//     return 0;
// }
