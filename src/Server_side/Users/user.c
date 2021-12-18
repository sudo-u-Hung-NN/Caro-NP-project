#include "user.h"

int compare(User *a, User* b) {
    return strcmp(a->account, b->account);
}

User* create_User(int id, char* name, char* account, char* password) {
    User *tmp = (User*) malloc(sizeof(User));
    tmp->id = id;
    strcpy(tmp->name, name);
    strcpy(tmp->account, account);
    strcpy(tmp->password, password);
    tmp->conn_sock = -1;
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
        if (compare(user, root->user) > 0) {
            root->right = insert_NodeUser(root->right, user, is_stored_in_database);
        } else if (compare(user, root->user) < 0) {
            root->left = insert_NodeUser(root->left, user, is_stored_in_database);
        } else {
            root->is_active = 1;
        }
    }

    return root;
}

NodeUser *search_NodeUser(NodeUser *root, User *user) {
    if (root == NULL) {
        return NULL;
    }
    if (compare(user, root->user) > 0) {
        return search_NodeUser(root->right, user);
    } else if (compare(user, root->user) < 0) {
        return search_NodeUser(root->left, user);
    } else {
        return root;
    }
}

NodeUser *search_NodeUser_withAccount(NodeUser *root, char *account) {
    if (root == NULL) {
        return NULL;
    }
    if (strcmp(account, root->user->account) > 0) {
        return search_NodeUser_withAccount(root->right, account);
    } else if (strcmp(account, root->user->account) < 0) {
        return search_NodeUser_withAccount(root->left, account);
    } else {
        return root;
    }
}

void inOrderTraversal(NodeUser *root, int *count, int verbose) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left, count, verbose);
    if (count != NULL) {
        (*count) = (*count) + 1;
    }
    if (verbose) {
        printf("TRAVERSE: id<%d> user<%s> account<%s> passwd<%s>\n", root->user->id, root->user->name, root->user->account, root->user->password);
    }
    inOrderTraversal(root->right, count, verbose);
}

void delete_NodeUser(NodeUser *root, User *user) {
    if(root == NULL) {
        return;
    } else if (compare(user, root->user) == 0) {
        root->is_active = 0;
    } else if (compare(user, root->user) > 0) {
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