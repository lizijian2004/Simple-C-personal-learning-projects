#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define INETADDR "127.0.0.1"
int main(int argc, char *argv[]){
  struct sockaddr_in client_socket;
  int len = sizeof(client_socket);
  memset(&client_socket, 0, len);
  client_socket.sin_family = AF_INET;
  client_socket.sin_addr.s_addr=inet_addr(INETADDR);
  client_socket.sin_port=htons(PORT);

  while (1) {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if(fd==-1){
      perror("create socket failed\n");
      sleep(2);
      continue;
    }
    if(connect(fd, (struct sockaddr*)&client_socket, len)==-1){
      perror("create connect failed\n");
      // 连接失败则关闭客户端, 或重新连接, 这里演示选择简单处理
      close(fd);
      sleep(2);
      continue;
    }
    /*
     * 这里用于处理业务, 大概率是 read, send 等函数
    */
    close(fd);
  }
  return 0;
}
