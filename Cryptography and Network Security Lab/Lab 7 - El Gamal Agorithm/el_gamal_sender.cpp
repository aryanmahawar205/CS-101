#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <ctime>

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
    
    // Receive Public Key (p, g, y)
    long long p, g, y;
    valread = read(sock, &p, sizeof(p));
    valread = read(sock, &g, sizeof(g));
    valread = read(sock, &y, sizeof(y));
    
    cout << "Received Public Key: (p: " << p << ", g: " << g << ", y: " << y << ")" << endl;
    
    string message;
    cout << "Enter message to encrypt: ";
    getline(cin, message);
    
    cout << "Encrypting message..." << endl;
    
    srand(time(0));
    for (char c : message) {
        long long m = (long long)c;
        
        // Encryption: a = g^k % p, b = (y^k * m) % p
        // Choose a random k such that 1 < k < p-1
        long long k = 2 + (rand() % (p - 3)); 
        
        long long a = power(g, k, p);
        long long b = (power(y, k, p) * m) % p;
        
        // Send a and b
        send(sock, &a, sizeof(a), 0);
        send(sock, &b, sizeof(b), 0);
    }
    
    cout << "Encrypted message sent." << endl;
    
    close(sock);
    return 0;
}
