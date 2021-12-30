#include "client_helper.h"


extern sts_type curr_status;
extern msg_type sendCommand;
extern msg_type recvCommand;


struct {
	sts_type status;
	char name[10];
} status_table [4] = {
	{playing, "playing"},
	{spectating, "spectate"},
	{console, "console"},
	{waiting, "waiting"}
};


char *getStatusName(sts_type status) {
	return status_table[status].name;
}


struct {
	sts_type prev_status;
	msg_type recv_command;
	msg_type send_command;
	sts_type next_status;

} transitions [NUM_TRANSITION] = {
	{console,		not_identified,	 	play,			waiting},
	{console,		not_identified,	 	rematch,		waiting},
	{console,		play,				acpt,			playing},
	{console,		play,				deny,			console},
	{console,		rematch,			acpt,			playing},
	{console,		rematch,			deny,			console},
	{console,		not_identified,	 	spec,			spectating},

	{waiting,		acpt,			  	play, 			playing},
	{waiting,		deny,				play, 			console},
	{waiting,		play,	 			cancel,			console},

	{playing,		draw,				acpt,			console},
	{playing,		draw,				deny,			playing},
	{playing,		play,			 	draw,			playing},
	{playing, 		done, 				not_identified,	console},

	{spectating,	spec,				squit,			console},
	{spectating,	play,				acpt,			playing},
	{spectating,	play,				deny,			spectating},
	{spectating,	rematch,			acpt,			playing},
	{spectating,	rematch,			deny,			spectating},
	{spectating, 	done,				not_identified,	console}
};


void apply_transition() {
    for (int i = 0; i < NUM_TRANSITION; i++) {
        if (transitions[i].prev_status == curr_status && 
            transitions[i].recv_command == recvCommand &&
            transitions[i].send_command == sendCommand) {
            curr_status = transitions[i].next_status;
        }
    }
}


void send_command(msg_type command) {
	if (command == play ||
		command == rematch ||
		command == acpt ||
		command == deny ||
		command == cancel ||
		command == squit ||
		command == draw ||
		command == spec) {
			sendCommand = command;
			apply_transition();
		}
}


void recv_command(msg_type command) {
	if (command == play ||
		command == rematch ||
		command == acpt ||
		command == deny ||
		command == draw ||
		command == done) {
			recvCommand = command;
			if (command == done) {
				curr_status = console;
				sendCommand = not_identified;
				recvCommand = not_identified;
			} else 
				apply_transition();
		}
}

struct {
	char server_reply[50];
	char instruction[150];
} Translator[NUM_TRANSLATE] = {
	{"REQUEST_ID", "Please login (\033[0;33mLOGIN <account>\033[0m) or sign up (\033[0;33mSIGNUP <account>\033[0m):\n"},
	{"CACC_TRUE", "Valid account! Enter your password (\033[0;33mSIGNPWD <password>\033[0m):\n"},
	{"CACC_FALSE", "\033[0;35mAccount existed!\033[0m Please login (\033[0;33mLOGIN <account>\033[0m) or sign up (\033[0;33mSIGNUP <account>\033[0m):\n"},
	{"ACC_FALSE", "\033[0;35mYour account doesn't exist!\033[0m Please login (\033[0;33mLOGIN <account>\033[0m) or sign up (\033[0;33mSIGNUP <account>\033[0m):\n"},
	{"ACC_TRUE", "Valid account! Enter your password (\033[0;33mLOGPWD <password>\033[0m):\n"},
	{"PWD_TRUE", "\033[0;34mAccess granted!\033[0m Login done. Use \033[1;34mhelp\033[0m to explore for more!\n"},
	{"PWD_FALSE", "\033[0;35mWrong password!\033[0m Please login (\033[0;33mLOGIN <account>\033[0m) or sign up (\033[0;33mSIGNUP <account>\033[0m):\n"},
	{"SETNAME_SUCESS", "\033[0;34mSetname successful\033[0m\n"},
	{"DUPLICATED", "\033[0;35mYour account is already online!\033[0m\n"}, 
	{"NULL_RANKING", "\033[0;35mRanking file not found!\033[0m\n"},
	{"NULL_HISTORY", "\033[0;35mHistory not found or not established yet!\033[0m\n"},
	{"NULL_ACCOUNT", "\033[0;35mYou are looking for a ghoust account!\033[0m\n"},
	{"OFFLINE_ACCOUNT", "\033[0;35mYou are looking for an offline account!\033[0m\n"},
	{"MESSAGE_SENT", "\033[0;34mMessage sent successfully\033[0m\n"},
	{"MESSAGE_FAILED", "\033[0;35mFailed to send message!\033[0m\n"},
	{"BLANK_RANKING", "\033[0;35mBlank ranking file!\033[0m\n"},
	{"ON_DEVELOP", "\033[0;35mThis functionality is on develop!\033[0m\n"},
	{"LOOP_OPERATOR", "\033[0;35mYou are trying to execute operators on yourself!\033[0m\n"},
	
	// Gamming
	{"CHALLENGE_SENT", "\033[1;34mChallenge sent!\033[0m\n"},
	{"ACCEPTED", "\033[1;34mYour challenge request is accepted!\033[0m\n"},
	{"DENIED", "\033[1;35mYour challenge request is denied!\033[0m\n"},
	{"GAME_CREATED_X", "\033[1;34mThe game is successfully created! You play X\033[0m\n"},
	{"GAME_CREATED_O", "\033[1;34mThe game is successfully created! You play O\033[0m\n"},
	{"GAME_FAILED", "\033[1;35mFailed to create new game! Try again latter!\033[0m\n"},
	{"YOUR_TURN", "\033[1;34mYour turn!\033[0m (format: \033[0;33mGO <row><col>\033[0m, e.g. GO A3)\n"},
	{"OPPONENT_TURN", "\033[1;35mIt's your opponent's turn!\033[0m\n"},
	{"WIN", "\033[1;34mYou won!\033[0m\n"},
	{"LOSE", "\033[1;35mYou went second place!\033[0m\n"},
	{"SCREEN", "\033[1;34m<============= GAME SCREEN ==============>!\033[0m\n"},
	{"INVALID_MOVE", "\033[1;35mYou have made an invalid move!\033[0m\n"},
	{"FALSE_FORMAT", "\033[1;35mYour move is of wrong format!\033[0m\n"},
	{"DRAW_REQUEST", "\033[1;34mYou have received a draw request!\033[0m\n"},
	{"DRAW_REQUEST_SENT", "\033[1;34mSent request successfully!\033[0m\n"},
	{"DRAW",  "\033[1;34mThe game ends tie for both!\033[0m\n"},
	{"TIE", "\033[1;34mThe game ends tie for both!\033[0m\n"},

	// Cancel
	{"CANCELED", "\033[1;35mThe invitation is canceled by the challenger!\033[0m\n"},
	{"NULL_CANCEL", "\033[1;35mThe game is not found!\033[0m\n"},
	{"INVALID_CANCEL", "\033[1;35mYou're attempting to over-authoritize!\033[0m\n"}
};


char *translate(char *server_reply) {
	for (int i = 0; i < NUM_TRANSLATE; i++) {
		if (strcmp(server_reply, Translator[i].server_reply) == 0) {
			return Translator[i].instruction;
		}
	}

	return server_reply;
}
