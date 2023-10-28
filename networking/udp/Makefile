CC = gcc
ARGS = -Wall

all: udpserver udpclient 

udpserver: Server.c
	$(CC) $(ARGS) -o udpserver Server.c

udpclient: Client.c
	$(CC) $(ARGS) -o udpclient Client.c

clean:
	rm -f *.o udpserver udpclient *~
