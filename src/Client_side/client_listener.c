#include "client_helper.h"

extern sts_type curr_status;

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


void loadGameScreen(char *board) {
    printf("    0   1   2   3   4   5   6   7   8   9\n");
    printf("  -----------------------------------------\n");
    char row = 65;
    for (int i = 0; i < SIZE; i++)
    {
        printf("%c ", row++);
        for (int j = 0; j < SIZE; j++)
        {
            printf("| %c ", board[SIZE * i + j]);
        }
        printf("|\n  -----------------------------------------\n");
    }
}


void *client_listener_handler(void *client_socket) {
	int client_sock = *(int*) client_socket;

	char rendered[BUFF_SIZE];
	int msg_len = sizeof(reply);
	int bytes_received;

    reply *rep = (reply*) malloc(sizeof(reply));
    bzero(rep, msg_len);

    char screen[SIZE * SIZE];
    bzero(screen, SIZE * SIZE);

    while ((bytes_received = recv(client_sock, rep, BUFF_SIZE, 0)) > 0) {
        if (rep->command != ok && rep->command != ko && rep->command != not_identified) {
            recv_command(rep->command);
        }

        if (rep->command == chat) {
            bzero(rendered, BUFF_SIZE);
            sprintf(rendered, "\033[1;34mFROM\033[0m %s", translate(rep->instruction));
            printf("%s\n", rendered);
            store_chat(rendered);

        } else if (rep->command == scrn) {
            printf("Received scrn reply\n");
            memcpy(screen, rep->instruction, SIZE * SIZE);
            system("clear");
            loadGameScreen(screen);

        } else {
            printf("\033[0;33m%s\033[0m \033[1;34mSERVER:\033[0m %s", getStatusName(curr_status), translate(rep->instruction));
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