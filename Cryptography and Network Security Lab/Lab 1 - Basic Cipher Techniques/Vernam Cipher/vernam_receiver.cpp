#include <netinet/in.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080

// Function to decrypt a message using Vernam cipher
std::string vernam_decrypt(const std::string& ciphertext, const std::string& key) {
    std::string plaintext = "";
    for (size_t i = 0; i < ciphertext.length(); ++i) {
        plaintext += ciphertext[i] ^ key[i];
    }
    return plaintext;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Forcefully attaching socket to the port 8080
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
    std::cout << "Enter the key to decrypt: ";
    std::getline(std::cin, key);

    std::string decrypted_message = vernam_decrypt(received_message, key);
    std::cout << "Decrypted message: " << decrypted_message << std::endl;

    close(new_socket);
    close(server_fd);
    return 0;
}
