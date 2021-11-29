#ifndef CLIENT_H
#define CLIENT_H

#include "types.h"
#include "message.h"

#define NUM_TRANSITION 20

sts_type prev_status = console;
sts_type curr_status = console;

struct {
	sts_type prev_status;
	msg_type recv_command;
	msg_type send_command;
	sts_type next_status;

} transitions [NUM_TRANSITION] = {
	{console,		not_identified,	 	play,			waiting},
	{console,		not_identified,	 	rematch,		waiting},
	{console,		play,				accept,			playing},
	{console,		play,				deny,			console},
	{console,		rematch,			accept,			playing},
	{console,		rematch,			deny,			console},
	{console,		not_identified,	 	spec,			spectating},

	{waiting,		accept,			  	not_identified, playing},
	{waiting,		deny,				not_identified, console},
	{waiting,		not_identified,	 	cancel,			console},

	{playing,		draw,				accept,			console},
	{playing,		draw,				deny,			playing},
	{playing,		not_identified,	 	draw,			playing},

	{spectating,	not_identified,		squit,			console},
	{spectating,	play,				accept,			playing},
	{spectating,	play,				deny,			spectating},
	{spectating,	rematch,			accept,			playing},
	{spectating,	rematch,			deny,			spectating}
};

void apply_transaction(msg_type recv_command, msg_type send_command);



#endif