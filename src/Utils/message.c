#include "message.h"

struct KEY {
  char string[25];
  msg_type mtype;
  sts_type usable_in_status[4];
  int num_usable;
  char help[120];

} keywords[MSG_TYPE_LEN] = {
  {"play", play, {console}, 1, "Type: 'play <account>' to challenge other players"},
  {"go", go, {playing}, 1, "Type: 'go <A5>' to place your move to cell A5. You can only use this command in play mode"},
  {"accept", acpt, {console, spectating}, 2, "Type: 'accept' to accept challenge invitation from other"},
  {"deny", deny, {console, spectating}, 2, "Type: 'deny' to decline challenge invitation from other"},
  {"cancel", cancel, {waiting}, 1, "Type: 'cancel' to cancel challenge invitation to other"},
  {"draw", draw, {playing}, 1, "Type: 'draw' to send draw request to opponent. You can only use this command in play mode"},
  {"rematch", rematch, {console}, 1, "Type: 'rematch' to re-challenge your previous opponent"},
  {"chat", chat, {console, playing, spectating, waiting}, 4, "Type: 'chat <account> <content>' to send message to an ONLINE account"},
  {"quit", quit, {console, playing, spectating, waiting}, 4, "Type: 'quit' to turn off the application"},
  {"spec", spec, {console}, 1, "Type: 'spec' to spectate a currently-playing game"},
  {"schat", schat, {spectating}, 1, "Type: 'schat' to send message to all players in a game. You can only use this command in spectating mode"},
  {"squit", squit, {spectating}, 1, "Type: 'squit' to exit spectating. You can only use this command in spectating mode"},
  {"hist", hist, {console, playing, spectating}, 3, "Type: 'hist' to check your history"},
  {"histp", histp, {console, spectating, playing}, 3, "Type: 'histp <account>' to check an account's history"},
  {"hista", hista, {console}, 1, "Type: 'hista' to check rankings"},
  {"return", ret, {spectating, waiting}, 2, "Type: 'return' to get back"},
  {"listp", listp, {console, playing}, 2, "Type: 'listp' to list all players"},
  {"listg", listg, {console, playing}, 2, "Type: 'listg' to list all currently-playing games"},
  {"setname", setname, {console}, 1, "Type: 'setname <newname>' to set your name to newname"},
  {"signup", signup, {console}, 1, ""},
  {"signpwd", signpwd, {console}, 1, ""},
  {"login", login, {console}, 1, ""},
  {"logpwd", logpwd, {console}, 1, ""}
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
    printf("return unidentified\n");
    return not_identified;
}


message *create_msg(char *input, sts_type curr_status) {
    message *new_msg = NULL;

    char command[25] = "\0", target[TARGET_LEN] = "\0", data[DATA_LEN] = "\0";

    int i = 0, j = 0, k = 0;

    for (; i < strlen(input) && input[i] != ' '; i++) {
        command[i] = input[i];
    }

    msg_type mtype = command_char2type(command);

    if (mtype == not_identified) {
        error(ERROR_COMMAND_NOT_FOUND);
        return NULL;

    } else if (!check_valid(curr_status, mtype)) {
        error(ERROR_INVALID_STATUS_COMMAND);
        return NULL;

    } else {
        switch (mtype) {
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

        new_msg = (message *) malloc(sizeof(message));
        bzero(new_msg, sizeof(message));
        new_msg->command = mtype;
        // new_msg->status = curr_status;
        strcpy(new_msg->data.target, target);
        strcpy(new_msg->data.data, data);

    }
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


reply *create_reply(msg_type command, char *instruction) {
    reply *tmp = (reply*) malloc(sizeof(reply));
    if (tmp == NULL) {
        printf("FAILED to create reply\n");
        return NULL;
    }
    tmp->command = command;
    strcpy(tmp->instruction, instruction);
    return tmp;
}


void help() {
    for (int i = 0; i < MSG_TYPE_LEN; i++) {
        if (strlen(keywords[i].help) > 1) {
            printf("%s\n", keywords[i].help);
        }
    }
}