#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 8080
#define MAXSIZE 1024

void sendhtml(int client_socket,const char *path){
  FILE* file = fopen(path, "r");
  int size = -1;
  if (file==NULL){
    fprintf(stderr, "NO %s file in .\n",path);
    return;
  }
  char buf[MAXSIZE];
  const char* http_head = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
  send(client_socket, http_head, strlen(http_head), 0);
  while ((size = fread(buf, sizeof(char), MAXSIZE, file)) > 0)
   if(send(client_socket, buf, size, 0) == -1){
      const char* http_failed = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n";
      send(client_socket, http_failed, strlen(http_failed), 0);
      break;
    }
  fclose(file);
}

// 由于没有处理多线程因此如果要在浏览器上打开网页需要快速多次重进
int main(int argc, char *argv[]){
  int server_socket = socket(AF_INET, SOCK_STREAM, 0); // 第三个参数为0则自动选择
  if(server_socket == -1){
  fprintf(stderr, "Socket creation failed\n");
  exit(EXIT_FAILURE);
  }

  struct sockaddr_in tcp_server,tcp_client;
  socklen_t socket_len = sizeof(tcp_client);
  memset(&tcp_server, 0, sizeof(tcp_server));
  tcp_server.sin_addr.s_addr=INADDR_ANY;
  tcp_server.sin_family=AF_INET;
  tcp_server.sin_port=htons(PORT);

  if(bind(server_socket, (struct sockaddr*)&tcp_server, sizeof(tcp_server))==-1){
    perror("Socket bind failed\n");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  if(listen(server_socket, 15)==-1){
    perror("Listen failed\n");
    close(server_socket);
    exit(EXIT_FAILURE);
  }

  printf("Server listening on port %d...\n", PORT);
  while (1) {
    int client_socket = accept(server_socket, (struct sockaddr*)&tcp_client, &socket_len);
    if(client_socket==-1){
      perror("Accept filed\n");
      close(client_socket);
    }
    printf("Client connected\n");
    sendhtml(client_socket,"index.html");
    close(client_socket);
    printf("Client disconnected\n");
  }
  close(server_socket);
  return 0;
 }

