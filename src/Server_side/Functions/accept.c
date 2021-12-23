#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;

extern Player *myself;
extern Player *rival;

void process_accept(message *msg, User* current_user) {

    size_t rep_len = sizeof(reply);
    
    // notice the sender
    send(current_user->listener, create_reply(acpt, "ACCEPTED"), rep_len, 0);
    
    // get game id
    int game_id = atoi(getData(msg));

    // get game by id
    NodeGame *nodegame = search_NodeGame_byId(game_root, game_id);

    if (nodegame == NULL) {
        WARNING("Accept a non-existing game");
        send(current_user->listener, create_reply(ko, "GAME_FAILED"), rep_len, 0);

    } else {
        Game *opened_game = nodegame->game;

        if(myself == NULL) {
            myself = opened_game->player2;

        } else {
            WARNING("Myself is participating ?");
            return;
        }

        if (rival == NULL) {
            rival = opened_game->player1; 

        } else {
            WARNING("Trying to reassign your current opponent");
            return;
        }

        char board[SIZE * SIZE];
        memcpy(board, opened_game->board, SIZE* SIZE);

        INFORLOG("Sending board");
        send(myself->user->listener, create_reply(scrn, board), rep_len, 0);
        send(rival->user->listener, create_reply(scrn, board), rep_len, 0);
        INFORLOG("Initial board sent");

        sleep(5000);

        send(myself->user->listener, create_reply(ok, "GAME_CREATED_X"), rep_len, 0);
        send(rival->user->listener, create_reply(ok, "GAME_CREATED_O"), rep_len, 0);

        send(myself->user->listener, create_reply(ok, "YOUR_TURN"), rep_len, 0);
        send(rival->user->listener, create_reply(ok, "OPPONENT_TURN"), rep_len, 0);   
    }
}