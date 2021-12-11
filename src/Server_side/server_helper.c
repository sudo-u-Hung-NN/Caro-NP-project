#include "server_helper.h"
#include "../Utils/message.h"


char *uppercase(char* input) {
    char* output = (char*) malloc(strlen(input) * sizeof(char));
    for (int i = 0; i < strlen(input); i++) {
        output[i] = toupper(input[i]);
    }
    return output;
}

int process_sign_up(message *msg) {
    printf("target: %s\ncontent: %s\n", msg->data.target, msg->data.data);
    return 1;
}

void client_sign_up(int conn_sock) {
    send(conn_sock, "REQUEST_ID", 50, 0);
    
    message *msg = (message *) malloc(sizeof(message));
    recv(conn_sock, msg, 1024, 0);
    int success = process_sign_up(msg);
    if (success) {
        send(conn_sock, "ACC_TRUE", 50, 0);
    } else {
        send(conn_sock, "ACC_FALSE", 50, 0);
    }
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