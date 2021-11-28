CC = gcc
FLAGS = -Wall -g -c

SOURCEDIR = src
CSOURCEDIR = $(SOURCEDIR)/Csrc
HSOURCEDIR = $(SOURCEDIR)/Hsrc

BUILDDIR = build

EXEDIR = exec

all: $(EXEDIR)/server $(EXEDIR)/client

$(EXEDIR)/server: $(BUILDDIR)/tcp_server.o
	$(CC) $(BUILDDIR)/tcp_server.o -o $(EXEDIR)/server

$(BUILDDIR)/tcp_server.o: $(CSOURCEDIR)/tcp_server.c $(HSOURCEDIR)/server.h
	$(CC) $(FLAGS) $(CSOURCEDIR)/tcp_server.c -o $(BUILDDIR)/tcp_server.o

$(EXEDIR)/client: $(BUILDDIR)/tcp_client.o
	$(CC) $(BUILDDIR)/tcp_client.o -o $(EXEDIR)/client

$(BUILDDIR)/tcp_client.o: $(CSOURCEDIR)/tcp_client.c
	$(CC) $(FLAGS) $(CSOURCEDIR)/tcp_client.c -o $(BUILDDIR)/tcp_client.o

clean:
	rm -f $(BUILDDIR)/*.o
	rm -f $(EXEDIR)/server $(EXEDIR)/client