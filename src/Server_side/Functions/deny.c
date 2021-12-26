#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;


void process_deny(message *msg, User* current_user) {
    size_t rep_len = sizeof(reply);
    
    // get game id
    int game_id = atoi(getData(msg));

    // get game by id
    NodeGame *nodegame = search_NodeGame_byId(game_root, game_id);

    if (nodegame == NULL) {
        WARNING("Accept a non-existing game");
        send(current_user->listener, create_reply(ko, "GAME_FAILED"), rep_len, 0);

    } else {
        // Destroy the game
        free(nodegame->game->player1);
        free(nodegame->game->player2);
        free(nodegame->game);
        close_NodeGame_byId(game_root, game_id);

        // send deny to the sender
        send(nodegame->game->player1->user->listener, create_reply(deny, "DENIED"), rep_len, 0);

        // send notification to myself
        send(current_user->listener, create_reply(ok, "You have denied successfully"), rep_len, 0);
    }

    // send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}