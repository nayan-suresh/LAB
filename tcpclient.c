#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<netdb.h>
#include<strings.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    char message[50];
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter port: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("Connected to server.\n");
    send(clientsocket, "Im client", sizeof("Im client"),0);
    printf("Message sent\n");
    recv(clientsocket, message, sizeof(message), 0);
    printf("From server: %s\n", message);
    close(clientsocket);
}
