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
    int a, b, sum = 0;
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter port number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("Connected to the server\n");
    printf("Enter two numbers: ");
    scanf("%d%d", &a, &b);
    send(clientsocket, &a, sizeof(a), 0);
    send(clientsocket, &b, sizeof(b), 0);
    printf("Numbers sent to server\n");
    recv(clientsocket, &sum, sizeof(sum), 0);
    printf("Sum received from server: %d\n", sum);
    close(clientsocket);
}
