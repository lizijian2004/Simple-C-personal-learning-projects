#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<assert.h>
#include<unistd.h>
#include<stdbool.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main(){
    char buf[BUFSIZ] = {0};
    int tcpClnt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int nByte;
    FILE *fp = fopen("/home/l/下载/服务器模拟传输数据", "a+");

    struct sockaddr_in clnt;
    memset(&clnt, 0, sizeof(clnt));
    clnt.sin_family = AF_INET;
    clnt.sin_addr.s_addr = inet_addr("127.0.0.1");
    clnt.sin_port = htons(1234);

    connect(tcpClnt, (struct sockaddr *)&clnt, sizeof(clnt));
    while ((nByte = read(tcpClnt, buf, BUFSIZ)) > 0){
        fwrite(buf, 1, nByte, fp);
    }
    fclose(fp);
    close(tcpClnt);

    return 0;
}
