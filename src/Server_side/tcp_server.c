#include "server_helper.h"


NodeUser *root = NULL;			// Record all users
NodeGame *game_root = NULL;		// Record current games


int main(){
	// Load User tree
	INFORLOG("Loading user tree");
	root = loadUserTree(root);
	INFORLOG("Loaded user tree");

	int listen_sock;
	int client_listener_sock;
	int client_speaker_sock; /* file descriptors */
	struct sockaddr_in server; /* server's address information */
	struct sockaddr_in client; /* client's address information */
	// pid_t pid;
	int sin_size;

	if ((listen_sock=socket(AF_INET, SOCK_STREAM, 0)) == -1 ){  /* calls socket() */
		printf("socket() error\n");
		return 0;
	}

	int option = 1;
	setsockopt(listen_sock, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
	
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

	int max_threads = 10;
	int no_threads=0;
    pthread_t threads[max_threads];
    while (no_threads < max_threads) {
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

		puts("Connection accepted");

		struct args *argus = (struct args *)malloc(sizeof(struct args));
		argus->client_listener_sock = client_listener_sock;
		argus->client_speaker_sock = client_speaker_sock;

		if( pthread_create( &threads[no_threads], NULL ,  &serve , (void*)argus) < 0){
			perror("Could not create thread");
			return 1;
		}

		puts("Handler assigned");
		no_threads++;
	}

	int k=0;
    for (k = 0; k < max_threads; k++){
		pthread_join(threads[k],NULL);
	}


	close(listen_sock);
	dumpUserTree(root);
	freeUserTree(root);
	
	return 0;
}
