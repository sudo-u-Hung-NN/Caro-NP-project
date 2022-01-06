#include "../server_helper.h"

extern thread_local Player *myself;
extern thread_local Player *rival;


char* fromLineToDataRematch(char *line, char sep) {
    if (line == NULL) {
        return NULL;
    }

    int i = 0;
    char data[50] = "";
    char cut[2] = "";

    int game_id = 0;

    bzero(data, sizeof(data));
    for(; line[i] != sep; i++) {
        cut[0] = line[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    game_id = atoi(data);
    char *opponent = (char*) malloc (100 * sizeof(char));
    bzero(opponent, 100);
    bzero(data, sizeof(data));
    for(i=i+1; line[i] != sep; i++) {
        cut[0] = line[i];
        cut[1] = '\0';
        strcat(data, cut);
    }
    strcpy(opponent, data);
    return opponent;
}


void process_rematch(message *msg, User* current_user) {
    char filename[100] = "";
    sprintf(filename, "%s/%s.hist", HISTORY_PATH, current_user->account);
    INFORLOG(filename);
    FILE* fptr = fopen(filename, "r");
    if(fptr == NULL) {
        WARNING("Invalid ramatch!");
        send(current_user->listener, create_reply(done, "INVALID_REMATCH"), sizeof(reply), 0);
        return;
    }
    
    char *line = NULL;
    char *opponent = NULL;
    char sep = ',';

    size_t len = 0;
    ssize_t read;

    do {
        read = getline(&line, &len, fptr);
        if (opponent != NULL) {
            free(opponent);
        }
        opponent = fromLineToDataRematch(line, sep);

        if(opponent == NULL) {
            return;
        } else {
            INFORLOG(opponent);
        }
    } while (read < 2);
    fclose(fptr);
    
    INFORLOG("Redirecting message command, data...");
    msg->command = play;
    
    if(opponent == NULL) {
        WARNING("Null opponent!");
        return;
    } else {
        INFORLOG(opponent);
    }
    strcpy(msg->data.data, opponent);

    INFORLOG("Triggering process_play procedure...");
    process_play(msg, current_user);
    INFORLOG("Rematch request processing done");
}