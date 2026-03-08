#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define PORT 8081

long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    long long p = 997, g = 2;
    long long b = 25; // Bob's private key
    long long B = power(g, b, p);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 3);
    
    cout << "Bob waiting for Alice..." << endl;
    new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);

    // Receive public value from "Alice"
    long long received_val;
    read(new_socket, &received_val, sizeof(received_val));
    
    // Send B to "Alice"
    send(new_socket, &B, sizeof(B), 0);

    long long secret_key = power(received_val, b, p);
    cout << "Bob's Shared Key: " << secret_key << endl;

    // Receive message
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    string msg(buffer, valread);
    
    cout << "Received (Encrypted): " << msg << endl;
    for(char &c : msg) c ^= (char)secret_key; // XOR Decryption
    cout << "Decrypted message at Bob: " << msg << endl;

    close(new_socket);
    close(server_fd);
    return 0;
}
