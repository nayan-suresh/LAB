#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    int sockfd, limit;
    struct sockaddr_in serv_addr;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

    printf("Enter limit: ");
    scanf("%d", &limit);

    write(sockfd, &limit, sizeof(limit));
    read(sockfd, buffer, sizeof(buffer));
    printf("%s\n", buffer);

    close(sockfd);
    return 0;
}
