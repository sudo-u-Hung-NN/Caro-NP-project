#include "client_helper.h"

extern sts_type curr_status;
extern char screen[SIZE * SIZE];


void *client_speaker_handler(void *client_speaker) {
	int client_sock = *(int*) client_speaker;

	char buff[BUFF_SIZE + 1];
	char rendered[BUFF_SIZE];
	int msg_len = sizeof(message);
	int bytes_sent;

	bzero(buff, BUFF_SIZE + 1);
	
    while (1) {
		// fgets(buff, BUFF_SIZE, stdin);
		scanf("%[^\n]s", buff);
		while (getchar() != '\n');

        buff[strlen(buff)] = '\0';

		if (strcasecmp(buff, "cs") == 0) {
			display_chatscreen();
			continue;
		} else if (strcasecmp(buff, "help") == 0) {
			help();
			continue;
		} else if (strcasecmp(buff, "clear") == 0) {
			system("clear");
			continue;
		} else if(strcasecmp(buff, "scrn") == 0) {
			system("clear");
			loadGameScreen(screen);
			continue;
		}

		message *msg = create_msg(buff, curr_status);

		if (msg == NULL) {
			continue;
		} else if (msg->command == quit) {
			send(client_sock, msg, msg_len, 0);
			free(msg);
			break;
		} else {
			send_command_v2(msg->command);

			if (msg->command == chat) {
				bzero(rendered, BUFF_SIZE);
				sprintf(rendered, "\033[1;34mTO \033[1;32m%s\033[0m: %s", msg->data.target, msg->data.data);
				printf("%s\n", rendered);
				store_chat(rendered);
			}
            
			bytes_sent = send(client_sock, msg, msg_len, 0);

			if(bytes_sent < 0)
				perror("\nError: ");

		}
		bzero(buff, BUFF_SIZE);
		free(msg);
    }

	return 0;
}