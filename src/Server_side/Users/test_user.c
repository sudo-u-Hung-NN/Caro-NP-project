#include "./user.h"


int main(int argc, char const *argv[])
{
    NodeUser *s = NULL;
    s = loadUserTree(s);
    int count = 0;
    User *new_user = create_User(5, "hung", "hung20184118", "hung2000");
    s = insert_NodeUser(s, new_user, 0);
    NodeUser *found = search_NodeUser_withAccount(s, "hung20184118");
    int valid = (found != NULL);
    printf("%d\n", valid);
    inOrderTraversal(s, &count, 1);
    dumpUserTree(s);
    freeUserTree(s);
    return 0;
}
