#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buf_server[40] = "服务器\0";
  char buf_client[40] = {0};

  int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  struct sockaddr_in tcp;
  memset(&tcp, 0, sizeof(tcp));
  tcp.sin_family = AF_INET;
  if (inet_pton(AF_INET, "127.0.0.1", &tcp.sin_addr) != 1) {
    perror("inet_pton failed");
    close(socket_fd);
    exit(-1);
  }
  tcp.sin_port = htons(12345);
  if (bind(socket_fd, (struct sockaddr *)&tcp, sizeof(tcp)) == -1) {
    perror("bind failed");
    exit(-1);
  }
  listen(socket_fd, 50);
  struct sockaddr_in client;
  while (1) {
    int client_size = sizeof(client);
    int client_fd = accept(socket_fd, (struct sockaddr *)&client, &client_size);
    read(client_fd, buf_client, sizeof(buf_client));
    printf("data from client: %s", buf_client);
    write(client_fd, buf_server, strlen(buf_server));
    close(client_fd);
  }
  close(socket_fd);
  return 0;
}
