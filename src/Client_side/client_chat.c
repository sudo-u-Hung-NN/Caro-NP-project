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


void *client_chat_sock_handler(void *client_game_socket) {
	int client_game_sock = *(int*) client_game_socket;

	for(int i = 0; i < NUM_CHATSTORE; i++) {
		bzero(ChatScreen[i], 150);
	}

	char buff[BUFF_SIZE];
	char rendered_content[150];

	bzero(rendered_content, 150);
	bzero(buff, BUFF_SIZE);
	
    while (recv(client_game_sock, buff, BUFF_SIZE, 0) > 0) {
		sprintf(rendered_content, "\033[1;34mFROM\033[0m %s", translate(buff));

		printf("%s\n", rendered_content);
		store_chat(rendered_content);

		bzero(buff, BUFF_SIZE);
		bzero(rendered_content, 150);
    }
	return 0;
}

