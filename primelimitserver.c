#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>

int is_prime(int num) {
    if (num < 2) return 0;
    for (int i = 2; i <= num / 2; i++) {
        if (num % i == 0) return 0;
    }
    return 1;
}

int main() {
    int sockfd, newsockfd, port = 8080;
    struct sockaddr_in serv_addr, cli_addr;
    socklen_t clilen;
    int limit, i;
    char buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);

    read(newsockfd, &limit, sizeof(limit));
    sprintf(buffer, "Prime numbers up to %d:\n", limit);
    for (i = 2; i <= limit; i++) {
        if (is_prime(i)) {
            char temp[10];
            sprintf(temp, "%d ", i);
            strcat(buffer, temp);
        }
    }
    write(newsockfd, buffer, strlen(buffer) + 1);
    close(newsockfd);
    close(sockfd);
    return 0;
}
