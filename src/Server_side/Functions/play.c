#include "../server_helper.h"

extern NodeUser *root;              // Global
extern NodeGame *game_root;         // Global


thread_local Player *myself = NULL;
thread_local Player *rival = NULL;
thread_local Spectator *my_spectator = NULL;


void process_play(message *msg, User* current_user) {

    char *opponent_account = getData(msg);
    NodeUser *opponent = search_NodeUser_withAccount(root, opponent_account);

    size_t rep_len = sizeof(reply);

    if (opponent == NULL) {
        WARNING("Failed to find opponent");
        send(current_user->listener, create_reply(done, "NULL_ACCOUNT"), rep_len, 0);

    } else if (opponent->is_active != 1) {
        WARNING("Trying to challenge an offline opponent");
        send(current_user->listener, create_reply(ko, "OFFLINE_ACCOUNT"), rep_len, 0);

    } else if (opponent->user == current_user) {
        WARNING("Self challenging detected!");
        send(current_user->listener, create_reply(done, "LOOP_OPERATOR"), rep_len, 0); 

    } else {
        // Init myself
        myself = initPlayer(current_user, 'X');
        rival = initPlayer(opponent->user, 'O');

        // Create new game
        INFORLOG("Create new game");
        Game *newgame = initGame(myself, rival);

        if (newgame != NULL) {
            newgame->turn = 'X';
            // Link players to game
            myself->current_game = newgame;
            rival->current_game = newgame;

            // Insert new game into Game Tree
            INFORLOG("Insert new game into Game Binary Tree");
            game_root = insert_NodeGame(game_root, newgame);

            // Render invitation
            INFORLOG("Sending invitation");
            char rendered[150];
            bzero(rendered, 150);
            sprintf(rendered, "\033[1;36mCHALLENGE\033[0m from %s, game id %d (use \033[0;33mACCEPT %d\033[0m or \033[0;33mDENY %d\033[0m)\n", 
                    current_user->account,
                    newgame->id, 
                    newgame->id, 
                    newgame->id);
            
            // Send challenge to opponent
            send(opponent->user->listener, create_reply(play, rendered), rep_len, 0);
            send(current_user->listener, create_reply(ok, "CHALLENGE_SENT"), rep_len, 0);

            INFORLOG("Waiting for acceptance");

        } else {
            WARNING("Failed to create new game");
            send(current_user->listener, create_reply(ko, "GAME_FAILED"), rep_len, 0);
            free(myself);
            free(rival);
        }
    }
}