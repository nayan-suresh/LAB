#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<unistd.h>
#include<arpa/inet.h>
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
    int serversocket, port;
    struct sockaddr_in serveraddr, clientaddr;
    socklen_t len = sizeof(clientaddr);
    int frameid = 0;
    Frame frame_recv;
    Frame frame_send;
    serversocket = socket(AF_INET, SOCK_DGRAM, 0);
    printf("Enter the port no: ");
    scanf("%d", &port);
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port = htons(port);
    serveraddr.sin_addr.s_addr = INADDR_ANY;
    bind(serversocket, (struct sockaddr*)&serveraddr, sizeof(serveraddr));
    while(1)
    {
        int frecv_size = recvfrom(serversocket, &frame_recv, sizeof(frame_recv), 0, (struct sockaddr*)&clientaddr, &len);
        if(frecv_size > 0 && frame_recv.frame_kind == 1 && frame_recv.sq_no == frameid)
        {
            printf("Frame received: %s\n", frame_recv.packet.data);
            frame_send.sq_no = 0;
            frame_send.frame_kind = 0;
            frame_send.ack = frame_recv.sq_no + 1;
            sendto(serversocket, &frame_send, sizeof(frame_send), 0, (struct sockaddr*)&clientaddr, len);
            printf("Ack send\n");
        }
        else
        {
            printf("Frame not received\n");
        }
        frameid++;
    }
    close(serversocket);
}
