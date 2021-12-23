#include "../server_helper.h"
#include "ctype.h"

extern Player *myself;
extern Player *rival;

void process_go(message *msg, User* current_user) {

    if (myself == NULL || rival == NULL) {
        WARNING("Using go without a game");
        send(current_user->listener, create_reply(ko, "NO_GAME"), sizeof(reply), 0);

    } else {
        Game *current_game = myself->current_game;
        if (myself->role == current_game->turn) {
            
            char *move = getData(msg);
            if (isalpha(move[0]) && isdigit(move[1])) {
                int row = (int)move[0] - 65;
                int col = (int)move[1] - 48;
                INFORLOG("Here check valid");
                int valid = isValid(current_game, row, col);
                INFORLOG("Valid check ok");

                if (valid) {
                    INFORLOG("Player made his move");
                    loadGame(current_game, current_game->turn, row, col);

                    current_game->turn = (current_game->turn == 'X') ? 'O' : 'X';

                    char board[SIZE * SIZE];
                    memcpy(board, current_game->board, SIZE* SIZE);

                    send(myself->user->listener, create_reply(scrn, board), sizeof(reply), 0);
                    send(rival->user->listener, create_reply(scrn, board), sizeof(reply), 0);

                    INFORLOG("Here check done");
                    int done = checkWin(current_game, row, col);
                    INFORLOG("Check done ok");

                    if (done) {
                        send(myself->user->listener, create_reply(done, "WIN"), sizeof(reply), 0);
                        send(rival->user->listener, create_reply(done, "LOSE"), sizeof(reply), 0);
                        INFORLOG("Game completed");
                        return;
                    }

                } else {
                    send(myself->user->listener, create_reply(ko, "INVALID_MOVE"), sizeof(reply), 0);
                    send(myself->user->listener, create_reply(ok, "YOUR_TURN"), sizeof(reply), 0);
                    WARNING("Invalid move detected");
                    return;
                }

            } else {
                WARNING("False format detected");
                send(myself->user->listener, create_reply(ko, "FALSE_FORMAT"), sizeof(reply), 0);
                send(myself->user->listener, create_reply(ok, "YOUR_TURN"), sizeof(reply), 0);
                return;
            }

        } else {
            WARNING("Wrong turn detected");
            send(myself->user->listener, create_reply(ko, "OPPONENT_TURN"), sizeof(reply), 0);
        }
    }
}