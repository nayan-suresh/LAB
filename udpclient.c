#include<netinet/in.h>
#include<netdb.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    char message[50];
    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter port: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    sendto(clientsocket, "Hi,im client", sizeof("Hi,im client"), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("Message sent to server\n");
    recvfrom(clientsocket, message, sizeof(message), 0, (struct sockaddr*)&serveraddr, &len);
    printf("Message from server: %s\n", message);
    close(clientsocket);
}
