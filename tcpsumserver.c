#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<sys/socket.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    int a, b, sum = 0;
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter port number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversocket, 5);
    printf("Waiting for client\n");
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);
    printf("Client connected\n");
    read(clientsocket, &a, sizeof(a));
    read(clientsocket, &b, sizeof(b));
    printf("Client sent %d and %d\n", a, b);
    sum = a + b;
    write(clientsocket, &sum, sizeof(sum));
    printf("Sum calculated and sent to client\n");
    close(clientsocket);
    close(serversocket);
}
