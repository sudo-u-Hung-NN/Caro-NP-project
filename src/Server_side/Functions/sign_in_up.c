#include "../server_helper.h"

extern NodeUser *root;


User* process_sign_up(int conn_sock, message *msg) {
    User *newUser = NULL;

    // process message to get account
    char *account = getData(msg);

    // Search User with account
    INFORLOG("Checking valid ...");
    NodeUser *found = search_NodeUser_withAccount(root, account);
    int valid = (found != NULL);
    INFORLOG("done!");

    if (valid) {
        // send CACC_TRUE
        INFORLOG("Sending CACC_TRUE");
        send(conn_sock, "CACC_TRUE", 50, 0);

        // recv SIGNPWD <pass>
        memset(msg, 0, sizeof(message));
        INFORLOG("Waiting SIGNPWD");
        recv(conn_sock, msg, sizeof(message), 0);

        // process message to get password
        displayMessage(msg, "Received message");
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

        INFORLOG("Send REQUEST_ID");
        // send REQUEST_ID
        send(conn_sock, "REQUEST_ID", 50, 0);

    } else {
        INFORLOG("Send CACC_FALSE");
        send(conn_sock, "CACC_FALSE", 50, 0);
    }
    return newUser;
}


User* process_sign_in(int conn_sock, message *msg) {
    // process message to get account
    char *account = getData(msg);

    // check valid account
    INFORLOG("Checking user ...");
    NodeUser *found = search_NodeUser_withAccount(root, account);
    int valid = (found != NULL);
    INFORLOG("done!");

    if (valid) {
        // send CACC_TRUE
        INFORLOG("Sending ACC_TRUE");
        send(conn_sock, "ACC_TRUE", 50, 0);

        // recv SIGNPWD <pass>
        memset(msg, 0, sizeof(message));
        INFORLOG("Waiting LOGINPWD");
        recv(conn_sock, msg, sizeof(message), 0);

        // process message to get password
        displayMessage(msg, "Received message");
        char *password = getData(msg);

        // create USer
        INFORLOG("Comparing password...");
        if (ASSERT(password, found->user->password)) {
            INFORLOG("Send PWD_TRUE");
            // send PWD_TRUE
            send(conn_sock, "PWD_TRUE", 50, 0);
            // activate Node User
            found->is_active = 1;
            
            return found->user;
        } else {
            INFORLOG("Send PWD_FALSE");
            // send PWD_FALSE
            send(conn_sock, "PWD_FALSE", 50, 0);
            return NULL;
        }

    } else {
        INFORLOG("Send ACC_FALSE");
        send(conn_sock, "ACC_FALSE", 50, 0);
        return NULL;
    }
}