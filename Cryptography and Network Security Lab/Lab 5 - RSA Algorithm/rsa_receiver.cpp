#include <iostream>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cmath>

using namespace std;

#define PORT 8080

// Greatest Common Divisor
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

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

// Extended Euclidean Algorithm to find Modular Inverse
long long modInverse(long long e, long long phi) {
    long long t = 0, newt = 1;
    long long r = phi, newr = e;
    
    while (newr != 0) {
        long long quotient = r / newr;
        long long temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    
    if (r > 1) return -1; // e is not invertible
    if (t < 0) t = t + phi;
    return t;
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

    // RSA Key Generation
    long long p, q;
    cout << "Enter two prime numbers (p and q) such that p*q > 255: ";
    cin >> p >> q;

    if (!isPrime(p) || !isPrime(q)) {
        cout << "Both numbers must be prime!" << endl;
        close(new_socket);
        close(server_fd);
        return 1;
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);
    
    if (n < 255) {
        cout << "Warning: n (p*q) is less than 255. ASCII characters might not be encrypted correctly." << endl;
    }

    // Choose e such that 1 < e < phi and gcd(e, phi) = 1
    long long e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1) break;
        e++;
    }

    long long d = modInverse(e, phi);

    cout << "Public Key: (e: " << e << ", n: " << n << ")" << endl;
    cout << "Private Key: (d: " << d << ", n: " << n << ")" << endl;

    // Send Public Key to Client
    send(new_socket, &e, sizeof(e), 0);
    send(new_socket, &n, sizeof(n), 0);
    cout << "Sent Public Key to Sender." << endl;

    // Receive Encrypted Message
    // We expect a sequence of long long values. 
    // Since we don't know the length, we can read until the connection is closed or a specific sentinel.
    // For simplicity, let's just read in a loop.
    
    cout << "Waiting for encrypted message..." << endl;
    
    long long encrypted_char;
    string decrypted_message = "";
    int valread;
    
    while ((valread = read(new_socket, &encrypted_char, sizeof(encrypted_char))) > 0) {
        // Decrypt: m = (c^d) % n
        long long decrypted_char_code = power(encrypted_char, d, n);
        decrypted_message += (char)decrypted_char_code;
    }
    
    cout << "Decrypted Message: " << decrypted_message << endl;

    close(new_socket);
    close(server_fd);
    
    return 0;
}
