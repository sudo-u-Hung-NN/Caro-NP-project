#include "server_helper.h"

extern NodeUser *root;


char *uppercase(char* input) {
    char* output = (char*) malloc(strlen(input) * sizeof(char));
    for (int i = 0; i < strlen(input); i++) {
        output[i] = toupper(input[i]);
    }
    return output;
}


void sig_chld(int signo){
	pid_t pid;
	int stat;
	
	/* Wait the child process terminate */
	while((pid = waitpid(-1, &stat, WNOHANG))>0)
		printf("\nChild %d terminated\n",pid);
}


void serve(int sockfd) {
	message *msg = (message *) malloc(sizeof(message));
    User *current_user = NULL;
    int bytes_received;
	
    int keep_on = 1;
    while(keep_on) {
        
        if (current_user == NULL) {
            send(sockfd, "REQUEST_ID", 50, 0);
        }

        bzero(msg, sizeof(message));
        bytes_received = recv(sockfd, msg, sizeof(message), 0); //blocking

        displayMessage(msg, "RECV message");

        if (bytes_received < 0) {
            perror("\nError: ");
        }

        switch (msg->command)
        {
        case play:
        case go:
        case acpt:
        case deny:
        case cancel:
        case draw:
        case rematch:
        case chat:
        case quit:
            keep_on = 0;
            break;
        case spec:
        case schat:
        case squit:
        case hist:
        case histp:
        case hista:
        case ret:
        case listp:
        case listg:
        case setname:
        case signup:
            INFORLOG("Process sign up signal");
            current_user = process_sign_up(sockfd, msg);
            break;
        case login:
            current_user = process_sign_in(sockfd, msg);
            break;
        case not_identified:
            break;
        default:
            break;
        }
    }
    free(msg);
	close(sockfd);
}