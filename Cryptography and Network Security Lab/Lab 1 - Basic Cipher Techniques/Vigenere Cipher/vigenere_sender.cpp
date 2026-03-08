#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

// Function to encrypt a message using Vigenere cipher
std::string vigenere_encrypt(const std::string& message, const std::string& key) {
    std::string encrypted_message = "";
    for (size_t i = 0; i < message.length(); ++i) {
        char msg_char = message[i];
        char key_char = key[i % key.length()];
        
        if (isalpha(msg_char)) {
            char base = isupper(msg_char) ? 'A' : 'a';
            msg_char = (msg_char - base + (toupper(key_char) - 'A')) % 26 + base;
        }
        encrypted_message += msg_char;
    }
    return encrypted_message;
}

int main() {
    int client_fd;
    struct sockaddr_in serv_addr;

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

    std::string message, key;
    std::cout << "Enter the message: ";
    std::getline(std::cin, message);
    std::cout << "Enter the keyword: ";
    std::getline(std::cin, key);

    std::string encrypted_message = vigenere_encrypt(message, key);
    send(client_fd, encrypted_message.c_str(), encrypted_message.length(), 0);
    std::cout << "Encrypted message sent." << std::endl;

    close(client_fd);
    return 0;
}