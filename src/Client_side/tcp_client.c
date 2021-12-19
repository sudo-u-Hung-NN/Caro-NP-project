#include "client_helper.h"

sts_type prev_status = console;
sts_type curr_status = console;
msg_type recv_command = not_identified;

int main()
{
	int client_sock, client_chat_sock;
	struct sockaddr_in server_addr; /* server's address information */

	//Step 1: Construct socket
	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	client_chat_sock = socket(AF_INET, SOCK_STREAM, 0);

	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);

	//Step 3: Request to connect server
	if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("Error! Can not connect client to sever! Client exit imediately!\n");
		return 0;
	}

	if (connect(client_chat_sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) < 0)
	{
		printf("Error! Can not connect client game socket to sever! Client exit imediately!\n");
		return 0;
	}

	//Step 4: Communicate with server
	pthread_t threads[2];

	// Step 4.1: Threading client_sock
	if (pthread_create(&threads[0], NULL, client_sock_handler, &client_sock) < 0) {
		perror("Could not create thread for client_sock_handler");
		return 1;
	} else if (client_sock < 0) {
		printf("server doesn't accept client_sock...\n");
		exit(0);
	} else {
		printf("Server accepts the client_sock...\n");
	}

	// Step 4.2: Threading client_sock
	if (pthread_create(&threads[1], NULL, client_chat_sock_handler, &client_chat_sock) < 0) {
		perror("Could not create thread for client_chat_sock_handler");
		return 1;
	} else if (client_chat_sock < 0) {
		printf("server doesn't accept client_chat_sock...\n");
		exit(0);
	} else {
		printf("Server accepts the client_chat_sock...\n");
	}
	
	// Step 4.3: Joining threads
	pthread_join(threads[0], NULL);
	pthread_join(threads[1], NULL);

	//Step 5: Close socket
	close(client_sock);
	close(client_chat_sock);
	return 0;
}
