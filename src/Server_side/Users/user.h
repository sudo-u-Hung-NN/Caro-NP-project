#ifndef USER_H
#define USER_H

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define USER_DATABASE "src/Server_side/Database/Users.csv"

typedef struct User {
    int id;
    char name[50];
    char account[50];
    char password[50];
    int conn_sock;
    int chat_sock;
} User;


typedef struct NodeUser {
    int is_active;
    int is_stored_in_database;
    User* user;
    struct NodeUser *left;
    struct NodeUser *right;
} NodeUser;

/* Only interface function are shown */

/**
 * @brief Create a User object, use when a new User sign up
 * @param id 
 * @param name 
 * @param account 
 * @param password 
 * @return User* 
 */
User* create_User(int id, char* name, char* account, char* password);


/**
 * @brief When a User sign up, the User object inserted in User's binary tree.
 * Use this function when a User sign in
 * @param root 
 * @param user 
 * @param is_stored_in_database this value is 1 when the function is called to load database, 0 when new User sign up
 * @return NodeUser* 
 */
NodeUser *insert_NodeUser(NodeUser *root, User *user, int is_stored_in_database);


/**
 * @brief This function traverse and return the total node in the tree
 * @param root [INPUT] the tree root
 * @param count [OUTPUT] the total number of nodes
 * @param verbose [INPUT] if 1 then printing the tree
 */
void inOrderTraversal(NodeUser *root, int *count, int verbose);
void freeUserTree(NodeUser *root);


/**
 * @brief This function look up a User in the Binary tree
 * @param root 
 * @param user 
 * @return NodeUser* 
 */
NodeUser *search_NodeUser(NodeUser *root, User *user);


/**
 * @brief This function look up an account in the Binary tree
 * @param root 
 * @param account 
 * @return NodeUser* 
 */
NodeUser *search_NodeUser_withAccount(NodeUser *root, char *account);


/**
 * @brief This function load user database file into a binary tree.
 * This function is called first when running server.
 * The database file path is defined in Users/user.h
 * @param root 
 * @return root
 */
NodeUser* loadUserTree(NodeUser* root);


/**
 * @brief This function is called when the server is shutdown, to write the binary tree to database file
 * @param root 
 */
void dumpUserTree(NodeUser* root);


/**
 * @brief This function deactivate of the UserNode in the tree.
 * Use this function when a User disconnect to server
 * @param root 
 * @param user 
 */
void delete_NodeUser(NodeUser *root, User *user);

#endif