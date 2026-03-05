#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <string>

#define PORT 8080

// Function to get the key matrix from the user
void getKeyMatrix(std::vector<std::vector<int>>& keyMatrix) {
    std::cout << "Enter the 2x2 key matrix (4 integers):" << std::endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            std::cin >> keyMatrix[i][j];
        }
    }
    std::cin.ignore(); // Consume the newline character
}

// Function to encrypt the message using Hill Cipher
std::string encrypt(std::string message, std::vector<std::vector<int>>& keyMatrix) {
    std::string encryptedText = "";
    std::string processedMessage = "";

    // Process message: uppercase and letters only
    for (char& c : message) {
        if (isalpha(c)) {
            processedMessage += toupper(c);
        }
    }

    // Pad the message with 'X' if its length is odd
    if (processedMessage.length() % 2 != 0) {
        processedMessage += 'X';
    }

    // Perform encryption
    for (size_t i = 0; i < processedMessage.length(); i += 2) {
        int p1 = processedMessage[i] - 'A';
        int p2 = processedMessage[i + 1] - 'A';

        int c1 = (keyMatrix[0][0] * p1 + keyMatrix[0][1] * p2) % 26;
        int c2 = (keyMatrix[1][0] * p1 + keyMatrix[1][1] * p2) % 26;

        encryptedText += (char)(c1 + 'A');
        encryptedText += (char)(c2 + 'A');
    }

    return encryptedText;
}

int main() {
    int client_fd;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Socket creation error";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "Invalid address / Address not supported";
        return -1;
    }

    if (connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Connection Failed";
        return -1;
    }

    std::string message;
    std::vector<std::vector<int>> keyMatrix(2, std::vector<int>(2));

    std::cout << "Enter the message: ";
    std::getline(std::cin, message);

    getKeyMatrix(keyMatrix);

    // Basic validation for the key matrix determinant
    int det = keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0];
    det = (det % 26 + 26) % 26;
    if (det == 0 || det % 2 == 0 || det % 13 == 0) {
        std::cerr << "The key matrix is not invertible. Please use a valid key." << std::endl;
        close(client_fd);
        return -1;
    }


    std::string encryptedMessage = encrypt(message, keyMatrix);
    send(client_fd, encryptedMessage.c_str(), encryptedMessage.size(), 0);
    std::cout << "Encrypted message sent: " << encryptedMessage << std::endl;

    ssize_t valread = read(client_fd, buffer, sizeof(buffer) - 1);
    if (valread > 0) {
        buffer[valread] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
    }

    close(client_fd);
    return 0;
}
