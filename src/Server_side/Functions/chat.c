#include "../server_helper.h"

extern NodeUser* root;

void process_chat(message *msg, User* current_user) {
    char *to_account = getTarget(msg);
    char *content = getData(msg);

    NodeUser *receiver = search_NodeUser_withAccount(root, to_account);

    size_t rep_len = sizeof(reply);

    if (receiver == NULL) {
        WARNING("Receiver not found!");
        send(current_user->listener, create_reply(ko, "NULL_ACCOUNT"), rep_len, 0);

    } else if (receiver->is_active != 1) {
        WARNING("Trying to send message to offline account");
        send(current_user->listener, create_reply(ko, "OFFLINE_ACCOUNT"), rep_len, 0);

    } else {
        INFORLOG("Transfering message...");
        char rendered[rep_instruct_len];
        bzero(rendered, rep_instruct_len);

        sprintf(rendered, "\033[1;32m%s\033[0m: %s", current_user->account, content);

        send(receiver->user->listener, create_reply(chat, rendered), rep_len, 0);
        send(current_user->listener, create_reply(ok, "MESSAGE_SENT"), rep_len, 0);

        INFORLOG("Transfered message!");
    }
}