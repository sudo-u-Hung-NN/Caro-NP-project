#include "../server_helper.h"

void process_return(message *msg, User* current_user) {
    send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}