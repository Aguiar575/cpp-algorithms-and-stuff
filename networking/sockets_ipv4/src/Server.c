#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/lib.h"

int main() {
  int server_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (server_socket < 0) {
    error("socket");
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    error("bind");
  }

  if (listen(server_socket, 10) < 0) {
    error("listen");
  }

  struct sockaddr_in client_address;
  socklen_t client_address_len = sizeof(client_address);
  int client_socket = accept(server_socket, (struct sockaddr*)&client_address, &client_address_len);
  if (client_socket < 0) {
    error("accept");
  }

  char buffer[1024];
  int bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
  if (bytes_received < 0) {
    error("recv");
  }

  int bytes_sent = send(client_socket, buffer, bytes_received, 0);
  if (bytes_sent < 0) {
    error("send");
  }

  close(client_socket);
  close(server_socket);

  return 0;
}

