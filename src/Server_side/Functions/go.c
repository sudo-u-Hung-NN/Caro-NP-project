#include "../server_helper.h"

void process_go(message *msg, User* current_user, Game *game) {
    send(current_user->conn_sock, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}