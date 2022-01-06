#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;

extern thread_local Player *myself;
extern thread_local Player *rival;


void process_cancel(message *msg, User* current_user) {
    size_t rep_len = sizeof(reply);
    
    if (myself == NULL) {
        WARNING("Trying to excecute cancel while no game was initiated");
        send(current_user->listener, create_reply(ko, "NULL_CANCEL"), rep_len, 0);

    } else {
        Game *current_game = myself->current_game;

        if (current_game == NULL) {
            send(current_user->listener, create_reply(ko, "NULL_CANCEL"), rep_len, 0);
            return;
        } else if (current_game->player1->user != current_user) {
            send(current_user->listener, create_reply(ko, "INVALID_CANCEL"), rep_len, 0);
            return;
        }

        INFORLOG("Closing the game");
        // Free players
        INFORLOG("Free myself");
        free(myself);
        INFORLOG("Free rival");
        free(rival);

        // Free spectators
        INFORLOG("Free spectator");
        free_Spectator_List(current_game);

        // Set game to closed
        NodeGame *game = search_NodeGame_byId(game_root, current_game->id);
        if (game == NULL) {
            WARNING("Trying to close a null game");
        } else {
            game->playing = -1;
        }       
        INFORLOG("Game closed");

        // send cancel to player 2
        send(current_game->player2->user->listener, create_reply(cancel, "CANCELED"), rep_len, 0);

        // send notification to myself
        send(current_user->listener, create_reply(ok, "You have cancel successfully"), rep_len, 0);
    }
}