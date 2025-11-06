#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    char buf[BUFSIZ] = {"无用的测试数据"};

    struct sockaddr_in clnt;
    memset(&clnt, 0, sizeof(clnt));
    clnt.sin_family = AF_INET;
    clnt.sin_addr.s_addr = inet_addr("127.0.0.1");
    clnt.sin_port = htons(1234);
    
    struct sockaddr sever;
    int size = sizeof(sever);

    while (true){
        sendto(sock, buf, BUFSIZ, 0, (struct sockaddr_in*)&clnt, sizeof(clnt));
        recvfrom(sock, buf, BUFSIZ, 0, (struct sockaddr*)&sever, &size);
        printf("%s\n", buf);
        close(sock);
    }
    return 0;
 
}