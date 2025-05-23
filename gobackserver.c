#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int main()
{
    int serversocket, clientsocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    char buffer[100];
    int w_start = 1, w_current = 1, w_end = 4, w_oldstart;
    serversocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter port number : ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    listen(serversocket, 1);
    clientsocket = accept(serversocket, (struct sockaddr*)&clientaddr, &len);
    recv(clientsocket, buffer, 100, 0);
    fcntl(clientsocket, F_SETFL, O_NONBLOCK);
    printf("Connected to client,Sending packets one by one\n");
    do
    {
        if(w_current != w_end)
        {
            sprintf(buffer, "%d", w_current);
            send(clientsocket, buffer, 100, 0);
            printf("Packet send : %d\n", w_current);
            w_current++;
        }
        int rlen = recv(clientsocket, buffer, 100, 0);
        buffer[rlen] = '\0';
        if(buffer[0] == 'R')
        {
            printf("Received a RETRANSMIT packet.\nResending packet no.%c...\n", buffer[1]);
            sprintf(buffer, "%d", atoi(&buffer[1]));
            send(clientsocket, buffer, 100, 0);
            w_current = atoi(&buffer[0]);
            w_current++;
        }
        else if(buffer[0] == 'A')
        {
            w_oldstart = w_start;
            w_start = atoi(&buffer[1]) + 1;
            w_end += (w_start - w_oldstart);
            printf("Received ACK %c.Sliding window....!\n", buffer[1]);
        }
    }while(w_current != 10);
    close(clientsocket);
    close(serversocket);
    printf("sending complete\n");
}
