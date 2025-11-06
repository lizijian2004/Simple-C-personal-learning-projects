#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  char buf_server[40] = {0};
  char buf_client[40] = "客户端数据\0";

  struct sockaddr_in tcp;
  memset(&tcp, 0, sizeof(tcp));
  tcp.sin_family = AF_INET;
  if (inet_pton(AF_INET, "127.0.0.1", &tcp.sin_addr) != 1) {
    perror("failed inet_pton");
    exit(-1);
  }
  tcp.sin_port = htons(12345);

  for (int i = 0; i < 10; i++) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connect(socket_fd, (struct sockaddr *)&tcp, sizeof(tcp)) == -1) {
      perror("failed connect, retry later");
      close(socket_fd);
      sleep(2);
      continue;
    }
    write(socket_fd, buf_client, strlen(buf_client));
    if (read(socket_fd, buf_server, sizeof(buf_server) - 1) <= 0) {
      perror("failed get data from server");
      close(socket_fd);
      continue;
    }
    printf("data from server: %s", buf_server);
    close(socket_fd);
  }
  return 0;
}
