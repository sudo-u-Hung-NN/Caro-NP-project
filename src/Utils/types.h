#ifndef TYPE_H
#define TYPE_H

#define MSG_TYPE_LEN 23

typedef enum {
	play, go, acpt, deny, cancel, draw, rematch, chat, quit, 
	spec, schat, squit,
	hist, histp, hista,
	ret, listp, listg, setname, signup, signpwd, login, logpwd,
  	not_identified,
	ok, ko, done
} msg_type;


typedef enum {
	playing, spectating, console, waiting
} sts_type;


#endif