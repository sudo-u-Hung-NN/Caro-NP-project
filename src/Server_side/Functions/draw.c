#include "../server_helper.h"

extern NodeGame *game_root;

extern thread_local Player *myself;
extern thread_local Player *rival;

void process_draw(message *msg, User* current_user) {
    size_t rep_len = sizeof(reply);
    Game *game = myself->current_game;
    
    myself->draw = 1;
    send(myself->user->listener, create_reply(ok, "DRAW_REQUEST_SENT"), rep_len, 0);
    send(rival->user->listener, create_reply(draw, "DRAW_REQUEST"), rep_len, 0);

    if (myself->draw && rival->draw) {
        INFORLOG("Agreement to draw");
        // Notify players
        send(myself->user->listener, create_reply(acpt, "DRAW"), rep_len, 0);
        send(rival->user->listener, create_reply(acpt, "DRAW"), rep_len, 0);

        // Notify spectators
        for (Spectator *tmp = game->spectator_head; tmp != NULL; tmp = tmp->next) {
            send(tmp->user->listener, create_reply(done, "The game ends tie"), rep_len, 0);
        }
        
        INFORLOG("Closing the game");
        // Free players
        free(myself);
        free(rival);
        game_root = close_NodeGame_byId(game_root, game->id);
        free(game);
        INFORLOG("Game closed");
    }
    
}