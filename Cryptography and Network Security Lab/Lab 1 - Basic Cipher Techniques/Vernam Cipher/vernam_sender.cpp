#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

// Function to encrypt a message using Vernam cipher
std::string vernam_encrypt(const std::string& message, const std::string& key) {
    std::string ciphertext = "";
    for (size_t i = 0; i < message.length(); ++i) {
        ciphertext += message[i] ^ key[i];
    }
    return ciphertext;
}

int main() {
    int client_fd;
    struct sockaddr_in serv_addr;

    // Creating socket file descriptor
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported\n";
        return -1;
    }

    // Connect to the server
    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed\n";
        return -1;
    }

    std::string message;
    std::string key;

    std::cout << "Enter the message: ";
    std::getline(std::cin, message);

    do {
        std::cout << "Enter the key (must be same length as message): ";
        std::getline(std::cin, key);
        if (key.length() != message.length()) {
            std::cout << "Error: Key length must be equal to message length.\n";
        }
    } while (key.length() != message.length());


    std::string encrypted_message = vernam_encrypt(message, key);
    send(client_fd, encrypted_message.c_str(), encrypted_message.length(), 0);
    std::cout << "Encrypted message sent." << std::endl;

    close(client_fd);
    return 0;
}
