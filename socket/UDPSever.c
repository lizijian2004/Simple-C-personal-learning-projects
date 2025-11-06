#include<stdio.h>
#include<stdbool.h>
#include<pthread.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>

int main(){
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    char buf[BUFSIZ] = {0};
    struct sockaddr_in temp;
    memset(&temp, 0, sizeof(temp));
    temp.sin_family = AF_INET;
    temp.sin_addr.s_addr = htonl(INADDR_ANY);
    temp.sin_port = htons(1234);
    bind(sock, (struct sockaddr *)&temp, sizeof(temp));

    struct sockaddr clntTemp;
    int size = sizeof(clntTemp);
    while(true){
        int nByte = recvfrom(sock, buf, BUFSIZ, 0, &clntTemp, &size);
        printf("%s\n", buf);
        sendto(sock, buf, nByte, 0, &clntTemp, size);
    }
    close(sock);
    return 0;
}