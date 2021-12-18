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

SERVER_USERS_FILE := $(BUILDDIR)/user.o $(BUILDDIR)/utils.o
SERVER_FUNCTIONS_FILE := $(BUILDDIR)/sign_in_up.o $(BUILDDIR)/setname.o $(BUILDDIR)/list.o
SERVERSIDE_REQUIREMENTS := $(SERVER_FUNCTIONS_FILE) $(SERVER_USERS_FILE)


# ====================== DEFINE UTILS ==============================
UTILS_FILE := $(BUILDDIR)/error.o $(BUILDDIR)/message.o $(BUILDDIR)/logger.o



all: $(EXEDIR)/server $(EXEDIR)/client $(UTILS_FILE) $(TEST)/test_user


#========================== COMPILATION ============================
#==========================< Server >===============================
$(EXEDIR)/server: $(BUILDDIR)/tcp_server.o $(BUILDDIR)/server_helper.o $(SERVERSIDE_REQUIREMENTS) $(UTILS_FILE)
	$(CC) $(BUILDDIR)/tcp_server.o $(BUILDDIR)/server_helper.o $(SERVERSIDE_REQUIREMENTS) $(UTILS_FILE) -o $(EXEDIR)/server

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
$(BUILDDIR)/sign_in_up.o: $(SERVER_FUNCTIONS)/sign_in_up.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/sign_in_up.c -o $(BUILDDIR)/sign_in_up.o

$(BUILDDIR)/setname.o: $(SERVER_FUNCTIONS)/setname.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/setname.c -o $(BUILDDIR)/setname.o

$(BUILDDIR)/list.o: $(SERVER_FUNCTIONS)/list.c
	$(CC) $(FLAGS) $(SERVER_FUNCTIONS)/list.c -o $(BUILDDIR)/list.o



#==========================< Client >===============================
$(EXEDIR)/client: $(BUILDDIR)/tcp_client.o $(BUILDDIR)/client_helper.o $(UTILS_FILE)
	$(CC) $(BUILDDIR)/tcp_client.o $(BUILDDIR)/client_helper.o $(UTILS_FILE) -o $(EXEDIR)/client

$(BUILDDIR)/tcp_client.o: $(CLIENTSIDE)/tcp_client.c
	$(CC) $(FLAGS) $(CLIENTSIDE)/tcp_client.c -o $(BUILDDIR)/tcp_client.o

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
	rm -f $(EXEDIR)/server $(EXEDIR)/client