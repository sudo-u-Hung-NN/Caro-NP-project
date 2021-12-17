#include "../server_helper.h"

extern NodeUser *root;


void checkValidAccount(char *account, NodeUser *root, int* valid) { 
    if (root == NULL) {
        return;
    }
    if (strcmp(root->user->account, account) == 0) {
        *valid = 1;
    }
    checkValidAccount(account, root->left, valid);
    checkValidAccount(account, root->right, valid);
}


User* process_sign_up(int conn_sock, message *msg) {
    User *newUser = NULL;

    // process message to get account
    char *account = getData(msg);

    // check valid account
    int valid = 0;

    INFORLOG("Checking valid ...");
    checkValidAccount(account, root, &valid);
    INFORLOG("done!");

    if (valid) {
        // send CACC_TRUE
        INFORLOG("Sending ACC_TRUE");
        send(conn_sock, "ACC_TRUE", 50, 0);

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
        INFORLOG("Send ACC_FALSE");
        send(conn_sock, "ACC_FALSE", 50, 0);
    }
    
    free(msg);
    return newUser;
}


User* process_sign_in(int conn_sock, message *msg) {
    return NULL;
}