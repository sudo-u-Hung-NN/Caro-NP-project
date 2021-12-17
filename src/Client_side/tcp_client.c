#include "client_helper.h"

sts_type prev_status = console;
sts_type curr_status = console;
msg_type recv_command = not_identified;

int main(){
	int client_sock;
	char buff[BUFF_SIZE + 1];
	struct sockaddr_in server_addr; /* server's address information */
	int msg_len = sizeof(message);
	int bytes_sent, bytes_received;
	
	//Step 1: Construct socket
	client_sock = socket(AF_INET,SOCK_STREAM,0);
	
	//Step 2: Specify server address
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	
	//Step 3: Request to connect server
	if(connect(client_sock, (struct sockaddr*)&server_addr, sizeof(struct sockaddr)) < 0){
		printf("Error! Can not connect to sever! Client exit imediately!\n");
		return 0;
	}
		
	//Step 4: Communicate with server			
	memset(buff,'\0',(strlen(buff)+1));
	bytes_received = recv(client_sock, buff, BUFF_SIZE, 0); // Receive REQUEST_ID
	printf("Receive: %s\n", buff);
	
    while (fgets(buff, BUFF_SIZE, stdin) != NULL) {
        buff[strlen(buff) - 1] = '\0';

		message *msg = create_msg(buff, curr_status);
		if (msg->command == quit) {
			break;
		}
		apply_transaction(msg->command);
            
        bytes_sent = send(client_sock, msg, msg_len, 0);

        if(bytes_sent < 0)
            perror("\nError: ");
        
        //receive echo reply
        bytes_received = recv(client_sock, buff, BUFF_SIZE, 0);
        if (bytes_received < 0) {
                perror("\nError: ");
                exit(1);
        }
        else if (bytes_received == 0) {
                printf("Connection closed.\n");
                break;
        }
		
        buff[bytes_received] = '\0';
        printf("Reply from server: %s\n", buff);
    }
	
	//Step 4: Close socket
	close(client_sock);
	return 0;
}
