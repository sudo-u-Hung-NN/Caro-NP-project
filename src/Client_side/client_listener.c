#include "client_helper.h"


int latest_chat_index = 0;
int oldest_chat_index = 0;
char ChatScreen[NUM_CHATSTORE][150];


void store_chat(char* buff) {
    strcpy(ChatScreen[latest_chat_index], buff);
	latest_chat_index ++;
	latest_chat_index = (latest_chat_index) % NUM_CHATSTORE;

	if (oldest_chat_index >= latest_chat_index) {
		oldest_chat_index ++;
		oldest_chat_index = (oldest_chat_index) % NUM_CHATSTORE;
	}
}


void display_chatscreen() {
	system("clear");
	printf("<===========< \033[1;34mCHAT SCREEN\033[0m >===========>\n");
    for (int i = oldest_chat_index; i < NUM_CHATSTORE && (strlen(ChatScreen[i]) > 1); i++) {
		printf("%s\n", ChatScreen[i]);
    }
}


void *client_listener_handler(void *client_socket) {
	int client_sock = *(int*) client_socket;

	char rendered[BUFF_SIZE];
	int msg_len = sizeof(reply);
	int bytes_received;

    reply *rep = (reply*) malloc(sizeof(reply));
    bzero(rep, msg_len);

    while ((bytes_received = recv(client_sock, rep, BUFF_SIZE, 0)) > 0) {
        if (rep->command != ok && rep->command != ko && rep->command != not_identified) {
            apply_transition(rep->command);
        }

        if (rep->command == chat) {
            bzero(rendered, BUFF_SIZE);
            sprintf(rendered, "\033[1;34mFROM\033[0m %s", translate(rep->instruction));
            store_chat(rendered);
        } else {
            printf("\033[1;34mSERVER:\033[0m %s", translate(rep->instruction));
        }

        bzero(rep, msg_len);
    }

    if (bytes_received < 0) {
        perror("\nError: ");
        exit(1);
    } else if (bytes_received == 0) {
        printf("Connection closed.\n");
    }

	return 0;
}