#include "server_helper.h"


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
        bytes_received = recv(current_user->conn_sock, msg, sizeof(message), 0); //blocking

        // displayMessage(msg, "RECV message");

        if (bytes_received < 0) {
            perror("\nError: ");
        }

        switch (msg->command) {
            case play:
                INFORLOG("Process play");
                break;
            case go:
                INFORLOG("Process squit");
                break;
            case acpt:
                INFORLOG("Process squit");
                break;
            case deny:
                INFORLOG("Process squit");
                break;
            case cancel:
                INFORLOG("Process cancel");
                break;
            case draw:
                INFORLOG("Process draw");
                break;
            case rematch:
                INFORLOG("Process rematch");
                break;
            case chat:
                INFORLOG("Process chat");
                break;
            case quit:
                INFORLOG("Process quit");
                keep_on = 0;
                break;
            case spec:
                INFORLOG("Process spec");
                break;
            case schat:
                INFORLOG("Process schat");
                break;
            case squit:
                INFORLOG("Process squit");
                break;
            case hist:
                INFORLOG("Process hist signal");
                process_hist(msg, current_user);
                break;
            case histp:
                INFORLOG("Process histp signal");
                process_histp(msg, current_user);
                break;
            case hista:
                INFORLOG("Process hista signal");
                process_hista(msg, current_user);
                break;
            case ret:
                break;
            case listp:
                INFORLOG("Process listp signal");
                process_listp(msg, current_user);
                break;
            case listg:
                INFORLOG("Process listg signal");
                process_listg(msg, current_user);
                break;
            case setname:
                INFORLOG("Process setname signal");
                process_setname(msg, current_user);
                break;
            case signup:
                INFORLOG("Process sign up signal");
                current_user = process_sign_up(msg, current_user);
                break;
            case login:
                INFORLOG("Process login signal");
                current_user = process_sign_in(msg, current_user);
                break;
            default:
                break;
        }
    }
    free(msg);
	close(sockfd);
}