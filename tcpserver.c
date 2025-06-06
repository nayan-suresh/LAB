#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
    int serversocket,clientsocket,port;
    struct sockaddr_in serveraddr,clientaddr;
    socklen_t len=sizeof(clientaddr);
    char message[50];
    serversocket=socket(AF_INET,SOCK_STREAM,0);
    printf("Enter the port number:");
    scanf("%d",&port);
    serveraddr.sin_family=AF_INET;
    serveraddr.sin_port=htons(port);
    serveraddr.sin_addr.s_addr=INADDR_ANY;
    bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr));
    listen(serversocket,5);
    printf("Waiting for client...\n");
    clientsocket=accept(serversocket,(struct sockaddr*)&clientaddr,&len);
    printf("client connected\n");
    read(clientsocket,message,sizeof(message));
    printf("Client sent:%s\n",message);
    printf("Sending acknowledgement to client\n");
    write(clientsocket,"message_received",strlen("message_received")+1);
    close(clientsocket);
    close(serversocket);
}
