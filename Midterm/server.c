//使用chatGPT生成

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024
#define RESPONSE_SIZE 4096

void handle_client(int client_socket);
void send_response(int client_socket, const char *header, const char *content_type, const char *body);

int main() {
    int server_fd, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 建立 socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // 設定 server_addr
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 綁定 socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // 監聽 socket
    if (listen(server_fd, 10) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("HTTP Server is running on port %d\n", PORT);

    // 接受連線
    while ((client_socket = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len)) >= 0) {
        handle_client(client_socket);
        close(client_socket);
    }

    close(server_fd);
    return 0;
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    read(client_socket, buffer, BUFFER_SIZE);
    printf("Received request:\n%s\n", buffer);

    // 處理GET請求
    if (strncmp(buffer, "GET / ", 6) == 0) {
        const char *body = "<html><body><h1>Hello, World!</h1></body></html>";
        send_response(client_socket, "HTTP/1.1 200 OK", "text/html", body);
    } else {
        const char *body = "<html><body><h1>404 Not Found</h1></body></html>";
        send_response(client_socket, "HTTP/1.1 404 Not Found", "text/html", body);
    }
}

void send_response(int client_socket, const char *header, const char *content_type, const char *body) {
    char response[RESPONSE_SIZE];
    snprintf(response, sizeof(response), "%s\nContent-Type: %s\nContent-Length: %lu\n\n%s",
             header, content_type, strlen(body), body);
    write(client_socket, response, strlen(response));
}
