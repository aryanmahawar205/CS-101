#include <netinet/in.h>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <unistd.h>
#include <cctype>

#define PORT 8080

// Function to decrypt a message using Vigenere cipher
std::string vigenere_decrypt(const std::string& ciphertext, const std::string& key) {
    std::string decrypted_message = "";
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        char cipher_char = ciphertext[i];
        char key_char = key[i % key.length()];

        if (isalpha(cipher_char)) {
            char base = isupper(cipher_char) ? 'A' : 'a';
            cipher_char = (cipher_char - base - (toupper(key_char) - 'A') + 26) % 26 + base;
        }
        decrypted_message += cipher_char;
    }
    return decrypted_message;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    ssize_t valread = read(new_socket, buffer, 1024);
    std::string received_message(buffer, valread);
    std::cout << "Encrypted message received." << std::endl;

    std::string key;
    std::cout << "Enter the keyword to decrypt: ";
    std::getline(std::cin, key);

    std::string decrypted_message = vigenere_decrypt(received_message, key);
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    close(new_socket);
    close(server_fd);
    return 0;
}