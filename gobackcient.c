#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
int main()
{
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    char data[100];
    int firsttime = 1, curr_packet, wait = 3;
    clientsocket = socket(AF_INET, SOCK_STREAM, 0);
    printf("Enter the port : ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    printf("Starting...\n");
    connect(clientsocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    strcpy(data, "Request");
    send(clientsocket, data, strlen(data), 0);
    do
    {
        int rlen = recv(clientsocket, data, 100, 0);
        data[rlen] = '\0';
        curr_packet = atoi(data);
        printf("Got packet : %d\n", curr_packet);
        if(curr_packet == 3 && firsttime == 1)
        {
            printf("\n***Retransmission simulation : sending RETRANSMIT for packet 1\n");
            strcpy(data, "R1");
            send(clientsocket, data, strlen(data), 0);
            firsttime = 0;
        }
        else
        {
            wait--;
            if(wait == 0)
            {
                printf("packet accepted -> sending ACK\n");
                wait = 3;
                sprintf(data, "A%d", curr_packet);
                send(clientsocket, data, strlen(data), 0);
            }
        }
    } while(curr_packet != 9);
    printf("\nAll packets received....Exiting \n");
    close(clientsocket);
}
