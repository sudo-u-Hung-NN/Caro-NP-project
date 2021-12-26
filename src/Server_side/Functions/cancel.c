#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;


void process_cancel(message *msg, User* current_user) {
    size_t rep_len = sizeof(reply);
    
    // get game id
    int game_id = atoi(getData(msg));

    // get game by id
    NodeGame *nodegame = search_NodeGame_byId(game_root, game_id);

    if (nodegame == NULL) {
        send(current_user->listener, create_reply(ko, "NULL_CANCEL"), rep_len, 0);
        return;
    } else if (nodegame->game->player1->user != current_user) {
        send(current_user->listener, create_reply(ko, "INVALID_CANCEL"), rep_len, 0);
        return;
    }

    // Destroy the game
    free(nodegame->game->player1);
    free(nodegame->game->player2);
    free(nodegame->game);
    close_NodeGame_byId(game_root, game_id);

    // send cancel to player 2
    send(nodegame->game->player2->user->listener, create_reply(cancel, "CANCELED"), rep_len, 0);

    // send notification to myself
    send(current_user->listener, create_reply(ok, "You have cancel successfully"), rep_len, 0);

    // send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}