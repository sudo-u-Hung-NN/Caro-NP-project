#include <stdio.h>
#include <string.h>

typedef struct Player
{
    int id;
    int score;
    char name[30];
    int draw;
} Player;

Player* initPlayer(char name[30]) {
    Player *player = (Player*) malloc(sizeof(Player));
    if (player == NULL) {
        printf("Can't allocate!\n");
        exit(0);
    }
    strcat(player->name, name);
    player->score = 0;
    player->draw = 0;
    return player;
}

void setName(Player* player, char newName[30]) {
    strcpy(player->name, newName);
}