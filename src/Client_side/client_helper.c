#include "client_helper.h"

extern sts_type prev_status;
extern sts_type curr_status;
extern msg_type recv_command;

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

	{waiting,		acpt,			  	not_identified, playing},
	{waiting,		deny,				not_identified, console},
	{waiting,		not_identified,	 	cancel,			console},

	{playing,		draw,				acpt,			console},
	{playing,		draw,				deny,			playing},
	{playing,		not_identified,	 	draw,			playing},

	{spectating,	not_identified,		squit,			console},
	{spectating,	play,				acpt,			playing},
	{spectating,	play,				deny,			spectating},
	{spectating,	rematch,			acpt,			playing},
	{spectating,	rematch,			deny,			spectating}
};


void apply_transition(msg_type send_command) {
    for (int i = 0; i < NUM_TRANSITION; i++) {
        if (transitions[i].prev_status == prev_status && 
            transitions[i].recv_command == recv_command &&
            transitions[i].send_command == send_command) {
            prev_status = transitions[i].next_status;
        }
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
	{"PWD_TRUE", "\033[0;34mAccess granted!\033[0m Login done\n"},
	{"PWD_FALSE", "\033[0;35mWrong password!\033[0m Please login (\033[0;33mLOGIN <account>\033[0m) or sign up (\033[0;33mSIGNUP <account>\033[0m):\n"},
	{"SETNAME_SUCESS", "\033[0;34mSetname successful\033[0m\n"},
	{"DUPLICATED", "\033[0;35mYour account is already online!\033[0m"}
};


char *translate(char *server_reply) {
	for (int i = 0; i < NUM_TRANSLATE; i++) {
		if (strcmp(server_reply, Translator[i].server_reply) == 0) {
			return Translator[i].instruction;
		}
	}

	return server_reply;
}
