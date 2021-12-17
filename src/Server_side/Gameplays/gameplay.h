#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include "../Users/user.h"

typedef struct {
    int gameplay_id;            // game's id
    User *first_place;          // winner
    User *second_place;         // loser
    int duration;               // number of transitions
    int first_place_go_first;   // If winner plays 'X' then TRUE
} Gameplay;


typedef struct {
    Gameplay *record;
    NodeGameplay *left;
    NodeGameplay *right;
} NodeGameplay;



NodeGameplay *newRecord(int game_id, User *first_place, User *second_place, int duration, int first_place_go_first) {
    // Create new game record
    Gameplay* tmp = (Gameplay*) malloc(sizeof(Gameplay));
    tmp->gameplay_id = game_id;
    tmp->first_place = first_place;
    tmp->second_place = second_place;
    tmp->duration = duration;
    tmp->first_place_go_first = first_place_go_first;

    // Create new game record node
    NodeGameplay* tmp_node = (NodeGameplay*) malloc(sizeof(NodeGameplay));
    tmp_node->record = tmp;

    return tmp_node;
}

#endif