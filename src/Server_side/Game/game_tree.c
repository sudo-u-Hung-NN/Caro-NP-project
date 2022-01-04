#include "game.h"

int total_game = 0;

NodeGame *create_NodeGame(Game *game) {
    // NodeGame *tmp = (NodeGame*) malloc (sizeof(NodeGame));
    NodeGame *tmp = (NodeGame*) mmap (NULL, sizeof(NodeGame), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    tmp->playing = 0; // 0: Pending; 1: Playing; -1: Closed
    tmp->game = game;
    tmp->left = NULL;
    tmp->right = NULL;
    return tmp;
}


NodeGame *insert_NodeGame(NodeGame *game_root, Game *game) {
    if (game_root == NULL) {

        game_root = create_NodeGame(game);
    } else if (game->id > game_root->game->id) {

        game_root->right = insert_NodeGame(game_root->right, game);
    } else if (game->id < game_root->game->id) {

        game_root->left = insert_NodeGame(game_root->left, game);
    } else {
        WARNING("Trying to create a game that existed");
        return NULL;
    }
    return game_root;
}


NodeGame *search_NodeGame_byId(NodeGame *game_root, int id) {
    if (game_root == NULL) {
        return NULL;
    } else if (id > game_root->game->id) {
        printf("Here right: game id = %d\n", game_root->game->id);
        return search_NodeGame_byId(game_root->right, id);
    } else if (id < game_root->game->id) {
        printf("Here left: game id = %d\n", game_root->game->id);
        return search_NodeGame_byId(game_root->left, id);
    } else {
        return game_root;
    }
}


NodeGame* minValueNode(NodeGame* node)
{
    NodeGame* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->left != NULL)
        current = current->left;
 
    return current;
}


NodeGame* close_NodeGame_byId(NodeGame* game_root, int key) {
    // base case
    if (game_root == NULL)
        return game_root;
 
    // If the key to be deleted is
    // smaller than the game_root's
    // key, then it lies in left subtree
    if (key < game_root->game->id)
        game_root->left = close_NodeGame_byId(game_root->left, key);
 
    // If the key to be deleted is
    // greater than the game_root's
    // key, then it lies in right subtree
    else if (key > game_root->game->id)
        game_root->right = close_NodeGame_byId(game_root->right, key);
 
    // if key is same as game_root's key, then This is the node
    // to be deleted
    else {
        // node has no child
        if (game_root->left==NULL && game_root->right==NULL)
            return NULL;
       
        // node with only one child or no child
        else if (game_root->left == NULL) {
            NodeGame* temp = game_root->right;
            free(game_root);
            return temp;
        }
        else if (game_root->right == NULL) {
            NodeGame* temp = game_root->left;
            free(game_root);
            return temp;
        }
 
        // node with two children: Get the inorder successor
        // (smallest in the right subtree)
        NodeGame* temp = minValueNode(game_root->right);
 
        // Copy the inorder successor's content to this node
        game_root->game->id = temp->game->id;
 
        // Delete the inorder successor
        game_root->right = close_NodeGame_byId(game_root->right, temp->game->id);
    }
    return game_root;
}