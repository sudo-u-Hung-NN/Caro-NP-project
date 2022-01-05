#include "../server_helper.h"


/**
 * @brief This function read a line and get game record information
 * @param input [INPUT] a string
 * @param sep [INPUT] separator
 * @param game_id [OUTPUT] game_id
 * @param opponent_account [OUTPUT] the account of the opponent
 * @param win [OUTPUT] the result, 1 if win, 0 if lose
 */
void fromLineToHist(char* input, char sep, int* game_id, char *opponent_account, int *win) {
    int i = 0;
    char data[50] = "";
    char cut[2] = "";

    bzero(data, sizeof(data));
    for(; input[i] != sep; i++) {
        cut[0] = input[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    *game_id = atoi(data);
    
    bzero(data, sizeof(data));
    for(i = i + 1; input[i] != sep; i++) {
        cut[0] = input[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    strcpy(opponent_account, data);

    bzero(data, sizeof(data));
    for(i = i + 1; input[i] != '\n' && input[i] != EOF; i++) {
        cut[0] = input[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    *win = atoi(data);
}


/**
 * @brief This function read history file and return formated string
 * @param account The user to be checked
 * @return char* 
 */
char* read_hist_file(char *account) {
    char *history = (char*) malloc(rep_instruct_len * sizeof(char));
    bzero(history, rep_instruct_len);
    history[0] = '\n';

    char filename[50];
    bzero(filename, 50);

    sprintf(filename, "%s/%s.hist", HISTORY_PATH, account);
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL) {
        WARNING("Profile not found!");
        return NULL;
    } else {
        char line[100] = "";
        int game_id = 0;
        int win = 0;
        char opponent_account[50] = "\0";

        char rendered_line[150];

        while ((fgets(line, 100, fptr) != NULL) && strlen(history) < rep_instruct_len - 1) {
            fromLineToHist(line, ',', &game_id, opponent_account, &win);

            bzero(line, 100);
            bzero(rendered_line, 150);
            
            if (win) {
                sprintf(rendered_line, "%s played with %s :-: game id<%d> :-: \033[1;34mwin\033[0m\n", account, opponent_account, game_id);
            } else {
                sprintf(rendered_line, "%s played with %s :-: game id<%d> :-: \033[0;31mlose\033[0m\n", account, opponent_account, game_id);
            }
            strcat(history, rendered_line);
        }

        fclose(fptr);
        return history;
    }
}


/** History
 * @brief This function shows the current user his own history.
 * This function is defined in "src/Server_side/Functions/hist.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_hist(message *msg, User* current_user) {
    char self_infor[rep_instruct_len];
    bzero(self_infor, rep_instruct_len);
    sprintf(self_infor, "\nName: %s\nAccount: %s\nId: %d\nListener socket: %d\nSpeaker socket: %d\n",
                current_user->name, current_user->account, current_user->id, current_user->listener, current_user->speaker);
    
    send(current_user->listener, create_reply(ok, self_infor), sizeof(reply), 0);

    char *history = read_hist_file(current_user->account);

    if(history == NULL) {
        send(current_user->listener, create_reply(ko, "NULL_HISTORY"), sizeof(reply), 0);
    } else {
        send(current_user->listener, create_reply(ok, history), sizeof(reply), 0);
        free(history);
    }
}


/**
 * @brief This function shows the current user a nother player's history.
 * This function is defined in "src/Server_side/Functions/hist.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_histp(message *msg, User* current_user) {
    char *account = getData(msg);
    char *history = read_hist_file(account);

    char self_infor[rep_instruct_len];
    bzero(self_infor, rep_instruct_len);

    NodeUser *nodeuser = search_NodeUser_withAccount(root, account);
    if (nodeuser != NULL) {
        User* target = search_NodeUser_withAccount(root, account)->user;
        sprintf(self_infor, "\nName: %s\nAccount: %s\nId: %d\nListener socket: %d\nSpeaker socket: %d\n",
                    target->name, target->account, target->id, target->listener, target->speaker);

        send(current_user->listener, create_reply(ok, self_infor), sizeof(reply), 0);
    }

    if(history == NULL) {
        send(current_user->listener, create_reply(ko, "NULL_HISTORY"), sizeof(reply), 0);
    } else {
        send(current_user->listener, create_reply(ok, history), sizeof(reply), 0);
        free(history);
    }
}


/**
 * @brief This function shows the rankings.
 * This function is defined is "src/Server_side/Functions/hist.c"
 * @param msg the requested message from client
 * @param current_user the current user
 */
void process_hista(message *msg, User* current_user) {
    char *ranking = (char*) malloc(rep_instruct_len * sizeof(char));
    bzero(ranking, rep_instruct_len);

    char filename[50];
    bzero(filename, 50);

    sprintf(filename, "%s/all.ranking", ACCOUNT_PATH);
    FILE *fptr = fopen(filename, "r");

    size_t rep_len = sizeof(reply);

    int rank = 0;
    if (fptr == NULL) {
        WARNING("Ranking file not found!");
        send(current_user->listener, create_reply(ko, "NULL_RANKING"), rep_len, 0);

    } else {
        char line[50] = "";
        fgets(line, 50, fptr);

        while ((fgets(line, 50, fptr) != NULL) && (strlen(ranking) < rep_instruct_len - 1) && (rank < 15)) {
            strcat(ranking, line);
            bzero(line, 50);
        }
        
        if (strlen(ranking) > 1) {
            send(current_user->listener, create_reply(ok, ranking), rep_len, 0);
        } else {
            send(current_user->listener, create_reply(ko, "BLANK_RANKING"), rep_len, 0);
        }
        
    }

    free(ranking);
}