#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cmath>
#include <cstring>

using namespace std;

#define PORT 8080 // Connecting to Mallory (thinks it's Bob)

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
    int sock = 0;
    struct sockaddr_in serv_addr;
    long long p = 997, g = 2;
    long long a = 15; // Alice's private key
    long long A = power(g, a, p); // Alice's public value

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) return -1;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) return -1;

    // Send A to "Bob"
    send(sock, &A, sizeof(A), 0);
    
    // Receive public value from "Bob"
    long long received_val;
    read(sock, &received_val, sizeof(received_val));
    
    long long secret_key = power(received_val, a, p);
    cout << "Alice's Shared Key: " << secret_key << endl;

    // Send encrypted message
    string msg = "Hello Bob!";
    cout << "Sending: " << msg << endl;
    for(char &c : msg) c ^= (char)secret_key; // XOR Encryption
    
    send(sock, msg.c_str(), msg.length(), 0);
    close(sock);
    return 0;
}
