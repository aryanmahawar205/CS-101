#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

#define ALICE_PORT 8080
#define BOB_PORT 8081

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
    int server_fd, alice_sock, bob_sock;
    struct sockaddr_in m_addr, b_addr;
    int addrlen = sizeof(m_addr);
    long long p = 997, g = 2;
    
    // Mallory's private keys for two different sessions
    long long m1 = 10, m2 = 20; 
    long long M1 = power(g, m1, p); // Mallory's public value for Alice
    long long M2 = power(g, m2, p); // Mallory's public value for Bob

    // 1. Setup server to intercept Alice
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    m_addr.sin_family = AF_INET;
    m_addr.sin_addr.s_addr = INADDR_ANY;
    m_addr.sin_port = htons(ALICE_PORT);
    bind(server_fd, (struct sockaddr *)&m_addr, sizeof(m_addr));
    listen(server_fd, 3);
    
    cout << "Mallory (MITM) listening for Alice on 8080..." << endl;
    alice_sock = accept(server_fd, (struct sockaddr *)&m_addr, (socklen_t*)&addrlen);
    cout << "Alice connected!" << endl;

    // 2. Setup client to connect to Bob
    bob_sock = socket(AF_INET, SOCK_STREAM, 0);
    b_addr.sin_family = AF_INET;
    b_addr.sin_port = htons(BOB_PORT);
    inet_pton(AF_INET, "127.0.0.1", &b_addr.sin_addr);
    
    if (connect(bob_sock, (struct sockaddr *)&b_addr, sizeof(b_addr)) < 0) {
        cout << "Could not connect to Bob." << endl;
        return -1;
    }
    cout << "Connected to Bob on 8081!" << endl;

    // --- Key Exchange Phase ---
    long long A, B;
    
    // Receive A from Alice, send M2 to Bob
    read(alice_sock, &A, sizeof(A));
    send(bob_sock, &M2, sizeof(M2), 0);
    
    // Receive B from Bob, send M1 to Alice
    read(bob_sock, &B, sizeof(B));
    send(alice_sock, &M1, sizeof(M1), 0);

    // Mallory computes two keys
    long long K_Alice = power(A, m1, p);
    long long K_Bob = power(B, m2, p);

    cout << "Mallory's Key with Alice: " << K_Alice << endl;
    cout << "Mallory's Key with Bob: " << K_Bob << endl;

    // --- Message Interception Phase ---
    char buffer[1024] = {0};
    int len = read(alice_sock, buffer, 1024);
    string msg(buffer, len);
    
    cout << endl << "Intercepted Encrypted Message from Alice: " << msg << endl;
    
    // Mallory decrypts message from Alice
    for(char &c : msg) c ^= (char)K_Alice;
    cout << "Mallory decrypted it: " << msg << endl;
    
    // Mallory modifies message (Optional)
    msg = msg + " - [Mallory was here]";
    
    // Mallory re-encrypts for Bob
    for(char &c : msg) c ^= (char)K_Bob;
    cout << "Sending re-encrypted message to Bob..." << endl;
    send(bob_sock, msg.c_str(), msg.length(), 0);

    close(alice_sock);
    close(bob_sock);
    close(server_fd);
    return 0;
}
