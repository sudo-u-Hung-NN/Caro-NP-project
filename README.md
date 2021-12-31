# Caro-NP-project

First, create the following folders:
1. build/
2. exec/
3. test/

## Folder Tree
The folder organization should look like this:

```text
.
├── LICENSE
├── Makefile
├── README.md
├── build
├── exec
├── src
│   ├── Client_side
│   │   ├── client_helper.c
│   │   ├── client_helper.h
│   │   ├── client_listener.c
│   │   ├── client_speaker.c
│   │   └── tcp_client.c
│   ├── Server_side
│   │   ├── Database
│   │   │   ├── Accounts
│   │   │   │   ├── admin123.hist
│   │   │   │   └── all.ranking
│   │   │   └── Users.csv
│   │   ├── Functions
│   │   │   ├── accept.c
│   │   │   ├── cancel.c
│   │   │   ├── chat.c
│   │   │   ├── deny.c
│   │   │   ├── draw.c
│   │   │   ├── go.c
│   │   │   ├── hist.c
│   │   │   ├── list.c
│   │   │   ├── log_in.c
│   │   │   ├── play.c
│   │   │   ├── quit.c
│   │   │   ├── rematch.c
│   │   │   ├── return.c
│   │   │   ├── setname.c
│   │   │   ├── sign_up.c
│   │   │   └── spec.c
│   │   ├── Game
│   │   │   ├── caro_main.c
│   │   │   ├── game.c
│   │   │   ├── game.h
│   │   │   ├── game_tree.c
│   │   │   ├── player.c
│   │   │   └── spectator.c
│   │   ├── Users
│   │   │   ├── test_user.c
│   │   │   ├── user.c
│   │   │   ├── user.h
│   │   │   └── utils.c
│   │   ├── server_helper.c
│   │   ├── server_helper.h
│   │   └── tcp_server.c
│   └── Utils
│       ├── data.h
│       ├── error.c
│       ├── error.h
│       ├── logger.c
│       ├── logger.h
│       ├── message.c
│       ├── message.h
│       └── types.h
└── test
```

## How to run code
1. **Run Makefile** with:
```bash
make clean
make
```
Then the result should be like this
```bash
gcc -Wall -g -c src/Server_side/server_helper.c -o build/server_helper.o
gcc -Wall -g -c src/Server_side/Functions/play.c -o build/play.o
gcc -Wall -g -c src/Server_side/Functions/accept.c -o build/accept.o
gcc -Wall -g -c src/Server_side/Functions/deny.c -o build/deny.o
gcc -Wall -g -c src/Server_side/Functions/go.c -o build/go.o
gcc -Wall -g -c src/Server_side/Functions/draw.c -o build/draw.o
gcc -Wall -g -c src/Server_side/Functions/rematch.c -o build/rematch.o
gcc -Wall -g -c src/Server_side/Functions/chat.c -o build/chat.o
gcc -Wall -g -c src/Server_side/Functions/cancel.c -o build/cancel.o
gcc -Wall -g -c src/Server_side/Functions/return.c -o build/return.o
gcc -Wall -g -c src/Server_side/Functions/quit.c -o build/quit.o
gcc -Wall -g -c src/Server_side/Functions/spec.c -o build/spec.o
gcc -Wall -g -c src/Server_side/Functions/hist.c -o build/hist.o
gcc -Wall -g -c src/Server_side/Functions/list.c -o build/list.o
gcc -Wall -g -c src/Server_side/Functions/setname.c -o build/setname.o
gcc -Wall -g -c src/Server_side/Functions/sign_up.c -o build/sign_up.o
gcc -Wall -g -c src/Server_side/Functions/log_in.c -o build/log_in.o
gcc -Wall -g -c src/Server_side/Users/user.c -o build/user.o
gcc -Wall -g -c src/Server_side/Users/utils.c -o build/utils.o
gcc -Wall -g -c src/Server_side/Game/game.c -o build/game.o
gcc -Wall -g -c src/Server_side/Game/player.c -o build/player.o
gcc -Wall -g -c src/Server_side/Game/game_tree.c -o build/game_tree.o
gcc -Wall -g -c src/Server_side/Game/spectator.c -o build/spectator.o
gcc -Wall -g -c src/Utils/error.c -o build/error.o
gcc -Wall -g -c src/Utils/message.c -o build/message.o
gcc -Wall -g -c src/Utils/logger.c -o build/logger.o
gcc -pthread build/tcp_server.o build/server_helper.o build/play.o build/accept.o build/deny.o build/go.o build/draw.o build/rematch.o build/chat.o build/cancel.o build/return.o build/quit.o build/spec.o build/hist.o build/list.o build/setname.o build/sign_up.o build/log_in.o build/user.o build/utils.o build/game.o build/player.o build/game_tree.o build/spectator.o build/error.o build/message.o build/logger.o -o exec/server
gcc -Wall -g -c src/Client_side/tcp_client.c -o build/tcp_client.o
gcc -Wall -g -c src/Client_side/client_listener.c -o build/client_listener.o
gcc -Wall -g -c src/Client_side/client_speaker.c -o build/client_speaker.o
gcc -Wall -g -c src/Client_side/client_helper.c -o build/client_helper.o
gcc -pthread build/tcp_client.o build/client_listener.o build/client_speaker.o build/client_helper.o build/error.o build/message.o build/logger.o -o exec/client
gcc -Wall -g -c src/Server_side/Users/test_user.c -o build/test_user.o
gcc build/test_user.o build/user.o build/utils.o build/error.o build/message.o build/logger.o -o test/test_user
```
2. **Run server**
```bash
./exec/server
```
Then the result should be like this
```text
INFOR: Loading user tree
INFOR: src/Server_side/Database/Users.csv
INFOR: Loading user's database...
INFOR: Loaded user tree
```
3. **Run client**
```bash
./exec/client
```
Then the result should be like this
```text
Server accepts the client_speaker_sock...
Server accepts the client_listener_sock...
console SERVER: Please login (LOGIN <account>) or sign up (SIGNUP <account>):
```

## Config the code
If you make changes to the code, you need not to modify the makefile. However, if you add more files into the source code, add compile rule follow the patterns given in the Makefile:

```Makefile
CC = gcc
FLAGS = -Wall -g -c
BUILDDIR = build
EXEDIR = exec
TEST = test


# ====================== DEFINE CLIENT =============================
CLIENTSIDE = src/Client_side
SERVERSIDE = src/Server_side
UTILS = src/Utils


# ====================== DEFINE SERVER =============================
SERVER_USERS = src/Server_side/Users
SERVER_GAMEPLAY = src/Server_side/Gameplays
SERVER_FUNCTIONS = src/Server_side/Functions
SERVER_GAME = src/Server_side/Game

SERVER_USERS_FILE := $(BUILDDIR)/user.o $(BUILDDIR)/utils.o

SERVER_FUNCTIONS_FILE := $(BUILDDIR)/play.o $(BUILDDIR)/accept.o $(BUILDDIR)/deny.o $(BUILDDIR)/go.o $(BUILDDIR)/draw.o $(BUILDDIR)/rematch.o \
						$(BUILDDIR)/chat.o $(BUILDDIR)/cancel.o $(BUILDDIR)/return.o $(BUILDDIR)/quit.o \
						$(BUILDDIR)/spec.o \
						$(BUILDDIR)/hist.o \
						$(BUILDDIR)/list.o $(BUILDDIR)/setname.o $(BUILDDIR)/sign_up.o $(BUILDDIR)/log_in.o



SERVER_GAME_FILE := $(BUILDDIR)/game.o $(BUILDDIR)/player.o $(BUILDDIR)/game_tree.o $(BUILDDIR)/spectator.o

SERVERSIDE_REQUIREMENTS := $(SERVER_FUNCTIONS_FILE) $(SERVER_USERS_FILE) $(SERVER_GAME_FILE)


# ====================== DEFINE UTILS ==============================
UTILS_FILE := $(BUILDDIR)/error.o $(BUILDDIR)/message.o $(BUILDDIR)/logger.o



all: $(EXEDIR)/server $(EXEDIR)/client $(UTILS_FILE) $(TEST)/test_user


#========================== COMPILATION ============================
#==========================< Server >===============================
$(EXEDIR)/server: $(BUILDDIR)/tcp_server.o $(BUILDDIR)/server_helper.o $(SERVERSIDE_REQUIREMENTS) $(UTILS_FILE)
	$(CC) -pthread $(BUILDDIR)/tcp_server.o $(BUILDDIR)/server_helper.o $(SERVERSIDE_REQUIREMENTS) $(UTILS_FILE) -o $(EXEDIR)/server

$(BUILDDIR)/tcp_server.o: $(SERVERSIDE)/tcp_server.c
	$(CC) $(FLAGS) $(SERVERSIDE)/tcp_server.c -o $(BUILDDIR)/tcp_server.o

$(BUILDDIR)/server_helper.o: $(SERVERSIDE)/server_helper.c
	$(CC) $(FLAGS) $(SERVERSIDE)/server_helper.c -o $(BUILDDIR)/server_helper.o



#=====================< Server User files >=========================
$(BUILDDIR)/user.o: $(SERVER_USERS)/user.c
	$(CC) $(FLAGS) $(SERVER_USERS)/user.c -o $(BUILDDIR)/user.o

$(BUILDDIR)/utils.o: $(SERVER_USERS)/utils.c
	$(CC) $(FLAGS) $(SERVER_USERS)/utils.c -o $(BUILDDIR)/utils.o



#=====================< Server Functions >==========================
# 1. Game
$(BUILDDIR)/play.o: $(SERVER_FUNCTIONS)/play.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/play.c -o $(BUILDDIR)/play.o

$(BUILDDIR)/accept.o: $(SERVER_FUNCTIONS)/accept.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/accept.c -o $(BUILDDIR)/accept.o

$(BUILDDIR)/deny.o: $(SERVER_FUNCTIONS)/deny.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/deny.c -o $(BUILDDIR)/deny.o

$(BUILDDIR)/go.o: $(SERVER_FUNCTIONS)/go.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/go.c -o $(BUILDDIR)/go.o

$(BUILDDIR)/draw.o: $(SERVER_FUNCTIONS)/draw.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/draw.c -o $(BUILDDIR)/draw.o

$(BUILDDIR)/rematch.o: $(SERVER_FUNCTIONS)/rematch.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/rematch.c -o $(BUILDDIR)/rematch.o

# 2. Norm
$(BUILDDIR)/chat.o: $(SERVER_FUNCTIONS)/chat.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/chat.c -o $(BUILDDIR)/chat.o

$(BUILDDIR)/quit.o: $(SERVER_FUNCTIONS)/quit.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/quit.c -o $(BUILDDIR)/quit.o

$(BUILDDIR)/cancel.o: $(SERVER_FUNCTIONS)/cancel.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/cancel.c -o $(BUILDDIR)/cancel.o

$(BUILDDIR)/return.o: $(SERVER_FUNCTIONS)/return.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/return.c -o $(BUILDDIR)/return.o

# 3. Spec
$(BUILDDIR)/spec.o: $(SERVER_FUNCTIONS)/spec.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/spec.c -o $(BUILDDIR)/spec.o

# 4. Hist
$(BUILDDIR)/hist.o: $(SERVER_FUNCTIONS)/hist.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/hist.c -o $(BUILDDIR)/hist.o


# 5. Utils
$(BUILDDIR)/list.o: $(SERVER_FUNCTIONS)/list.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/list.c -o $(BUILDDIR)/list.o

$(BUILDDIR)/setname.o: $(SERVER_FUNCTIONS)/setname.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/setname.c -o $(BUILDDIR)/setname.o

$(BUILDDIR)/sign_up.o: $(SERVER_FUNCTIONS)/sign_up.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/sign_up.c -o $(BUILDDIR)/sign_up.o

$(BUILDDIR)/log_in.o: $(SERVER_FUNCTIONS)/log_in.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/log_in.c -o $(BUILDDIR)/log_in.o



#==========================< Server Game >==========================
$(BUILDDIR)/game.o: $(SERVER_GAME)/game.c
	$(CC) $(FLAGS) $(SERVER_GAME)/game.c -o $(BUILDDIR)/game.o

$(BUILDDIR)/player.o: $(SERVER_GAME)/player.c
	$(CC) $(FLAGS) $(SERVER_GAME)/player.c -o $(BUILDDIR)/player.o

$(BUILDDIR)/game_tree.o: $(SERVER_GAME)/game_tree.c
	$(CC) $(FLAGS) $(SERVER_GAME)/game_tree.c -o $(BUILDDIR)/game_tree.o

$(BUILDDIR)/spectator.o: $(SERVER_GAME)/spectator.c
	$(CC) $(FLAGS) $(SERVER_GAME)/spectator.c -o $(BUILDDIR)/spectator.o


#==========================< Client >===============================
$(EXEDIR)/client: $(BUILDDIR)/tcp_client.o $(BUILDDIR)/client_listener.o $(BUILDDIR)/client_speaker.o $(BUILDDIR)/client_helper.o $(UTILS_FILE)
	$(CC) -pthread $(BUILDDIR)/tcp_client.o $(BUILDDIR)/client_listener.o $(BUILDDIR)/client_speaker.o $(BUILDDIR)/client_helper.o $(UTILS_FILE) -o $(EXEDIR)/client

$(BUILDDIR)/tcp_client.o: $(CLIENTSIDE)/tcp_client.c
	$(CC) $(FLAGS) $(CLIENTSIDE)/tcp_client.c -o $(BUILDDIR)/tcp_client.o

$(BUILDDIR)/client_listener.o: $(CLIENTSIDE)/client_listener.c
	$(CC) $(FLAGS) $(CLIENTSIDE)/client_listener.c -o $(BUILDDIR)/client_listener.o

$(BUILDDIR)/client_speaker.o: $(CLIENTSIDE)/client_speaker.c
	$(CC) $(FLAGS) $(CLIENTSIDE)/client_speaker.c -o $(BUILDDIR)/client_speaker.o

$(BUILDDIR)/client_helper.o: $(CLIENTSIDE)/client_helper.c
	$(CC) $(FLAGS) $(CLIENTSIDE)/client_helper.c -o $(BUILDDIR)/client_helper.o


#==========================< Utils >=================================
$(BUILDDIR)/error.o: $(UTILS)/error.c
	$(CC) $(FLAGS) $(UTILS)/error.c -o $(BUILDDIR)/error.o

$(BUILDDIR)/message.o: $(UTILS)/message.c
	$(CC) $(FLAGS) $(UTILS)/message.c -o $(BUILDDIR)/message.o

$(BUILDDIR)/logger.o: $(UTILS)/logger.c
	$(CC) $(FLAGS) $(UTILS)/logger.c -o $(BUILDDIR)/logger.o



#==========================< Testing >===============================
$(TEST)/test_user: $(BUILDDIR)/test_user.o $(BUILDDIR)/user.o $(BUILDDIR)/utils.o $(UTILS_FILE)
	$(CC) $(BUILDDIR)/test_user.o $(BUILDDIR)/user.o $(BUILDDIR)/utils.o $(UTILS_FILE) -o $(TEST)/test_user

$(BUILDDIR)/test_user.o: $(SERVER_USERS)/test_user.c
	$(CC) $(FLAGS) $(SERVER_USERS)/test_user.c -o $(BUILDDIR)/test_user.o



clean:
	rm -f $(BUILDDIR)/*.o
	rm -f $(EXEDIR)/*
	rm -f $(TEST)/*
```

