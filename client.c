#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define SIZE 1024
int main(){
    int clnt_sock;
    int message_len;
    char message[SIZE];
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;
    clnt_sock = socket(PF_INET,SOCK_STREAM,0);
    if(clnt_sock == -1){
        printf("socket() error");
    }
    memset(&clnt_adr,0,sizeof(clnt_adr));
    clnt_adr.sin_family = AF_INET;
    clnt_adr.sin_addr.s_addr =inet_addr("127.0.0.1");
    clnt_adr.sin_port = htons(8080);

    //尝试连接客户端
    if(connect(clnt_sock,(struct sockaddr*)&clnt_adr,sizeof(clnt_adr))){
        printf("connect() error");
        exit(1);
    }
    //输出一下来自服务器的信息
    message_len = read(clnt_sock,message,SIZE-1);
    message[SIZE] = 0;
    printf("Message from server:%s",message);
    close(clnt_sock);
    return 0;
}