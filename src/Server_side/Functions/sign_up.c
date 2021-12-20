#include "../server_helper.h"


User* process_sign_up(message *msg, int client_sock, int conn_chat_sock) {
    User *newUser = NULL;

    // process message to get account
    char *account = getData(msg);

    // Search User with account
    INFORLOG("Checking valid ...");
    NodeUser *found = search_NodeUser_withAccount(root, account);
    int valid = (found == NULL);
    INFORLOG("done!");

    if (valid) {
        // send CACC_TRUE
        INFORLOG("Sending CACC_TRUE");
        send(client_sock, "CACC_TRUE", 50, 0);

        // recv SIGNPWD <pass>
        memset(msg, 0, sizeof(message));
        INFORLOG("Waiting SIGNPWD");
        recv(client_sock, msg, sizeof(message), 0);

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
        send(client_sock, "REQUEST_ID", 50, 0);

    } else {
        INFORLOG("Send CACC_FALSE");
        send(client_sock, "CACC_FALSE", 50, 0);
    }
    return newUser;
}