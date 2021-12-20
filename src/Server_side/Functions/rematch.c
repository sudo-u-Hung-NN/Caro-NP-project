#include "../server_helper.h"

void process_rematch(message *msg, User* current_user) {
    send(current_user->conn_sock, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}