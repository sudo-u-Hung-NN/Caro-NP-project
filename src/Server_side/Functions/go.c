#include "../server_helper.h"
#include "ctype.h"


void make_move(Player* current_player, Player *opponent_player, Game* game, message *msg) {
    if (current_player->role == game->turn) {
        char *move = getData(msg);
        if (isalpha(move[0]) && isdigit(move[1])) {
            int row = (int)move[0] - 65;
            int col = (int)move[1] - 48;
            if (isValid(game, row, col)) {
                INFORLOG("Player made his move");
                loadGame(game, game->turn, row, col);

                if (checkWin(game, row, col)) {
                    send(current_player->user->listener, create_reply(done, "WIN"), sizeof(reply), 0);
                    send(opponent_player->user->listener, create_reply(done, "LOSE"), sizeof(reply), 0);
                    INFORLOG("Game completed");
                    return;
                }
                char *screen = loadGameScreen(game);
                send(current_player->user->listener, create_reply(ok, screen), sizeof(reply), 0);
                send(opponent_player->user->listener, create_reply(ok, screen), sizeof(reply), 0);

            } else {
                send(current_player->user->listener, create_reply(ko, "INVALID_MOVE"), sizeof(reply), 0);
                send(current_player->user->listener, create_reply(ok, "YOUR_TURN"), sizeof(reply), 0);
                WARNING("Invalid move detected");
                return;
            }

        } else {
            WARNING("False format detected");
            send(current_player->user->listener, create_reply(ko, "FALSE_FORMAT"), sizeof(reply), 0);
            send(current_player->user->listener, create_reply(ok, "YOUR_TURN"), sizeof(reply), 0);
            return;
        }

    } else {
        WARNING("Wrong turn detected");
        send(current_player->user->listener, create_reply(ko, "OPPONENT_TURN"), sizeof(reply), 0);
    }
}


void process_go(message *msg, User* current_user, Game *game) {
    if (game->player1->user == current_user) {
        Player *current_player = game->player1;
        Player *opponent_player = game->player2;
        make_move(current_player, opponent_player, game, msg);

    } else if (game->player2->user == current_user) {
        Player *current_player = game->player2;
        Player * opponent_player = game->player1;
        make_move(current_player, opponent_player, game, msg);
    }
}