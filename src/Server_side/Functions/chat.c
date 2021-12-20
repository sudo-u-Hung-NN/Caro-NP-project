#include "../server_helper.h"

extern NodeUser* root;

void process_chat(message *msg, User* current_user) {
    char *to_account = getTarget(msg);
    char *content = getData(msg);

    NodeUser *receiver = search_NodeUser_withAccount(root, to_account);

    if (receiver == NULL) {
        WARNING("Receiver not found!");
        send(current_user->conn_sock, "NULL_ACCOUNT", 50, 0);

    } else if (receiver->is_active != 1) {
        WARNING("Trying to send message to offline account");
        send(current_user->conn_sock, "OFFLINE_ACCOUNT", 50, 0);

    } else {
        INFORLOG("Transfering message...");
        char rendered[BUFF_SIZE];
        bzero(rendered, BUFF_SIZE);

        sprintf(rendered, "\033[1;32m%s\033[0m: %s", current_user->account, content);
        send(receiver->user->chat_sock, rendered, BUFF_SIZE, 0);
        send(current_user->conn_sock, "MESSAGE_SENT", 50, 0);
    }

    INFORLOG("Transfered message!");
}