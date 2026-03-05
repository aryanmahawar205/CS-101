#include <netinet/in.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
using namespace std;

// Decrypt using Simple Columnar Transposition
string transposition_decrypt(string cipher, int key) {
    int len = cipher.length();
    int rows = (len + key - 1) / key;

    vector<vector<char>> matrix(rows, vector<char>(key));
    int k = 0;

    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            if (k < len)
                matrix[i][j] = cipher[k++];
        }
    }

    string plain;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key; j++) {
            plain += matrix[i][j];
        }
    }
    return plain;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    setsockopt(server_fd, SOL_SOCKET,
               SO_REUSEADDR | SO_REUSEPORT,
               &opt, sizeof(opt));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 3);

    new_socket = accept(server_fd,
                        (struct sockaddr*)&address, &addrlen);

    ssize_t valread = read(new_socket, buffer, 1024);
    string received_message(buffer, valread);

    cout << "Encrypted message received: "
         << received_message << endl;

    int key;
    cout << "Enter key (number of columns): ";
    cin >> key;

    string decrypted_message =
        transposition_decrypt(received_message, key);

    cout << "Decrypted message: " << decrypted_message << endl;

    close(new_socket);
    close(server_fd);
    return 0;
}