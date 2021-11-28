#ifndef TYPE_H
#define TYPE_H

#define MSG_TYPE_LEN 23

typedef enum {
	play, go, accept, deny, cancel, draw, rematch, chat, quit, 
	spec, schat, squit,
	hist, histp, hista,
	ret, listp, listg, setname, signin, signpwd, login, logpwd
} msg_type;


typedef enum {
	playing, spectating, console, waiting
} sts_type;


struct {
  char string[25];
  msg_type mtype;
  sts_type usable_in_status[4];
} keywords[MSG_TYPE_LEN] = {
  {"play", play, {console}},
  {"go", go, {playing}},
  {"accept", accept, {console, playing, spectating}},
  {"deny", deny, {console, playing, spectating}},
  {"cancel", cancel, {waiting}},
  {"draw", draw, {playing}},
  {"rematch", rematch, {console}},
  {"chat", chat, {console, playing, spectating}},
  {"quit", quit, {console, playing, spectating, waiting}},
  {"spec", spec, {console}},
  {"schat", schat, {spectating}},
  {"squit", squit, {spectating}},
  {"hist", hist, {console}},
  {"histp", histp, {console, spectating}},
  {"hista", hista, {console}},
  {"ret", ret, {spectating, waiting}},
  {"listp", listp, {console}},
  {"listg", listg, {console}},
  {"setname", setname, {console}},
  {"signin", signin, {console}},
  {"signpwd", signpwd, {console}},
  {"login", login, {console}},
  {"logpwd", logpwd, {console}}
};




#endif