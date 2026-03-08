#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <openssl/des.h>
#include <vector>

#define PORT 8080
using namespace std;

std::vector<unsigned char> encrypt_des(const std::string& plaintext, const std::string& key) {
    DES_cblock des_key;
    DES_key_schedule schedule;
    
    // Prepare key: strictly copy bytes and fix parity
    memset(des_key, 0, 8);
    memcpy(des_key, key.c_str(), (key.length() > 8 ? 8 : key.length()));
    DES_set_odd_parity(&des_key); // FIX: Ensures key is valid for DES
    DES_set_key_checked(&des_key, &schedule);

    // PKCS5 padding
    std::string padded_text = plaintext;
    int padding = 8 - (plaintext.length() % 8);
    for (int i = 0; i < padding; ++i) {
        padded_text += (char)padding;
    }

    std::vector<unsigned char> ciphertext(padded_text.length());
    for (size_t i = 0; i < padded_text.length(); i += 8) {
        DES_ecb_encrypt((DES_cblock*)(padded_text.c_str() + i), (DES_cblock*)(ciphertext.data() + i), &schedule, DES_ENCRYPT);
    }
    return ciphertext;
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr);

    if (connect(sock, (sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("Connection failed");
        return 1;
    }

    string msg, key;
    cout << "Enter message: ";
    getline(cin, msg);
    cout << "Enter 8-byte key: ";
    cin >> key;

    std::vector<unsigned char> encrypted = encrypt_des(msg, key);
    send(sock, encrypted.data(), encrypted.size(), 0);
    cout << "Encrypted message sent successfully!\n";

    close(sock);
    return 0;
}