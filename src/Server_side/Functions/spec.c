#include "../server_helper.h"

Game * process_spec(message *msg, User* current_user) {
    send(current_user->conn_sock, "ON_DEVELOP", 50, 0);
    return NULL;
}


void process_schat(message *msg, User* current_user, Game* game) {
    send(current_user->conn_sock, "ON_DEVELOP", 50, 0);
}


void process_squit(message *msg, User* current_user, Game* game) {
    send(current_user->conn_sock, "ON_DEVELOP", 50, 0);
}