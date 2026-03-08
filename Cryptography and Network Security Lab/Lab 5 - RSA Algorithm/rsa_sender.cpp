#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>

using namespace std;

#define PORT 8080

// Modular Exponentiation: (base^exp) % mod
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (res * base) % mod;
        base = (base * base) % mod;
        exp /= 2;
    }
    return res;
}

int main() {
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << endl << "Socket creation error" << endl;
        return -1;
    }
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cout << endl << "Invalid address/ Address not supported" << endl;
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << endl << "Connection Failed" << endl;
        return -1;
    }
    
    // Receive Public Key (e, n)
    long long e, n;
    valread = read(sock, &e, sizeof(e));
    valread = read(sock, &n, sizeof(n));
    
    cout << "Received Public Key: (e: " << e << ", n: " << n << ")" << endl;
    
    string message;
    cout << "Enter message to encrypt: ";
    getline(cin, message);
    
    cout << "Encrypting message..." << endl;
    
    for (char c : message) {
        long long m = (long long)c;
        // Encrypt: c = (m^e) % n
        long long encrypted_char = power(m, e, n);
        
        // Send encrypted character
        send(sock, &encrypted_char, sizeof(encrypted_char), 0);
    }
    
    cout << "Encrypted message sent." << endl;
    
    close(sock);
    return 0;
}
