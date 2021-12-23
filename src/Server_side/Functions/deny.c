#include "../server_helper.h"

extern NodeUser *root;
extern NodeGame *game_root;

extern Player *myself;
extern Player *rival;

void process_deny(message *msg, User* current_user) {
    send(current_user->listener, create_reply(ko, "ON_DEVELOP"), sizeof(reply), 0);
}