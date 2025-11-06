#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>
#include<assert.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(){
    char buf[BUFSIZ];
    FILE *fp = fopen("/home/l/文档/学习记录/测试的废话", "r");
    assert(fp);
    int nByte;
    assert(fp);
    int tcpSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in tcpSever;
    memset(&tcpSever, 0, sizeof(tcpSever));
    tcpSever.sin_family = AF_INET;
    tcpSever.sin_addr.s_addr = inet_addr("127.0.0.1");
    tcpSever.sin_port = htons(1234);
    bind(tcpSock, (struct sockaddr *)&tcpSever, sizeof(tcpSever));

    listen(tcpSock, 20);
    
    struct sockaddr_in tcpClnt;
    int size = sizeof(tcpClnt);
    while (true){
        int tcpClntSock = accept(tcpSock, (struct sockaddr *)&tcpClnt, &size);
        while ((nByte = fread(buf,1,BUFSIZ,fp)) > 0){
            write(tcpClntSock, buf, nByte);
        }
        ftell(fp);
        shutdown(tcpClntSock, SHUT_WR);
        read(tcpClntSock, buf, sizeof(buf) - 1);
        close(tcpClntSock);
        memset(buf, 0, BUFSIZ);
    }
    fclose(fp);
    close(tcpSock);
    return 0;
}
