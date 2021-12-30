#include "../server_helper.h"

extern NodeGame *game_root;
extern NodeUser *root;
extern thread_local Player *myself;


void process_spec(message *msg, User* current_user) {
    int game_id = atoi(getData(msg));
    NodeGame* spec_game = search_NodeGame_byId(game_root, game_id);
    size_t rep_len = sizeof(reply);

    if (spec_game == NULL) {
        WARNING("Request to spectate a null game");
        send(current_user->listener, create_reply(ko, "NULL_SPEC"), rep_len, 0);

    } else {
        INFORLOG("Insert spectator into game");
        spec_game->game->spectator_head = insert_Spectator(current_user, spec_game->game);

        char board[SIZE * SIZE];
        memcpy(board, spec_game->game->board, SIZE* SIZE);
        send(current_user->listener, create_reply(scrn, board), rep_len, 0);
    }
}


void process_schat(message *msg, User* current_user) {
    char *content = getData(msg);
    if (myself == NULL) {
        send(current_user->listener, create_reply(ko, "NULL_SCHAT"), sizeof(reply), 0);
    } else {
        Game *current_game = myself->current_game;
        INFORLOG("Sending messages to all people");
        char rendered[rep_instruct_len];
        bzero(rendered, rep_instruct_len);
        size_t rep_len = sizeof(reply);

        // Send message to players
        sprintf(rendered, "Spectator \033[1;32m%s\033[0m: %s", current_user->account, content);
        send(current_game->player1->user->listener, create_reply(chat, rendered), rep_len, 0);
        send(current_game->player2->user->listener, create_reply(chat, rendered), rep_len, 0);

        // Send to other spectators
        for (Spectator *tmp = current_game->spectator_head; tmp != NULL; tmp = tmp->next) {
            if (tmp->user != current_user) {
                send(tmp->user->listener, create_reply(chat, rendered), rep_len, 0);
            }
        }

        INFORLOG("Sent message successfully");
    }
}


void process_squit(message *msg, User* current_user) {
    if (myself != NULL) {
        Game *current_game = myself->current_game;

        INFORLOG("Removing spectator out of the game");
        current_game->spectator_head = remove_Spectator(current_game, current_user);

        // Notify
        char rendered[rep_instruct_len];
        bzero(rendered, rep_instruct_len);
        size_t rep_len = sizeof(reply);

        // Send message to players
        sprintf(rendered, "Spectator \033[1;32m%s\033[0m: %s", current_user->account, "has left the game!");
        send(current_game->player1->user->listener, create_reply(ok, rendered), rep_len, 0);
        send(current_game->player2->user->listener, create_reply(ok, rendered), rep_len, 0);

        for (Spectator *tmp = current_game->spectator_head; tmp != NULL; tmp = tmp->next) {
            send(tmp->user->listener, create_reply(ok, rendered), rep_len, 0);
        }

        send(current_user->listener, create_reply(ok, "SQUIT_SUCCESS"), rep_len, 0);
        INFORLOG("Removed spectator");

    } else {
        send(current_user->listener, create_reply(ko, "You're not spectating any games"), sizeof(reply), 0);
    }
}