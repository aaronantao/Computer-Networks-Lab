// Server side
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sockfd;
    char buﬀer[1024];
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd < 0) {
        perror("Socket crea on failed");
        return 1;
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        printf("Enter a string (exit to quit): ");
        fgets(buﬀer, sizeof(buﬀer), stdin);
        buﬀer[strcspn(buﬀer, "\n")] = '\0';

        sendto(sockfd, buﬀer, strlen(buﬀer), 0,
               (struct sockaddr *)&server_addr, len);

        memset(buﬀer, 0, sizeof(buﬀer));

        int n = recvfrom(sockfd, buﬀer, sizeof(buﬀer) - 1, 0,
                         NULL, NULL);

        if (n < 0) {
            perror("Receive failed");
            break;
        }

        buﬀer[n] = '\0';
        printf("Server response: %s\n", buﬀer);

        if (strcmp(buﬀer, "Server disconnected.") == 0)
            break;
    }

    close(sockfd);
    printf("Client socket closed.\n");

    return 0;
}
