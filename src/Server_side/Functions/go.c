#include "../server_helper.h"
#include "ctype.h"

extern thread_local Player *myself;
extern thread_local Player *rival;

void process_go(message *msg, User* current_user) {

    if (myself == NULL || rival == NULL) {
        WARNING("Using go without a game");
        send(current_user->listener, create_reply(ko, "NO_GAME"), sizeof(reply), 0);

    } else {
        Game *current_game = myself->current_game;
        size_t rep_len = sizeof(reply);

        printf("Turn %c, myself role %c, viral role %c\n", current_game->turn, myself->role, rival->role);
        if (myself->role == current_game->turn) {
            
            char *move = getData(msg);
            if (isalpha(move[0]) && isdigit(move[1])) {
                int row = (int)toupper(move[0]) - 65;
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

                    send(myself->user->listener, create_reply(scrn, board), rep_len, 0);
                    send(rival->user->listener, create_reply(scrn, board), rep_len, 0);

                    INFORLOG("Here check done");
                    int done = checkWin(current_game, row, col);
                    INFORLOG("Check done ok");

                    if (done) {
                        send(myself->user->listener, create_reply(done, "WIN"), rep_len, 0);
                        send(rival->user->listener, create_reply(done, "LOSE"), rep_len, 0);
                        INFORLOG("Game completed");
                        return;
                    }

                    send(myself->user->listener, create_reply(ok, "OPPONENT_TURN"), rep_len, 0);
                    send(rival->user->listener, create_reply(ok, "YOUR_TURN"), rep_len, 0);

                } else {
                    send(myself->user->listener, create_reply(ko, "INVALID_MOVE"), rep_len, 0);
                    send(myself->user->listener, create_reply(ok, "YOUR_TURN"), rep_len, 0);
                    WARNING("Invalid move detected");
                    return;
                }

            } else {
                WARNING("False format detected");
                send(myself->user->listener, create_reply(ko, "FALSE_FORMAT"), rep_len, 0);
                send(myself->user->listener, create_reply(ok, "YOUR_TURN"), rep_len, 0);
                return;
            }

        } else {
            WARNING("Wrong turn detected");
            send(myself->user->listener, create_reply(ko, "OPPONENT_TURN"), rep_len, 0);
        }
    }
}