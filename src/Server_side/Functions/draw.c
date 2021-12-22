#include "../server_helper.h"

extern NodeGame *game_root;

void process_draw(message *msg, User* current_user, Game *game) {
    size_t rep_len = sizeof(reply);
    
    if (current_user == game->player1->user) {
        game->player1->draw = 1;
        send(game->player2->user->listener, create_reply(ok, "DRAW_REQUEST"), rep_len, 0);
    } else {
        game->player2->draw = 1;
        send(game->player1->user->listener, create_reply(ok, "DRAW_REQUEST"), rep_len, 0);
    }

    if (game->player1->draw && game->player2->draw) {
        INFORLOG("Agreement to draw");
        send(game->player2->user->listener, create_reply(acpt, "DRAW"), rep_len, 0);
        send(game->player2->user->listener, create_reply(acpt, "DRAW"), rep_len, 0);

        INFORLOG("Closing the game");
        close_NodeGame_byId(game_root, game->id);
        INFORLOG("Game closed");
    }
    
}