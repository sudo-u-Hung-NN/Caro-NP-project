#include "server_helper.h"


NodeUser *root = NULL;			// Record all users
NodeGame *game_root = NULL;		// Record current games


int main(){
	// Load User tree
	INFORLOG("Loading user tree");
	root = loadUserTree(root);
	INFORLOG("Loaded user tree");

	int listen_sock, client_listener_sock, client_speaker_sock; /* file descriptors */
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	pid_t pid;
	int sin_size;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		return 0;
	}
	
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;         
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);  /* INADDR_ANY puts your IP address automatically */   

	if(bind(listen_sock, (struct sockaddr*)&server, sizeof(server))==-1){ 
		perror("Error");
		return 0;
	}     

	if(listen(listen_sock, BACKLOG) == -1){  
		perror("Error");
		return 0;
	}
	
	/* Establish a signal handler to catch SIGCHLD */
	signal(SIGCHLD, sig_chld);

	int dumpfile_frequency = 10;
	int count = 0;

	while(++count){
		sin_size=sizeof(struct sockaddr_in);

		// Connect sock to client_chat_sock
		if ((client_speaker_sock = accept(listen_sock, (struct sockaddr *)&client, &sin_size))==-1) {
			if (errno == EINTR)
				continue;
			else{
				perror("\nError");
				return 0;
			}
		}

		// Connect sock to client_sock
		if ((client_listener_sock = accept(listen_sock, (struct sockaddr *)&client, &sin_size))==-1){
			if (errno == EINTR)
				continue;
			else{
				perror("\nError");
				return 0;
			}
		}
		
		/* For each client, fork spawns a child, and the child handles the new client */
		pid = fork();
		
		/* fork() is called in child process */
		if(pid == 0){
			close(listen_sock);
			printf("You got a connection from %s\n", inet_ntoa(client.sin_addr)); /* prints client's IP */
			serve(client_listener_sock, client_speaker_sock);
		}

		if (count % dumpfile_frequency == 0) {
			dumpUserTree(root);
		}
		
		/* The parent closes the connected socket since the child handles the new client */
		close(client_listener_sock);
		close(client_speaker_sock);
	}
	close(listen_sock);

	dumpUserTree(root);
	return 0;
}
