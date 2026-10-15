#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sockfd;
    char buffer[1024];
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket creation failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        return 1;
    }

    printf("Server is running...\n");

    while (1) {
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr *)&client_addr, &client_len);

        if (n < 0) {
            perror("Receive failed");
            break;
        }

        buffer[n] = '\0';
        printf("Client message: %s\n", buffer);

        if (strcmp(buffer, "exit") == 0) {
            strcpy(buffer, "Server disconnected.");

            sendto(sockfd, buffer, strlen(buffer), 0,
                   (struct sockaddr *)&client_addr, client_len);
            break;
        }

        for (int i = 0; buffer[i] != '\0'; i++) {
            buffer[i] = tolower(buffer[i]);
        }

        sendto(sockfd, buffer, strlen(buffer), 0,
               (struct sockaddr *)&client_addr, client_len);
    }

    close(sockfd);
    printf("Server socket closed.\n");

    return 0;
}
