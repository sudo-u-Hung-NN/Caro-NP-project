#include "../server_helper.h"


User* process_sign_in(message *msg, int client_sock, int conn_chat_sock) {
    // process message to get account
    char *account = getData(msg);

    // check valid account
    INFORLOG("Checking user ...");
    NodeUser *found = search_NodeUser_withAccount(root, account);
    int valid = (found != NULL);
    INFORLOG("done!");

    if (valid) {
        int is_doubled = (found->is_active == 1);
        if (is_doubled) {
            WARNING("An account is accessed from 2 clients, cancel second connect");
            send(client_sock, "DUPLICATED", 50, 0);
            return NULL;
        } 

        // send CACC_TRUE
        INFORLOG("Sending ACC_TRUE");
        send(client_sock, "ACC_TRUE", 50, 0);

        // recv SIGNPWD <pass>
        memset(msg, 0, sizeof(message));
        INFORLOG("Waiting LOGINPWD");
        recv(client_sock, msg, sizeof(message), 0);

        // process message to get password
        // displayMessage(msg, "Received message");
        char *password = getData(msg);

        // activate USer
        INFORLOG("Comparing password...");
        if (ASSERT(password, found->user->password)) {
            INFORLOG("Send PWD_TRUE");
            // send PWD_TRUE
            send(client_sock, "PWD_TRUE", 50, 0);
            // activate Node User
            found->is_active = 1;
            found->user->conn_sock = client_sock;
            found->user->chat_sock = conn_chat_sock;
            return found->user;
        } else {
            INFORLOG("Send PWD_FALSE");
            // send PWD_FALSE
            send(client_sock, "PWD_FALSE", 50, 0);
            return NULL;
        }

    } else {
        INFORLOG("Send ACC_FALSE");
        send(client_sock, "ACC_FALSE", 50, 0);
        return NULL;
    }
}