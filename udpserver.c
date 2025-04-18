#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<stdlib.h>
#include<arpa/inet.h>
int main()
{
    int serversocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    char message[50];
    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter port number: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    printf("Waiting for client connection\n");
    recvfrom(serversocket, message, sizeof(message), 0, (struct sockaddr*)&clientaddr, &len);
    printf("Connected to client and received message: %s\n", message);
    sendto(serversocket, "message_received", sizeof("message_received"), 0, (struct sockaddr*)&clientaddr, len);
    printf("Acknowledgement sent to client\n");
    close(serversocket);
}
