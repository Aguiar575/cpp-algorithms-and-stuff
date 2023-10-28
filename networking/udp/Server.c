#include <arpa/inet.h>
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
} Server;

void error(char *msg) {
  perror(msg);
  exit(1);
}

void init_server(Server *server, int portno) {
  server->sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (server->sockfd < 0) {
    error("ERROR opening socket");
  }

  // Set the SO_REUSEADDR option on the socket. This allows the server to be
  // restarted immediately after it is killed, without having to wait for the
  // socket to be closed.
  int optval = 1;
  setsockopt(server->sockfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval,
             sizeof(int));

  bzero((char *)&server->serveraddr, sizeof(server->serveraddr));
  server->serveraddr.sin_family = AF_INET;
  server->serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
  server->serveraddr.sin_port = htons((unsigned short)portno);

  if (bind(server->sockfd, (struct sockaddr *)&server->serveraddr,
           sizeof(server->serveraddr)) < 0) {
    error("ERROR on binding");
  }
}

void handle_client(Server *server) {
  char buf[BUFSIZE];
  int n;

  // Receive a datagram from the client.
  n = recvfrom(server->sockfd, buf, BUFSIZE, 0, NULL, NULL);
  if (n < 0) {
    error("ERROR in recvfrom");
  }

  // Print the client's IP address and the contents of the datagram.
  printf("server received datagram from %s\n", buf);

  // Echo the datagram back to the client.
  n = sendto(server->sockfd, buf, strlen(buf), 0,
             (struct sockaddr *)&server->serveraddr,
             sizeof(server->serveraddr));
  if (n < 0) {
    error("ERROR in sendto");
  }
}

int main(int argc, char **argv) {
  if (argc != 2) {
    fprintf(stderr, "usage: %s <port>\n", argv[0]);
    exit(1);
  }

  int portno = atoi(argv[1]);

  Server server;
  init_server(&server, portno);

  while (1) {
    handle_client(&server);
  }

  return 0;
}
