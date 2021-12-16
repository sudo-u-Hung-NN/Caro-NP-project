#ifndef USER_H
#define USER_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define USER_DATABASE "../Database/Users.dat"

typedef struct User {
    int id;
    char name[50];
    char account[50];
    char password[50];
} User;


typedef struct NodeUser {
    int is_active;
    int is_stored_in_database;
    User* user;
    struct NodeUser *left;
    struct NodeUser *right;
} NodeUser;


User* create_User(int id, char* name, char* account, char* password);

NodeUser *create_NodeUser(User* user, int is_stored_in_database);

NodeUser *insert_NodeUser(NodeUser *root, User *user, int is_stored_in_database);

void delete_NodeUser(NodeUser *root, User *user);

void dumpUserTree(NodeUser* root);

void inOrderTraversal(NodeUser *root);

void freeUserTree(NodeUser *root);

#endif