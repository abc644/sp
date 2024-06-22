//使用chatGPT生成

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <assert.h>

#define PORT 12345
#define MAX_CLIENTS 10
#define BUFSIZE 1024

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int clients[MAX_CLIENTS];
int client_count = 0;

void broadcast(const char *message, int sender) {
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] != sender) {
            write(clients[i], message, strlen(message));
        }
    }
    pthread_mutex_unlock(&mutex);
}

void *client_handler(void *arg) {
    int connfd = *((int *)arg);
    free(arg);

    char cmd[BUFSIZE];
    int len;

    while ((len = read(connfd, cmd, BUFSIZE)) > 0) {
        cmd[len - 1] = '\0'; // Remove newline
        if (strncmp(cmd, "exit", 4) == 0) {
            break;
        }
        broadcast(cmd, connfd);
        FILE *fp = popen(cmd, "r");
        if (fp == NULL) {
            perror("popen");
            break;
        }
        char output[BUFSIZE];
        while (fgets(output, BUFSIZE, fp) != NULL) {
            write(connfd, output, strlen(output));
            broadcast(output, connfd);
        }
        pclose(fp);
    }

    close(connfd);
    pthread_mutex_lock(&mutex);
    for (int i = 0; i < client_count; i++) {
        if (clients[i] == connfd) {
            clients[i] = clients[client_count - 1];
            client_count--;
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}

int main(int argc, char *argv[]) {
    int port = (argc >= 2) ? atoi(argv[1]) : PORT;
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    assert(listenfd >= 0);

    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    assert(bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0);
    assert(listen(listenfd, MAX_CLIENTS) >= 0);

    printf("Server started on port %d\n", port);

    while (1) {
        struct sockaddr_in cli_addr;
        socklen_t cli_len = sizeof(cli_addr);
        int *connfd = malloc(sizeof(int));
        *connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &cli_len);
        assert(*connfd >= 0);

        pthread_t tid;
        pthread_create(&tid, NULL, client_handler, connfd);

        pthread_mutex_lock(&mutex);
        clients[client_count++] = *connfd;
        pthread_mutex_unlock(&mutex);
    }

    close(listenfd);
    return 0;
}
