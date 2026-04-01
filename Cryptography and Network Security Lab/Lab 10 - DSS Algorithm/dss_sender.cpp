#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cmath>

using namespace std;

#define PORT 8083

// Modular Exponentiation
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = (__int128)res * base % mod;
        base = (__int128)base * base % mod;
        exp /= 2;
    }
    return res;
}

// Modular Inverse using Extended Euclidean Algorithm
long long modInverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// Simple Hash Function for demonstration
long long simple_hash(string msg, long long q) {
    long long h = 0;
    for (char c : msg) {
        h = (h * 31 + c) % q;
    }
    return h;
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "\n Socket creation error \n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "\nConnection Failed \n";
        return -1;
    }

    // DSS Parameters (Pre-agreed or sent)
    // p = 607, q = 101, g = 122 (derived from h=3, g = 3^((p-1)/q) mod p)
    long long p = 607, q = 101, g = 122;
    long long x = 30; // Private Key
    long long y = power(g, x, p); // Public Key

    cout << "--- DSS Sender (Signing) ---" << endl;
    cout << "Public Parameters: p=" << p << ", q=" << q << ", g=" << g << endl;
    cout << "Private Key (x): " << x << endl;
    cout << "Public Key (y): " << y << endl;

    string message;
    cout << "Enter message to sign: ";
    getline(cin, message);

    // Signing Process
    long long h_m = simple_hash(message, q);
    long long k = 45; // Random per-message secret (should be 0 < k < q)
    
    long long r = power(g, k, p) % q;
    long long k_inv = modInverse(k, q);
    long long s = (k_inv * (h_m + x * r)) % q;

    cout << "Message Hash: " << h_m << endl;
    cout << "Signature (r, s): (" << r << ", " << s << ")" << endl;

    // Send data to receiver
    int msg_len = message.length();
    send(sock, &msg_len, sizeof(msg_len), 0);
    send(sock, message.c_str(), msg_len, 0);

    // Send Public Key and Signature
    send(sock, &y, sizeof(y), 0);
    send(sock, &r, sizeof(r), 0);
    send(sock, &s, sizeof(s), 0);

    cout << "Message, Public Key, and Signature sent." << endl;

    close(sock);
    return 0;
}
