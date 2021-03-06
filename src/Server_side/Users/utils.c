#include "user.h"
#include "../../Utils/error.h"
#include "../../Utils/logger.h"

/**
 * @brief This function exploit a line in database, returns information for User's creation
 * @param input [INPUT] a line text
 * @param sep [INPUT] separator character
 * @param id [OUTPUT] user's id
 * @param name [OUTPUT] user's name, must be initialized already
 * @param account [OUTPUT] user's account, must be initialized already
 * @param password [OUTPUT] user's password, must be initialized already
 */
void fromLineToData(char* input, char sep, int* id, char *name, char *account, char *password) {
    int i = 0;
    char data[50] = "";
    char cut[2] = "";

    bzero(data, sizeof(data));
    for(; input[i] != sep; i++) {
        cut[0] = input[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    *id = atoi(data);
    
    bzero(data, sizeof(data));
    for(i = i + 1; input[i] != sep; i++) {
        cut[0] = input[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    strcpy(name, data);

    bzero(data, sizeof(data));
    for(i = i + 1; input[i] != sep; i++) {
        cut[0] = input[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    strcpy(account, data);

    bzero(data, sizeof(data));
    for(i = i + 1; input[i] != '\0' && input[i] != '\n' && i < strlen(input); i++) {
        cut[0] = input[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    strcpy(password, data);
}

/**
 * @brief This function load user database file into a binary tree.
 * The database file path is defined in Users/user.h
 * @param root 
 * @return root
 */
NodeUser* loadUserTree(NodeUser* root) {
    INFORLOG(USER_DATABASE);
    FILE *fptr = fopen(USER_DATABASE, "r");
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    char sep = ',';
    int id = 0;
    char name[50]="\0";
    char account[50]="\0";
    char password[50]="\0";

    if (fptr == NULL) {
        error(ERROR_USER_DATABASE_NOTFOUND);
    } else {
        INFORLOG("Loading user's database...");
        while ((read = getline(&line, &len, fptr)) != -1) {
            strcpy(name, "\0");
            strcpy(account, "\0");
            strcpy(password, "\0");

            fromLineToData(line, sep, &id, name, account, password);
            // printf("IO: id<%d> user<%s> account<%s> passwd<%s>\n", id, name, account, password);

            User *user = create_User(id, name, account, password);
            root = insert_NodeUser(root, user, 1);
        }
        fclose(fptr);
        if (line) {
            free(line);
        }
    }

    return root;
};


void treeToFile(NodeUser* root, FILE* fptr) {
    if (root == NULL) {
        return;
    }
    treeToFile(root->left, fptr);
    fprintf(fptr, "%d,%s,%s,%s\n", root->user->id, root->user->name, root->user->account, root->user->password);
    treeToFile(root->right, fptr);
};


void dumpUserTree(NodeUser* root) {
    FILE *fptr = fopen(USER_DATABASE, "w");
    INFORLOG("Writing database...");
    treeToFile(root, fptr);
    INFORLOG("Finished writing database");
    fclose(fptr);
};


int test_fromLineToData() {
    int id = 0;
    char name[50]="\0";
    char account[50]="\0";
    char password[50]="\0";
    char input[152] = "15 HungNguyen sudo-u-Hung-NN hung2000";
    fromLineToData(input, ',', &id, name, account, password);
    printf("Output: <%d> <%s> <%s> <%s>\n", id, name, account, password);
    return 0;
};


int test_loadUserTree() {
    NodeUser *s = NULL;
    int count = 0;
    loadUserTree(s);
    inOrderTraversal(s, &count, 1);
    freeUserTree(s);
    return 0;
}

