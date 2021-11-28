#ifndef TYPE_H
#define TYPE_H

#define MSG_TYPE_LEN 23

typedef enum {
	play, go, accept, deny, cancel, draw, rematch, chat, quit, 
	spec, schat, squit,
	hist, histp, hista,
	ret, listp, listg, setname, signin, signpwd, login, logpwd,
  not_identified
} msg_type;


typedef enum {
	playing, spectating, console, waiting
} sts_type;


struct {
  char string[25];
  msg_type mtype;
  sts_type usable_in_status[4];
  int num_usable;
} keywords[MSG_TYPE_LEN] = {
  {"play", play, {console}, 1},
  {"go", go, {playing}, 1},
  {"accept", accept, {console, playing, spectating}, 3},
  {"deny", deny, {console, playing, spectating}, 3},
  {"cancel", cancel, {waiting}, 1},
  {"draw", draw, {playing}, 1},
  {"rematch", rematch, {console}, 1},
  {"chat", chat, {console, playing, spectating}, 3},
  {"quit", quit, {console, playing, spectating, waiting}, 4},
  {"spec", spec, {console}, 1},
  {"schat", schat, {spectating}, 1},
  {"squit", squit, {spectating}, 1},
  {"hist", hist, {console}, 1},
  {"histp", histp, {console, spectating}, 2},
  {"hista", hista, {console}, 1},
  {"ret", ret, {spectating, waiting}, 2},
  {"listp", listp, {console}, 1},
  {"listg", listg, {console}, 1},
  {"setname", setname, {console}, 1},
  {"signin", signin, {console}, 1},
  {"signpwd", signpwd, {console}, 1},
  {"login", login, {console}, 1},
  {"logpwd", logpwd, {console}, 1}
};




#endif