#include "message.h"

struct KEY {
  char string[25];
  msg_type mtype;
  sts_type usable_in_status[4];
  int num_usable;
} keywords[MSG_TYPE_LEN] = {
  {"play", play, {console}, 1},
  {"go", go, {playing}, 1},
  {"accept", acpt, {console, playing, spectating}, 3},
  {"deny", deny, {console, playing, spectating}, 3},
  {"cancel", cancel, {waiting}, 1},
  {"draw", draw, {playing}, 1},
  {"rematch", rematch, {console}, 1},
  {"chat", chat, {console, playing, spectating}, 3},
  {"quit", quit, {console, playing, spectating, waiting}, 4},
  {"spec", spec, {console}, 1},
  {"schat", schat, {spectating}, 1},
  {"squit", squit, {spectating}, 1},
  {"hist", hist, {console}, 1},
  {"histp", histp, {console, spectating}, 2},
  {"hista", hista, {console}, 1},
  {"ret", ret, {spectating, waiting}, 2},
  {"listp", listp, {console}, 1},
  {"listg", listg, {console}, 1},
  {"setname", setname, {console}, 1},
  {"signup", signup, {console}, 1},
  {"signpwd", signpwd, {console}, 1},
  {"login", login, {console}, 1},
  {"logpwd", logpwd, {console}, 1}
};


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
    bzero(new_msg, sizeof(message));

    char command[25] = "\0", target[TARGET_LEN] = "\0", data[DATA_LEN] = "\0";

    int i = 0, j = 0, k = 0;

    for (; i < strlen(input) && input[i] != ' '; i++) {
        command[i] = input[i];
    }

    msg_type mtype = command_char2type(command);
    int valid = check_valid(curr_status, mtype);

    if (mtype == not_identified) {
        error(ERROR_COMMAND_NOT_FOUND);
        free(new_msg);
        return NULL;

    } else if (!valid) {
        error(ERROR_INVALID_STATUS_COMMAND);
        free(new_msg);
        return NULL;
    }

    switch (mtype)
    {
    // case play:
    // case go:
    // case spec:
    // case histp:
    // case setname:
    // case signup:
    // case signpwd:
    // case login:
    // case logpwd:
    case chat:
        for (j = i + 1; j < TARGET_LEN && input[j] != ' '; j++) {
            target[j - (i+1)] = input[j];
        }
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
    // new_msg->status = curr_status;
    strcpy(new_msg->data.target, target);
    strcpy(new_msg->data.data, data);

    // printf("Create message:\nCommand: <%s>\nTarget: <%s>\nData: <%s>\n",
    //         keywords[new_msg->command].string, new_msg->data.target, new_msg->data.data);
    return new_msg;
}


char *getTarget(message *msg) {
    return msg->data.target;
}

char *getData(message *msg) {
    return msg->data.data;
}

void displayMessage(message *msg, char *announce) {
    printf("%s:\nCommand: <%s>\nTarget: <%s>\nData: <%s>\n",
            announce, keywords[msg->command].string, msg->data.target, msg->data.data);
}