#include "../server_helper.h"

void process_setname(message *msg, User* current_user) {
    char* newname = getData(msg);
    strcpy(current_user->name, newname);
    send(current_user->conn_sock, create_reply(ok, "SETNAME_SUCESS"), sizeof(reply), 0);
}