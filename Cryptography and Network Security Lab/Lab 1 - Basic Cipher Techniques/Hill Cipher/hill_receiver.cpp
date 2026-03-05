#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <string>

#define PORT 8080

// Function to find modular inverse of a under modulo m
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // Inverse does not exist
}

// Function to get the key matrix from the user
void getKeyMatrix(std::vector<std::vector<int>>& keyMatrix) {
    std::cout << "Enter the 2x2 key matrix used for encryption:" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cin >> keyMatrix[i][j];
        }
    }
    std::cin.ignore(); // Consume the newline character
}

// Function to decrypt the message using Hill Cipher
std::string decrypt(std::string message, std::vector<std::vector<int>>& keyMatrix) {
    std::string decryptedText = "";
    std::vector<std::vector<int>> invKeyMatrix(2, std::vector<int>(2));

    // Calculate determinant
    int det = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    det = (det % 26 + 26) % 26;

    // Find modular inverse of determinant
    int det_inv = modInverse(det, 26);
    if (det_inv == -1) {
        return "Decryption failed: Key matrix is not invertible.";
    }

    // Calculate inverse key matrix
    invKeyMatrix[0][0] = (keyMatrix[1][1] * det_inv) % 26;
    invKeyMatrix[0][1] = (-keyMatrix[0][1] * det_inv) % 26;
    invKeyMatrix[1][0] = (-keyMatrix[1][0] * det_inv) % 26;
    invKeyMatrix[1][1] = (keyMatrix[0][0] * det_inv) % 26;

    // Adjust for negative values
    for(int i=0; i<2; ++i) {
        for(int j=0; j<2; ++j) {
            if (invKeyMatrix[i][j] < 0) {
                invKeyMatrix[i][j] += 26;
            }
        }
    }

    // Perform decryption
    for (size_t i = 0; i < message.length(); i += 2) {
        int c1 = message[i] - 'A';
        int c2 = message[i + 1] - 'A';

        int p1 = (invKeyMatrix[0][0] * c1 + invKeyMatrix[0][1] * c2) % 26;
        int p2 = (invKeyMatrix[1][0] * c1 + invKeyMatrix[1][1] * c2) % 26;

        decryptedText += (char)(p1 + 'A');
        decryptedText += (char)(p2 + 'A');
    }

    return decryptedText;
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

        std::vector<std::vector<int>> keyMatrix(2, std::vector<int>(2));
        getKeyMatrix(keyMatrix);

        std::string decryptedMessage = decrypt(encryptedMessage, keyMatrix);
        std::cout << "Decrypted message: " << decryptedMessage << std::endl;

        send(new_socket, response, strlen(response), 0);
        std::cout << "Response sent";
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
