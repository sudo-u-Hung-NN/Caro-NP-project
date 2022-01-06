#include "../server_helper.h"

extern NodeUser* root;
extern NodeGame* game_root;

void traverse(NodeUser *root, char* buffer) {
    if (root == NULL || strlen(buffer) + 150 > rep_instruct_len) {
        return;
    }
    char formatted_string[150] = "\0";
    traverse(root->left, buffer);
    if (root->is_active) {
        sprintf(formatted_string, "%3d \033[0;32m%-10s\033[0m %-10s \033[1;34m%-5s\033[0m\n", root->user->id, root->user->account, root->user->name, "ONLINE");
    } else {
        sprintf(formatted_string, "%3d \033[0;32m%-10s\033[0m %-10s \033[0;31m%-5s\033[0m\n", root->user->id, root->user->account, root->user->name, "OFFLINE");
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


void traverse_game(NodeGame *game_root, char* buffer) {
    if (game_root == NULL || strlen(buffer) + 1 > rep_instruct_len) {
        return;
    }
    char formatted_string[200] = "\0";
    traverse_game(game_root->left, buffer);
    
    switch (game_root->playing) {
        case 0:
            sprintf(formatted_string, "%3d \033[1;32m%-15s\033[0m \033[1;32m%-15s\033[0m %-3d\033[1;32m%9s\033[0m\n", 
                                game_root->game->id, 
                                game_root->game->player1->user->account,
                                game_root->game->player2->user->account,
                                game_root->game->number_spectator,
                                "PENDING");
            break;
        case 1:
            sprintf(formatted_string, "%3d \033[1;32m%-15s\033[0m \033[1;32m%-15s\033[0m %-3d\033[1;32m%9s\033[0m\n", 
                                game_root->game->id, 
                                game_root->game->player1->user->account,
                                game_root->game->player2->user->account,
                                game_root->game->number_spectator,
                                "PLAYING");
            break;
        case -1:
            sprintf(formatted_string, "%3d \033[1;32m%-15s\033[0m \033[1;32m%-15s\033[0m %-3d\033[1;32m%9s\033[0m\n", 
                                game_root->game->id, 
                                "No one",
                                "No one",
                                0, 
                                "CLOSED");
            break;
        default:
            break;
    }

    strcat(buffer, formatted_string);
    traverse_game(game_root->right, buffer);
}


/**
 * @brief This function shows all current games
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_listg(message *msg, User* current_user) {
    INFORLOG("Received request listing all games");
    
    char list[rep_instruct_len];
    bzero(list, rep_instruct_len);

    char formatted_string[128] = "\0";
    sprintf(formatted_string, "\n%3s %-15s %-15s %5s %10s\n", "Id", "Player1", "Player2", "Specs", "Status");
    strcat(list, formatted_string);

    traverse_game(game_root, list);

    send(current_user->listener, create_reply(ko, list), sizeof(reply), 0);
}