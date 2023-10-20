CC = gcc
CFLAGS = -Wall -Iinclude
BUILD_DIR = build

# List the source files
SERVER_SRC = src/server.c src/lib.c
CLIENT_SRC = src/client.c src/lib.c

# Output executables
SERVER_EXEC = $(BUILD_DIR)/server
CLIENT_EXEC = $(BUILD_DIR)/client

all: $(SERVER_EXEC) $(CLIENT_EXEC) run-both

$(SERVER_EXEC): $(SERVER_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

$(CLIENT_EXEC): $(CLIENT_SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^

run-both: 
	$(SERVER_EXEC) & $(CLIENT_EXEC)

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean run-both

