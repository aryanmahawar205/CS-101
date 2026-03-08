#include <netinet/in.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <openssl/des.h>
#include <vector>
#include <string>

#define PORT 8080
using namespace std;

std::string decrypt_des(const std::vector<unsigned char>& ciphertext, const std::string& key) {
    if (ciphertext.empty()) return "Error: No data";

    DES_cblock des_key;
    DES_key_schedule schedule;
    
    // Prepare key: strictly copy bytes and fix parity
    memset(des_key, 0, 8);
    memcpy(des_key, key.c_str(), (key.length() > 8 ? 8 : key.length()));
    DES_set_odd_parity(&des_key); // FIX: Must match sender's parity logic
    DES_set_key_checked(&des_key, &schedule);
    
    std::vector<unsigned char> decrypted_padded(ciphertext.size());
    for (size_t i = 0; i < ciphertext.size(); i += 8) {
        DES_ecb_encrypt((DES_cblock*)(ciphertext.data() + i), (DES_cblock*)(decrypted_padded.data() + i), &schedule, DES_DECRYPT);
    }

    // PKCS5 padding removal
    if (decrypted_padded.empty()) return "Error: Decryption resulted in empty data";
    int padding = (int)decrypted_padded.back();

    // Check if padding value is realistic (1 to 8)
    if (padding < 1 || padding > 8 || padding > decrypted_padded.size()) {
        return "Error: Decryption failed (Wrong key or corrupted data)";
    }

    return std::string(decrypted_padded.begin(), decrypted_padded.end() - padding);
}

int main() {
    int server = socket(AF_INET, SOCK_STREAM, 0);
    int opt = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)); // Allow immediate restart

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(server, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("Bind failed");
        return 1;
    }
    listen(server, 3);

    cout << "Waiting for sender to connect...\n";
    int client = accept(server, nullptr, nullptr);
    
    std::vector<unsigned char> buffer(1024);
    int bytes_received = recv(client, buffer.data(), buffer.size(), 0);
    
    if (bytes_received <= 0) {
        cout << "No data received.\n";
    } else {
        buffer.resize(bytes_received);
        string key;
        cout << "Message received! Enter 8-byte key to decrypt: ";
        cin >> key;

        string decrypted = decrypt_des(buffer, key);
        cout << "Decrypted message: " << decrypted << endl;
    }

    close(client);
    close(server);
    return 0;
}