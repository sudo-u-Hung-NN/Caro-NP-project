#include "../server_helper.h"

extern NodeUser *root;

extern thread_local Spectator *my_spectator;

void process_quit(message *msg, User* current_user) {
    if (current_user == NULL) {
        return;
    }
    //If spectator request quit
    if (my_spectator != NULL) {
        msg->command = squit;
        process_squit(msg, current_user);
    }
    NodeUser *self = search_NodeUser_withAccount(root, current_user->account);
    if (self != NULL) {
        self->is_active = 0;
        INFORLOG("Process quit successfully");
    } else {
        WARNING("Can not find myself in the tree");
    }
}