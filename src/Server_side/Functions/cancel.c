#include "../server_helper.h"

void process_cancel(message *msg, User* current_user) {
    send(current_user->conn_sock, "ON_DEVELOP", 50, 0);
}