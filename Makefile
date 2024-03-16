CC=gcc
CFLAGS=-c -Wall -g 

# Build both client and server.
all: bin/server bin/client 

# SMTP server build files.
run-server: bin/server
	./bin/server

bin/server: bin/parser.o
	$(CC) bin/parser.o -o bin/server

bin/parser.o: server/parser.c
	$(CC) $(CFLAGS) server/parser.c -o bin/parser.o

# SMTP client build files.
#
# TODO: delete this once bin/client exists.
bin/client:

#run-client: bin/client
#	clear
#	./bin/client

#bin/client: bin/test.o
#	$(CC) bin/test.o -o bin/client

#bin/test.o: test.c
#	$(CC) $(CFLAGS) test.c -o bin/test.o
