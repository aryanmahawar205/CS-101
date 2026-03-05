#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

void decrypt(std::string& message, int shift) {
    for (char& c : message) {
        if (c >= 'a' && c <= 'z') {
            c = ((c - 'a' - shift + 26) % 26) + 'a';
        } else if (c >= 'A' && c <= 'Z') {
            c = ((c - 'A' - shift + 26) % 26) + 'A';
        }
    }
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};
    const char* response = "Message received and decrypted";

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
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
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("Accept");
        exit(EXIT_FAILURE);
    }

    ssize_t valread = read(new_socket, buffer, sizeof(buffer) - 1);
    if (valread > 0) {
        buffer[valread] = '\0';
        std::string encryptedMessage(buffer);

        std::cout << "Encrypted message received: " << encryptedMessage << std::endl;

        int shift;
        std::cout << "Enter the shift value to decrypt: ";
        std::cin >> shift;
        std::cin.ignore(); // consume the newline character

        decrypt(encryptedMessage, shift);
        std::cout << "Decrypted message: " << encryptedMessage << std::endl;

        send(new_socket, response, strlen(response), 0);
        std::cout << "Response sent\n";
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
