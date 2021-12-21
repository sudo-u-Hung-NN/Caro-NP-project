#include "../server_helper.h"

extern NodeUser* root;

void traverse(NodeUser *root, char* buffer) {
    if (root == NULL || strlen(buffer) + 1 > rep_instruct_len) {
        return;
    }
    char formatted_string[150] = "\0";
    traverse(root->left, buffer);
    if (root->is_active) {
        sprintf(formatted_string, "%3d \033[0;32m%-15s\033[0m %-15s \033[1;34m%-5s\033[0m\n", root->user->id, root->user->account, root->user->name, "ONLINE");
    } else {
        sprintf(formatted_string, "%3d \033[0;32m%-15s\033[0m %-15s \033[0;31m%-5s\033[0m\n", root->user->id, root->user->account, root->user->name, "OFFLINE");
    }
    
    strcat(buffer, formatted_string);
    traverse(root->right, buffer);
}


/**
 * @brief This function displays all online players
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_listp(message *msg, User* current_user) {
    INFORLOG("Received request listing all players");

    size_t rep_len = sizeof(reply);

    char list[rep_instruct_len];
    bzero(list, rep_instruct_len);

    char formatted_string[128] = "\0";
    sprintf(formatted_string, "\n%3s %-15s %-15s %-5s\n", "Id", "Account", "Name", "Status");

    strcat(list, formatted_string);
    traverse(root, list);
    // printf("%s", list);
    send(current_user->listener, create_reply(ok, list), rep_len, 0);
}


/**
 * @brief This function shows all current games
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_listg(message *msg, User* current_user) {
    INFORLOG("Received request listing all games");
    send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}