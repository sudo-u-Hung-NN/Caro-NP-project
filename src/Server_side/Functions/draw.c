#include "../server_helper.h"

extern NodeGame *game_root;

extern thread_local Player *myself;
extern thread_local Player *rival;

void process_draw(message *msg, User* current_user) {
    size_t rep_len = sizeof(reply);
    Game *game = myself->current_game;
    
    myself->draw = 1;

    if (myself->draw && rival->draw) {
        INFORLOG("Agreement to draw");
        send(myself->user->listener, create_reply(acpt, "DRAW"), rep_len, 0);
        send(rival->user->listener, create_reply(acpt, "DRAW"), rep_len, 0);

        INFORLOG("Closing the game");
        free(myself);
        free(rival);
        close_NodeGame_byId(game_root, game->id);
        INFORLOG("Game closed");
    }
    
}