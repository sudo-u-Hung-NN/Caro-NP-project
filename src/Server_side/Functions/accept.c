#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;

extern thread_local Player *myself;
extern thread_local Player *rival;

void process_accept(message *msg, User* current_user) {

    size_t rep_len = sizeof(reply);
    
    // get game id
    int game_id = atoi(getData(msg));

    // get game by id
    NodeGame *nodegame = search_NodeGame_byId(game_root, game_id);

    if (nodegame == NULL) {
        WARNING("Accept a non-existing game");
        send(current_user->listener, create_reply(ko, "GAME_FAILED"), rep_len, 0);

    } else {
        Game *opened_game = nodegame->game;

        myself = opened_game->player2;
        rival = opened_game->player1;

        if (myself == rival) {
            WARNING("What the heck");
        }

        // notice the sender
        send(rival->user->listener, create_reply(acpt, "ACCEPTED"), rep_len, 0);

        char board[SIZE * SIZE];
        memcpy(board, opened_game->board, SIZE* SIZE);

        INFORLOG("Sending board");
        send(myself->user->listener, create_reply(scrn, board), rep_len, 0);
        send(rival->user->listener, create_reply(scrn, board), rep_len, 0);
        INFORLOG("Initial board sent");  

        send(myself->user->listener, create_reply(ok, "OPPONENT_TURN"), rep_len, 0);
        send(rival->user->listener, create_reply(ok, "YOUR_TURN"), rep_len, 0);
    }
}