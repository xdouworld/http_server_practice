#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//unix系统的标准库
#include <unistd.h>
//套接字编程
#include <arpa/inet.h>
#include <sys/socket.h>

void error_handling(char * message);

#define BUF_SIZE 1024
int main(){
    int socket_server;
    int str_len;
    int recv_cnt;
    char message[BUF_SIZE];
    struct sockaddr_in socket_addr;
    
    //创建socket套接字
    socket_server = socket(PF_INET,SOCK_STREAM,0);
    if(socket<0){
        printf("socket() error\n");
    }
    memset(&socket_addr,0,sizeof(socket_addr));
    socket_addr.sin_family = AF_INET;
    socket_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socket_addr.sin_port = htons(8080);

    if(connect(socket_server,(struct sockaddr*)&socket_addr,sizeof(socket_addr))){
        printf("connect() error\n");
    }

    while(1){
    fputs("input message (Q to quit): ",stdout);
    fgets(message,BUF_SIZE,stdin);
    if(!strcmp(message,"q\n") || !strcmp(message,"Q\n")){
        break;
    }
// printf("Message :%s",message);
    str_len = write(socket_server,message,strlen(message));

    if(str_len<0){
        printf("read() error\n");
    }
    int recv_len = 0;
    while(recv_len<str_len){
        recv_cnt = read(socket_server,&message[recv_len],BUF_SIZE-1);
        if(recv_cnt<0){
            printf("read() error");
        }
        recv_len += recv_cnt;
    }
    message[recv_len] = 0;
    printf("Message from server :%s",message);
    }
    
    close(socket_server);
}



void error_handling(char* message){
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);

}