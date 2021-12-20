#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;


Game* process_play(message *msg, User* current_user) {

    Game *newgame = NULL;
    char *opponent_account = getData(msg);
    NodeUser *opponent = search_NodeUser_withAccount(root, opponent_account);

    if (opponent == NULL) {
        WARNING("Failed to find opponent");
        send(current_user->conn_sock, "NULL_ACCOUNT", 50, 0);

    } else if (opponent->is_active != 1) {
        WARNING("Trying to challenge an offline opponent");
        send(current_user->conn_sock, "OFFLINE_ACCOUNT", 50, 0);

    } else {
        INFORLOG("Sending invitation");
        char rendered[100];
        bzero(rendered, 100);
        sprintf(rendered, "\033[1;36mCHALLENGE\033[0m from %s", current_user->account);
        
        // Send challenge to opponent
        send(opponent->user->conn_sock, rendered, 100, 0);
        
        int recv_len = sizeof(message);
        bzero(msg, recv_len);

        // Waiting for reply
        INFORLOG("Waiting for acceptance");
        recv(opponent->user->conn_sock, msg, recv_len, 0);

        displayMessage(msg, "Receive reply");
        
        if (msg->command == acpt) {
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
            send(current_user->conn_sock, "DENIED", 50, 0);
        } 
        
    }

    return newgame;
}