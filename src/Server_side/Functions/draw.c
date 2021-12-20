#include "../server_helper.h"

void process_draw(message *msg, User* current_user, Game *game) {
    send(current_user->conn_sock, "ON_DEVELOP", 50, 0);
}