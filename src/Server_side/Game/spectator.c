#include "game.h"

/**
 * @brief Create new spectator
 * @param current_user 
 * @param current_game 
 * @return Spectator* 
 */
Spectator *new_Spectator(User *current_user, Game* current_game) {
    Spectator *new = (Spectator*) malloc(sizeof(Spectator));
    new->current_game = current_game;
    new->user = current_user;
    new->next = NULL;
    return new;
}


/**
 * @brief Insert new spectator into link list
 * @param current_game 
 * @return Spectator* 
 */
Spectator *insert_Spectator(Spectator* cureent_user, Game* current_game) {
    Spectator *head = current_game->spectator_head;
    if (head == NULL) {
        head = cureent_user;
    } else {
        Spectator *tmp = cureent_user;
        tmp->next = head;
        head = tmp;
    }
    return head;
}


/**
 * @brief If the spectator use squit, remove spectator from the list
 * @param current_game 
 * @param current_user 
 * @return Spectator* 
 */
Spectator *remove_Spectator(Game* current_game, User *current_user) {
    Spectator *head = current_game->spectator_head;
    if (head == NULL) {
        return head;

    } else if (head->user == current_user) {
        Spectator *tmp = head;
        head = head->next;
        free(tmp);

    } else {
        Spectator *tmp = head;
        for (; tmp->next->user != current_user; tmp = tmp->next);
        // Here, tmp->next is the one to be deleted
        Spectator *need_deleted = tmp->next;
        // Process deleting
        tmp->next = need_deleted->next;
        free(need_deleted);
    }

    return head;
}


void free_Spectator(Spectator *head) {
    if(head == NULL) {
        return;
    }
    free_Spectator(head->next);
    free(head);
}


/**
 * @brief The game is over, free entire spectator list
 * @param current_game 
 * @return Spectator* 
 */
Spectator *free_Spectator_List(Game* current_game) {
    Spectator *head = current_game->spectator_head;
    free_Spectator(head);
    return head;
}