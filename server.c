#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//unix系统的标准库
#include <unistd.h>
//套接字编程
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 1024
void error_handling(char * message);

int main(){
  int socket_serv;
  int socket_client;
  int option;
  char message[BUF_SIZE];
  int strlen = 0;
  socklen_t optlen,clnt_adr_sz;
  struct sockaddr_in  server_addr;
  struct sockaddr_in client_addr;
  int client_addr_size;
  socket_serv = socket(PF_INET,SOCK_STREAM,0);

  if(socket_serv<0){
    printf("socket() error");
  }
  optlen = sizeof(option);
  option = 1;
  setsockopt(socket_serv,SOL_SOCKET,SO_REUSEADDR,(void*)&option,optlen);


  memset(&server_addr,0,sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(8080);
  
  //使用bind函数进行绑定
  if(bind(socket_serv,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
    printf("bind() error\n");
  }

  //使用listen进行监听
  if(listen(socket_serv,5)<0)
    printf("listen() error");
  while(1){
  client_addr_size = sizeof(client_addr);
  socket_client = accept(socket_serv,(struct sockaddr *)&client_addr,&client_addr_size);
  if(socket_client<0){
    printf("socket() error\n");
  }
  while((strlen = read(socket_client,message,sizeof(message)))!=0){
    write(socket_client,message,strlen);
  }
  }

  // sleep(2);
  close(socket_client);
  close(socket_serv);
  return 0;

}

void error_handling(char* message){
  fputs(message,stderr);
  fputc('\n',stderr);
  exit(1);

}