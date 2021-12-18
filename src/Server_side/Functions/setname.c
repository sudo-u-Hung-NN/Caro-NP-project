#include "../server_helper.h"

void process_setname(int conn_sock, message *msg, User* current_user) {
    char* newname = getData(msg);
    strcpy(current_user->name, newname);
    send(conn_sock, "SETNAME_SUCESS", 50, 0);
}