#include "server_helper.h"

NodeUser *root = NULL;

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

void echo(int sockfd) {
	char buff[BUFF_SIZE];
	int bytes_sent, bytes_received;
	
    int keep_on = 1;
    while(keep_on) {
        bytes_received = recv(sockfd, buff, BUFF_SIZE, 0); //blocking
        printf("Received <%s>\n", buff);
        if (bytes_received < 0)
            perror("\nError: ");
        else if (bytes_received == 0)
            printf("Connection closed.");

        char *echo_string = uppercase(buff);

        if (strcasecmp(echo_string, "q") == 0) {
            printf("Terminate signal detected, close connection\n");
            keep_on = 0;
        } else {
            bytes_sent = send(sockfd, echo_string, bytes_received, 0); /* echo to the client */
            if (bytes_sent < 0)
                perror("\nError: ");
        }
        free(echo_string);
    }
	close(sockfd);
}

void serve(int sockfd) {
	message *msg = (message *) malloc(sizeof(message));
	int bytes_sent, bytes_received;
    User *current_user = NULL;
	
    int keep_on = 1;
    while(keep_on) {
        
        if (current_user == NULL) {
            current_user = process_sign_up(sockfd);
        }

        bzero(msg, sizeof(msg));
        bytes_received = recv(sockfd, msg, sizeof(msg), 0); //blocking

        printf("Received message\n");

        if (bytes_received < 0)
            perror("\nError: ");
        else if (bytes_received == 0) {
            printf("Connection closed.");
            keep_on = 0;
            break;
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
        case signin:
        case signpwd:
        case login:
        case logpwd:
        case not_identified:
            break;
        default:
            break;
        }
    }
	close(sockfd);
}