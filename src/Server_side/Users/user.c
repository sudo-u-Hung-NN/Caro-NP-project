#include "user.h"

User* create_User(int id, char* name, char* account, char* password) {
    User *tmp = (User*) malloc(sizeof(User));
    tmp->id = id;
    strcpy(tmp->name, name);
    strcpy(tmp->account, account);
    strcpy(tmp->password, password);

    return tmp;
}

NodeUser *create_NodeUser(User* user, int is_stored_in_database) {
    NodeUser *tmp = (NodeUser*) malloc(sizeof(NodeUser));

    tmp->is_active = 0;
    tmp->is_stored_in_database = is_stored_in_database;

    tmp->user = user;
    tmp->left = NULL;
    tmp->right = NULL;

    return tmp;
}

NodeUser *insert_NodeUser(NodeUser *root, User *user, int is_stored_in_database) {
    if (root == NULL) {
        root = create_NodeUser(user, is_stored_in_database);
    } else {
        if (user->id > root->user->id) {
            root->right = insert_NodeUser(root->right, user, is_stored_in_database);
        } else if (user->id < root->user->id) {
            root->left = insert_NodeUser(root->left, user, is_stored_in_database);
        } else {
            root->is_active = 1;
        }
    }

    return root;
}

void inOrderTraversal(NodeUser *root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    printf("TRAVERSE: id<%d> user<%s> account<%s> passwd<%s>\n", root->user->id, root->user->name, root->user->account, root->user->password);
    inOrderTraversal(root->right);
}

void delete_NodeUser(NodeUser *root, User *user) {
    if(root == NULL) {
        return;
    } else if (root->user->id == user->id) {
        root->is_active = 0;
    } else if (root->user->id > user->id) {
        delete_NodeUser(root->right, user);
    } else {
        delete_NodeUser(root->left, user);
    }
}

void freeUserTree(NodeUser *root) {
    if (root == NULL) {
        return;
    }
    freeUserTree(root->left);
    freeUserTree(root->right);
    free(root->user);
    free(root);
}