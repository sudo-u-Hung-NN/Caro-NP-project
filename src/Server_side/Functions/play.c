#include "../server_helper.h"
#include "../Game/game.h"

extern NodeUser *root;

Game* process_play(message *msg, User* current_user) {

    char *opponent_account = getData(msg);
    NodeUser *opponent = search_NodeUser_withAccount(root, opponent_account);

    if (opponent == NULL) {
        WARNING("Failed to find opponent");
        send(current_user->conn_sock, "NULL_OPPONENT", 50, 0);
        return NULL;
    } else if (opponent->is_active != 1) {
        WARNING("Trying to challenge an offline opponent");
        send(current_user->conn_sock, "OFFLINE_OPPONENT", 50, 0);
        return NULL;
    } else {

    }
}