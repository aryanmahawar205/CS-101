#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

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

    cout << "--- DSS Receiver (Verification) ---" << endl;
    cout << "Waiting for connection..." << endl;
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    cout << "Connection established!" << endl;

    // Receive message
    int msg_len;
    read(new_socket, &msg_len, sizeof(msg_len));
    char buffer[1024] = {0};
    read(new_socket, buffer, msg_len);
    string received_message(buffer);

    // Receive Public Key and Signature
    long long y, r, s;
    read(new_socket, &y, sizeof(y));
    read(new_socket, &r, sizeof(r));
    read(new_socket, &s, sizeof(s));

    cout << "Received Message: " << received_message << endl;
    cout << "Received Public Key (y): " << y << endl;
    cout << "Received Signature (r, s): (" << r << ", " << s << ")" << endl;

    // Verification Process
    long long p = 607, q = 101, g = 122; // Agreed parameters
    
    long long h_m = simple_hash(received_message, q);
    long long w = modInverse(s, q);
    long long u1 = (h_m * w) % q;
    long long u2 = (r * w) % q;
    
    long long g_u1 = power(g, u1, p);
    long long y_u2 = power(y, u2, p);
    long long v = ((g_u1 * y_u2) % p) % q;

    cout << "Verification Step:" << endl;
    cout << "  Hash of Received Message: " << h_m << endl;
    cout << "  w (s^-1 mod q): " << w << endl;
    cout << "  u1 (H(m)*w mod q): " << u1 << endl;
    cout << "  u2 (r*w mod q): " << u2 << endl;
    cout << "  v (((g^u1 * y^u2) mod p) mod q): " << v << endl;

    if (v == r) {
        cout << "Signature Verification: SUCCESS (v == r)" << endl;
    } else {
        cout << "Signature Verification: FAILED (v != r)" << endl;
    }

    close(new_socket);
    close(server_fd);

    return 0;
}
