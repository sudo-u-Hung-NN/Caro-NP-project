#include "../server_helper.h"

extern NodeGame *game_root;

extern thread_local Player *myself;
extern thread_local Player *rival;

void process_draw(message *msg, User* current_user) {
    size_t rep_len = sizeof(reply);
    Game *game = myself->current_game;
    
    myself->draw = 1;
    send(myself->user->listener, create_reply(ok, "DRAW_REQUEST_SENT"), rep_len, 0);
    send(rival->user->listener, create_reply(ok, "DRAW_REQUEST"), rep_len, 0);

    if (myself->draw && rival->draw) {
        INFORLOG("Agreement to draw");
        // Notify players
        if(send(myself->user->listener, create_reply(draw, "DRAW"), rep_len, 0) <= 0) {
            WARNING("FAILED TO SEND DRAW 1");
        }
        if(send(rival->user->listener, create_reply(draw, "DRAW"), rep_len, 0) <= 0) {
            WARNING("FAILED TO SEND DRAW 2");
        }

        // Notify spectators
        for (Spectator *tmp = game->spectator_head; tmp != NULL; tmp = tmp->next) {
            send(tmp->user->listener, create_reply(done, "The game ends tie"), rep_len, 0);
        }
        
        store_history(current_user, (rival->user), game);
        INFORLOG("Closing the game");
        // Free players
        free(myself);
        free(rival);
        free_Spectator_List(game);

        NodeGame *current_game = search_NodeGame_byId(game_root, game->id);
        if (current_game == NULL) {
            WARNING("Trying to close a null game");
        } else {
            current_game->playing = -1;
        }
        
        INFORLOG("Game closed");
    }
    
}