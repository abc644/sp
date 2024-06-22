//使用chatGPT生成

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <assert.h>

#define PORT 12345
#define BUFSIZE 1024

void *receive_handler(void *arg) {
    int sockfd = *((int *)arg);
    char recvBuff[BUFSIZE];
    int n;

    while ((n = read(sockfd, recvBuff, BUFSIZE - 1)) > 0) {
        recvBuff[n] = '\0';
        printf("%s", recvBuff);
    }

    return NULL;
}

int main(int argc, char *argv[]) {
    int port = (argc >= 2) ? atoi(argv[1]) : PORT;
    char *host = (argc >= 3) ? argv[2] : "localhost";

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(sockfd >= 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    assert(inet_pton(AF_INET, host, &serv_addr.sin_addr) > 0);
    assert(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0);

    printf("Connected to server %s:%d\n", host, port);

    pthread_t tid;
    pthread_create(&tid, NULL, receive_handler, &sockfd);

    char cmd[BUFSIZE];
    while (1) {
        printf("%s $ ", host);
        fgets(cmd, BUFSIZE, stdin);
        write(sockfd, cmd, strlen(cmd));

        if (strncmp(cmd, "exit", 4) == 0) {
            break;
        }
    }

    close(sockfd);
    return 0;
}
