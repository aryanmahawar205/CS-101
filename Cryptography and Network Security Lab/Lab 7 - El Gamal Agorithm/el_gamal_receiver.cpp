#include <iostream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cmath>

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

bool isPrime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; i++) {
        if (n % i == 0) return false;
    }
    return true;
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

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

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    cout << "Waiting for connection..." << endl;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    
    cout << "Connection established!" << endl;

    // El Gamal Key Generation
    long long p, g, x;
    cout << "Enter a large prime number (p) such that p > 255: ";
    cin >> p;
    if (!isPrime(p)) {
        cout << "Error: p must be prime!" << endl;
        close(new_socket);
        close(server_fd);
        return 1;
    }

    cout << "Enter a generator (g) for Zp*: ";
    cin >> g;
    cout << "Enter private key (x) such that 1 < x < p-1: ";
    cin >> x;

    long long y = power(g, x, p);

    cout << "Public Key: (p: " << p << ", g: " << g << ", y: " << y << ")" << endl;
    cout << "Private Key: (x: " << x << ")" << endl;

    // Send Public Key to Client
    send(new_socket, &p, sizeof(p), 0);
    send(new_socket, &g, sizeof(g), 0);
    send(new_socket, &y, sizeof(y), 0);
    cout << "Sent Public Key to Sender." << endl;

    // Receive Encrypted Message
    // In El Gamal, each character is a pair (a, b)
    cout << "Waiting for encrypted message..." << endl;
    
    long long a, b;
    string decrypted_message = "";
    int valread;
    
    while ((valread = read(new_socket, &a, sizeof(a))) > 0) {
        read(new_socket, &b, sizeof(b));
        
        // Decryption: M = (b * a^(p-1-x)) % p
        long long a_inv_x = power(a, p - 1 - x, p);
        long long decrypted_char_code = (b * a_inv_x) % p;
        decrypted_message += (char)decrypted_char_code;
    }
    
    cout << "Decrypted Message: " << decrypted_message << endl;

    close(new_socket);
    close(server_fd);
    
    return 0;
}
