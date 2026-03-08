#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

void encrypt(std::string& message, int shift) {
    for (char& c : message) {
        if (c >= 'a' && c <= 'z') {
            c = ((c - 'a' + shift) % 26) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            c = ((c - 'A' + shift) % 26) + 'A';
        }
    }
}

int main() {
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported\n";
        return -1;
    }

    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed\n";
        return -1;
    }

    std::string message;
    int shift;
    std::cout << "Enter the message: ";
    std::getline(std::cin, message);
    std::cout << "Enter the shift value: ";
    std::cin >> shift;
    std::cin.ignore(); // consume the newline character from the buffer

    encrypt(message, shift);
    send(client_fd, message.c_str(), message.size(), 0);
    std::cout << "Encrypted message sent: " << message << std::endl;

    ssize_t valread = read(client_fd, buffer, sizeof(buffer) - 1);
    if (valread > 0) {
        buffer[valread] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
    }

    close(client_fd);
    return 0;
}
