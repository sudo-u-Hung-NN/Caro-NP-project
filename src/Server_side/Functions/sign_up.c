#include "../server_helper.h"


User* process_sign_up(message *msg, int client_listener_sock, int client_speaker_sock) {
    User *newUser = NULL;

    // process message to get account
    char *account = getData(msg);

    // Search User with account
    INFORLOG("Checking valid ...");
    NodeUser *found = search_NodeUser_withAccount(root, account);
    int valid = (found == NULL);
    INFORLOG("done!");

    // Create reply
    size_t rep_len = sizeof(reply);

    if (valid) {
        // send CACC_TRUE
        INFORLOG("Sending CACC_TRUE");
        send(client_listener_sock, create_reply(ok, "CACC_TRUE"), rep_len, 0);

        // recv SIGNPWD <pass>
        memset(msg, 0, sizeof(message));
        INFORLOG("Waiting SIGNPWD");
        recv(client_listener_sock, msg, sizeof(message), 0);

        // process message to get password
        // displayMessage(msg, "Received message");
        char *password = getData(msg);

        // create USer
        int number_user = 0;
        INFORLOG("Generate id...");
        inOrderTraversal(root, &number_user, 0);
        INFORLOG("Creating new user...");
        newUser = create_User(number_user, "#newUser", account, password);

        INFORLOG("Insert user into tree");
        // insert User to Binary Tree
        root = insert_NodeUser(root, newUser, 0);
        inOrderTraversal(root, NULL, 1);
        INFORLOG("Insert done");

        INFORLOG("Send REQUEST_ID");
        // send REQUEST_ID
        send(client_listener_sock, create_reply(ok, "REQUEST_ID"), rep_len, 0);

    } else {
        INFORLOG("Send CACC_FALSE");
        send(client_listener_sock, create_reply(ko, "CACC_FALSE"), rep_len, 0);
        
    }

    return newUser;
}