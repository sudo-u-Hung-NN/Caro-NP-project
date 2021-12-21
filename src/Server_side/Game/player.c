#include "game.h"

Player* initPlayer(const User *user, char role) {
    Player *player = (Player*) malloc(sizeof(Player));
    if (player == NULL) {
        printf("Can't allocate!\n");
        exit(0);
    }
    player->user = user;
    player->role = role;
    player->score = 0;
    player->draw = 0;
    return player;
}