#include <arpa/inet.h>
#include <algorithm>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

const int PORT = 5000;
const int BUFFER_SIZE = 1024;

int main() {
    int serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

    if (serverSocket < 0) {
        std::cerr << "Socket creation failed.\n";
        return 1;
    }

    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    if (bind(serverSocket, reinterpret_cast<sockaddr*>(&serverAddress),
             sizeof(serverAddress)) < 0) {
        std::cerr << "Binding failed.\n";
        close(serverSocket);
        return 1;
    }

    std::cout << "UDP server is running on port " << PORT << "...\n";

    char buffer[BUFFER_SIZE];
    sockaddr_in clientAddress{};
    socklen_t clientLength = sizeof(clientAddress);

    int bytesReceived = recvfrom(
        serverSocket, buffer, BUFFER_SIZE - 1, 0,
        reinterpret_cast<sockaddr*>(&clientAddress), &clientLength);

    if (bytesReceived < 0) {
        std::cerr << "Message receiving failed.\n";
        close(serverSocket);
        return 1;
    }

    buffer[bytesReceived] = '\0';
    std::string message(buffer);

    std::cout << "Received string: " << message << '\n';

    std::reverse(message.begin(), message.end());

    sendto(serverSocket, message.c_str(), message.length(), 0,
           reinterpret_cast<sockaddr*>(&clientAddress), clientLength);

    std::cout << "Reversed string sent: " << message << '\n';

    close(serverSocket);
    return 0;
}
