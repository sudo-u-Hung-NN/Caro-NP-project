#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;

extern thread_local Player *myself;
extern thread_local Player *rival;

void process_deny(message *msg, User* current_user) {
    send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}