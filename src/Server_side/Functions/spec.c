#include "../server_helper.h"

void process_spec(message *msg, User* current_user) {
    send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}


void process_schat(message *msg, User* current_user) {
    send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}


void process_squit(message *msg, User* current_user) {
    send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}