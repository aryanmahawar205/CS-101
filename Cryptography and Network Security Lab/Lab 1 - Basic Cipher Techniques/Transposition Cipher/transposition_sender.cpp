#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
using namespace std;

// Encrypt using Simple Columnar Transposition
string transposition_encrypt(string text, int key) {
    int len = text.length();
    int rows = (len + key - 1) / key;

    vector<vector<char>> matrix(rows, vector<char>(key, 'X'));
    int k = 0;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < key && k < len; j++) {
            matrix[i][j] = text[k++];
        }
    }

    string cipher;
    for (int j = 0; j < key; j++) {
        for (int i = 0; i < rows; i++) {
            cipher += matrix[i][j];
        }
    }
    return cipher;
}

int main() {
    int client_fd;
    struct sockaddr_in serv_addr;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(client_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    string message;
    int key;

    cout << "Enter the message (no spaces): ";
    cin >> message;
    cout << "Enter key (number of columns): ";
    cin >> key;

    string encrypted_message = transposition_encrypt(message, key);

    send(client_fd, encrypted_message.c_str(),
         encrypted_message.length(), 0);

    cout << "Encrypted message sent: " << encrypted_message << endl;

    close(client_fd);
    return 0;
}