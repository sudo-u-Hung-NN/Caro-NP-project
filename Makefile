CC = gcc
FLAGS = -Wall -g -c

CLIENTSIDE = src/Client_side
SERVERSIDE = src/Server_side
UTILS = src/Utils

BUILDDIR = build

EXEDIR = exec

UTILS_FILE := $(BUILDDIR)/error.o $(BUILDDIR)/message.o

all: $(EXEDIR)/server $(EXEDIR)/client $(UTILS_FILE)

#==========================< Server >===============================
$(EXEDIR)/server: $(BUILDDIR)/tcp_server.o $(BUILDDIR)/server_helper.o $(UTILS_FILE)
	$(CC) $(BUILDDIR)/tcp_server.o $(BUILDDIR)/server_helper.o $(UTILS_FILE) -o $(EXEDIR)/server

$(BUILDDIR)/tcp_server.o: $(SERVERSIDE)/tcp_server.c
	$(CC) $(FLAGS) $(SERVERSIDE)/tcp_server.c -o $(BUILDDIR)/tcp_server.o

$(BUILDDIR)/server_helper.o: $(SERVERSIDE)/server_helper.c
	$(CC) $(FLAGS) $(SERVERSIDE)/server_helper.c -o $(BUILDDIR)/server_helper.o


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



clean:
	rm -f $(BUILDDIR)/*.o
	rm -f $(EXEDIR)/server $(EXEDIR)/client