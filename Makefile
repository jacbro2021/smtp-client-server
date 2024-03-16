CC=gcc
CFLAGS=-c -Wall -Wextra -Werror -Wpedantic -g 

# Build both client and server.
all: bin/server bin/client 

# Clean all build files.
clean: 
	rm -r bin 
	mkdir bin

# SMTP server build files.
run-server: bin/server
	./bin/server

bin/server: bin/server.o bin/parser.o
	$(CC) bin/server.o bin/parser.o -o bin/server

bin/server.o: server/server.c 
	$(CC) $(CFLAGS) server/server.c -o bin/server.o 

bin/parser.o: server/parser.c 
	$(CC) $(CFLAGS) server/parser.c -o bin/parser.o

# SMTP client build files.
# TODO: delete this once bin/client exists.
bin/client:
