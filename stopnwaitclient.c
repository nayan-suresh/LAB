#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
typedef struct packet{
    char data[1024];
}Packet;
typedef struct frame{
    int frame_kind;
    int sq_no;
    int ack;
    Packet packet;
}Frame;
int main()
{
    int clientsocket, port;
    struct sockaddr_in serveraddr;
    socklen_t len = sizeof(serveraddr);
    char buffer[1024];
    int frameid = 0;
    Frame frame_send;
    Frame frame_recv;
    int ack_recv = 1;
    clientsocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter port: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    while(1)
    {
        if(ack_recv == 1)
        {
            frame_send.sq_no = frameid;
            frame_send.frame_kind = 1;
            frame_send.ack = 0;
            printf("Enter data: ");
            scanf("%s", buffer);
            strcpy(frame_send.packet.data, buffer);
            sendto(clientsocket, &frame_send, sizeof(frame_send), 0, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
            printf("Frame send\n");
        }
        int frecv_size = recvfrom(clientsocket, &frame_recv, sizeof(frame_recv), 0, (struct sockaddr*)&serveraddr, &len);
        if(frecv_size > 0 && frame_recv.sq_no == 0 && frame_recv.ack == frameid + 1)
        {
            printf("Ack Received\n");
            ack_recv = 1;
        }
        else
        {
            printf("Ack not received\n");
            ack_recv = 0;
        }
        frameid++;
    }
    close(clientsocket);
}
