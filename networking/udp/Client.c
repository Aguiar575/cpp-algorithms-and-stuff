#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFSIZE 1024

typedef struct {
  int sockfd;
  struct sockaddr_in serveraddr;
} Client;

void error(char *msg) {
  perror(msg);
  exit(1);
}

void init_client(Client *client, int portno) {
  client->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (client->sockfd < 0) {
    error("ERROR opening socket");
  }

  bzero((char *)&client->serveraddr, sizeof(client->serveraddr));
  client->serveraddr.sin_family = AF_INET;
  client->serveraddr.sin_port = htons((unsigned short)portno);
}

void send_message(Client *client, const char *message) {
  int n = sendto(client->sockfd, message, strlen(message), 0,
                 (struct sockaddr *)&client->serveraddr,
                 sizeof(client->serveraddr));
  if (n < 0) {
    error("ERROR in sendto");
  }
}

void receive_message(Client *client, char *buf) {
  int n = recvfrom(client->sockfd, buf, BUFSIZE, 0, NULL, NULL);
  if (n < 0) {
    error("ERROR in recvfrom");
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  int portno = atoi(argv[1]);

  Client client;
  init_client(&client, portno);

  char buf[BUFSIZE];

  printf("Please enter msg: ");
  fgets(buf, BUFSIZE, stdin);

  send_message(&client, buf);
  receive_message(&client, buf);

  printf("Echo from server: %s", buf);

  return 0;
}
