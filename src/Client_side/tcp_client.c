#include "client_helper.h"

sts_type curr_status = console;
msg_type sendCommand = not_identified;
msg_type recvCommand = not_identified;

int main()
{
	int client_listener_sock, client_speaker_sock;
	struct sockaddr_in server_addr; /* server's address information */

	//Step 1: Construct socket
	client_listener_sock = socket(AF_INET, SOCK_STREAM, 0);
	client_speaker_sock = socket(AF_INET, SOCK_STREAM, 0);

	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	//Step 3: Request to connect server
	if (connect(client_speaker_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0) {
		printf("Error! Can not connect client speaker to sever! Client exit imediately!\n");
		return 0;
	}

	if (connect(client_listener_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0) {
		printf("Error! Can not connect client listener to sever! Client exit imediately!\n");
		return 0;
	}

	//Step 4: Communicate with server
	pthread_t threads[2];

	// Step 4.1: Threading client_listener_sock
	if (pthread_create(&threads[1], NULL, client_speaker_handler, &client_speaker_sock) < 0) {
		perror("Could not create thread for client_speaker_sock_handler");
		return 1;
	} else if (client_speaker_sock < 0) {
		printf("server doesn't accept client_speaker_sock...\n");
		exit(0);
	} else {
		printf("Server accepts the client_speaker_sock...\n");
	}

	if (pthread_create(&threads[0], NULL, client_listener_handler, &client_listener_sock) < 0) {
		perror("Could not create thread for client_listener_sock_handler");
		return 1;
	} else if (client_listener_sock < 0) {
		printf("server doesn't accept client_listener_sock...\n");
		exit(0);
	} else {
		printf("Server accepts the client_listener_sock...\n");
	}
	
	// Step 4.3: Joining threads
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	//Step 5: Close socket
	close(client_listener_sock);
	close(client_speaker_sock);
	return 0;
}
