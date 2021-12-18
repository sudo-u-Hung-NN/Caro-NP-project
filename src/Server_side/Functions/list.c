#include "../server_helper.h"

extern NodeUser* root;


void traverse(NodeUser *root, char* buffer) {
    if (root == NULL || strlen(buffer) + 1 > BUFF_SIZE) {
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
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 */
void process_listp(int conn_sock, message *msg) {
    INFORLOG("Received request listing all players");
    char list[BUFF_SIZE];
    bzero(list, BUFF_SIZE);

    char formatted_string[128] = "\0";
    sprintf(formatted_string, "\n%3s %-15s %-15s %-5s\n", "Id", "Account", "Name", "Status");

    strcat(list, formatted_string);
    traverse(root, list);
    INFORLOG("Listing...");
    printf("%s", list);
    send(conn_sock, list, BUFF_SIZE, 0);
}

/**
 * @brief This function shows all current games
 * @param conn_sock the socket connects to client
 * @param msg the requested message from client
 */
void process_listg(int conn_sock, message *msg) {
    INFORLOG("Received request listing all games");
}