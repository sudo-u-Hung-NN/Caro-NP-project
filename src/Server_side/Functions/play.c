#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;


Game* process_play(message *msg, User* current_user) {

    Game *newgame = NULL;
    char *opponent_account = getData(msg);
    NodeUser *opponent = search_NodeUser_withAccount(root, opponent_account);

    size_t rep_len = sizeof(reply);
    size_t recv_len = sizeof(message);

    if (opponent == NULL) {
        WARNING("Failed to find opponent");
        send(current_user->conn_sock, create_reply(ko, "NULL_ACCOUNT"), rep_len, 0);

    } else if (opponent->is_active != 1) {
        WARNING("Trying to challenge an offline opponent");
        send(current_user->conn_sock, create_reply(ko, "OFFLINE_ACCOUNT"), rep_len, 0);

    } else {
        INFORLOG("Sending invitation");
        char rendered[100];
        bzero(rendered, 100);
        sprintf(rendered, "\033[1;36mCHALLENGE\033[0m from %s", current_user->account);
        
        // Send challenge to opponent
        send(opponent->user->conn_sock, create_reply(play, rendered), rep_len, 0);
        
        
        // Waiting for reply
        INFORLOG("Waiting for acceptance");
        bzero(msg, recv_len);
        recv(opponent->user->conn_sock, msg, recv_len, 0);

        // displayMessage(msg, "Receive reply");
        
        if (msg->command == acpt) {
            // notice the sender
            send(current_user->conn_sock, create_reply(acpt, "ACCEPTED"), rep_len, 0);

            INFORLOG("Received acceptance!");
            
            INFORLOG("Create player 1");
            Player *player1 = initPlayer(current_user);

            INFORLOG("Create player 2");
            Player *player2 = initPlayer(opponent->user);

            INFORLOG("Create new game");
            newgame = initGame(player1, player2);

            INFORLOG("Insert new game into Game Binary Tree");
            game_root = insert_NodeGame(game_root, newgame);

        } else {
            INFORLOG("Received denial!");
            send(current_user->conn_sock, create_reply(deny, "DENIED"), rep_len, 0);
        } 
        
    }

    return newgame;
}