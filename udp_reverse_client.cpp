#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 5000;
const int BUFFER_SIZE = 1024;

int main() {
    int clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (clientSocket < 0) {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr);

    std::string message;

    std::cout << "Enter a string: ";
    std::getline(std::cin, message);

    sendto(clientSocket, message.c_str(), message.length(), 0,
           reinterpret_cast<sockaddr*>(&serverAddress),
           sizeof(serverAddress));

    char buffer[BUFFER_SIZE];
    sockaddr_in fromAddress{};
    socklen_t addressLength = sizeof(fromAddress);

    int bytesReceived = recvfrom(
        clientSocket, buffer, BUFFER_SIZE - 1, 0,
        reinterpret_cast<sockaddr*>(&fromAddress), &addressLength);

    if (bytesReceived < 0) {
        std::cerr << "Reply receiving failed.\n";
        close(clientSocket);
        return 1;
    }

    buffer[bytesReceived] = '\0';

    std::cout << "Reversed string received from server: "
              << buffer << '\n';

    close(clientSocket);
    return 0;
}
