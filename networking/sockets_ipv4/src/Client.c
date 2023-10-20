#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include "../include/lib.h"

int main() {
  int client_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (client_socket < 0) {
    error("socker");
  }

  struct sockaddr_in server_address;
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
  if (connect(client_socket, (struct sockaddr*)&server_address, sizeof(server_address)) < 0) {
    error("socker");
 }

  char buffer[1024] = "Hello, world!";
  int bytes_sent = send(client_socket, buffer, sizeof(buffer), 0);
  if (bytes_sent < 0) {
    error("socker");
   }

  char response_buffer[1024];
  int bytes_received = recv(client_socket, response_buffer, sizeof(response_buffer), 0);
  if (bytes_received < 0) {
    error("socker");
  }

  printf("Response from server: %s\n", response_buffer);

  close(client_socket);
}
