#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>


void error_handling(char* message);

int main(){

    int serv_sock;
    int clnt_sock;

    //存储服务器ip，端口信息的结构体
    struct sockaddr_in serv_adr;
    //存储客户端ip,端口信息的结构体
    struct sockaddr_in clnt_adr;
    socklen_t clnt_adr_sz;
    serv_sock = socket(PF_INET,SOCK_STREAM,0);
    if(serv_sock == -1){
        printf("socket() error");
    }
    memset(&serv_adr,0,sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr =htonl(INADDR_ANY);
    serv_adr.sin_port = htons(8080);
    if(bind(serv_sock,(struct sockaddr*)&serv_adr,sizeof(serv_adr))==-1){
        printf("bind() error");
    }
    if(listen(serv_sock,5) == -1){
        printf("liisten() error");
    }

    //监听客户端信息
    clnt_adr_sz = sizeof(clnt_adr);
    clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_adr,&clnt_adr_sz);
    if(clnt_sock == -1){
        printf("accept() error");
    }
    char meassge[] = "hello,world!\n";
    write(clnt_sock,meassge,sizeof(meassge));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}