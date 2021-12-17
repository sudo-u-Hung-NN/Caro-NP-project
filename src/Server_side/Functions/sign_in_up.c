#include "../server_helper.h"

extern NodeUser *root;

User* process_sign_up(int conn_sock) {

    message *msg = (message*) malloc (sizeof(message));
    User *newUser = NULL;
	int bytes_sent, bytes_received;

    // send REQUEST_ID
    bytes_sent = send(conn_sock, "REQUEST_ID", 50, 0);          

    // recv SIGN_IN <account>
    bzero(msg, sizeof(msg));
    bytes_received = recv(conn_sock, msg, sizeof(msg), 0);

    // process message to get account
    char *account = getData(msg);

    // check valid account
    int valid = 0; //checkValidAccount(account);

    if (valid) {
        // send CACC_TRUE
        bytes_sent = send(conn_sock, "ACC_TRUE", 50, 0);

        // recv SIGNPWD <pass>
        bzero(msg, sizeof(msg));
        bytes_received = recv(conn_sock, msg, sizeof(msg), 0);

        // process message to get password
        char *password = getData(msg);

        // create USer
        int number_user = 0;
        inOrderTraversal(root, &number_user, 0);
        newUser = create_User(number_user, "#newUser", account, password);

        // insert User to Binary Tree
        root = insert_NodeUser(root, newUser, 0);

        // send REQUEST_ID
        bytes_sent = send(conn_sock, "REQUEST_ID", 50, 0);

    } else {
        bytes_sent = send(conn_sock, "ACC_FALSE", 50, 0);
    }
    
    free(msg);
    return newUser;
}


int sign_in();