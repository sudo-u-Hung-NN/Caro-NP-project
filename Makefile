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



SERVER_GAME_FILE := $(BUILDDIR)/game.o $(BUILDDIR)/player.o $(BUILDDIR)/game_tree.o

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