#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>
#include <cstdint>

using namespace std;

#define PORT 8082

class SHA512 {
public:
    SHA512() {
        init();
    }

    void update(const string& message) {
        vector<uint8_t> data(message.begin(), message.end());
        update(data.data(), data.size());
    }

    void update(const uint8_t* data, size_t length) {
        size_t i = 0;
        while (i < length) {
            buffer[buffer_len++] = data[i++];
            if (buffer_len == 128) {
                transform(buffer);
                bit_len += 1024;
                buffer_len = 0;
            }
        }
    }

    string finalize() {
        uint64_t total_bits = bit_len + (buffer_len * 8);
        buffer[buffer_len++] = 0x80;

        if (buffer_len > 112) {
            while (buffer_len < 128) buffer[buffer_len++] = 0x00;
            transform(buffer);
            buffer_len = 0;
        }

        while (buffer_len < 120) buffer[buffer_len++] = 0x00;

        // Append total_bits as 128-bit big-endian (SHA-512 uses 128-bit length field)
        // For simplicity, we only use the lower 64 bits of the 128-bit length field
        for (int i = 0; i < 8; ++i) buffer[buffer_len++] = 0x00; 
        for (int i = 7; i >= 0; --i) buffer[buffer_len++] = (total_bits >> (i * 8)) & 0xFF;

        transform(buffer);

        stringstream ss;
        for (int i = 0; i < 8; ++i) {
            ss << hex << setw(16) << setfill('0') << state[i];
        }
        return ss.str();
    }

private:
    uint64_t state[8];
    uint64_t bit_len;
    uint8_t buffer[128];
    size_t buffer_len;

    static const uint64_t K[80];

    void init() {
        state[0] = 0x6a09e667f3bcc908;
        state[1] = 0xbb67ae8584caa73b;
        state[2] = 0x3c6ef372fe94f82b;
        state[3] = 0xa54ff53a5f1d36f1;
        state[4] = 0x510e527fade682d1;
        state[5] = 0x9b05688c2b3e6c1f;
        state[6] = 0x1f83d9abfb41bd6b;
        state[7] = 0x5be0cd19137e2179;
        bit_len = 0;
        buffer_len = 0;
    }

    uint64_t rotr(uint64_t x, uint32_t n) {
        return (x >> n) | (x << (64 - n));
    }

    void transform(const uint8_t* block) {
        uint64_t w[80];
        for (int i = 0; i < 16; ++i) {
            w[i] = 0;
            for (int j = 0; j < 8; ++j) {
                w[i] = (w[i] << 8) | block[i * 8 + j];
            }
        }

        for (int i = 16; i < 80; ++i) {
            uint64_t s0 = rotr(w[i-15], 1) ^ rotr(w[i-15], 8) ^ (w[i-15] >> 7);
            uint64_t s1 = rotr(w[i-2], 19) ^ rotr(w[i-2], 61) ^ (w[i-2] >> 6);
            w[i] = w[i-16] + s0 + w[i-7] + s1;
        }

        uint64_t a = state[0], b = state[1], c = state[2], d = state[3];
        uint64_t e = state[4], f = state[5], g = state[6], h = state[7];

        for (int i = 0; i < 80; ++i) {
            uint64_t S1 = rotr(e, 14) ^ rotr(e, 18) ^ rotr(e, 41);
            uint64_t ch = (e & f) ^ (~e & g);
            uint64_t temp1 = h + S1 + ch + K[i] + w[i];
            uint64_t S0 = rotr(a, 28) ^ rotr(a, 34) ^ rotr(a, 39);
            uint64_t maj = (a & b) ^ (a & c) ^ (b & c);
            uint64_t temp2 = S0 + maj;

            h = g; g = f; f = e; e = d + temp1;
            d = c; c = b; b = a; a = temp1 + temp2;
        }

        state[0] += a; state[1] += b; state[2] += c; state[3] += d;
        state[4] += e; state[5] += f; state[6] += g; state[7] += h;
    }
};

const uint64_t SHA512::K[80] = {
    0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
    0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
    0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
    0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
    0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
    0x2de92c6f592b0275, 0x4a7484aaed5d5120, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
    0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
    0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
    0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
    0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
    0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
    0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
    0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
    0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
    0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
    0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
    0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
    0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
    0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
    0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

string sha512(string str) {
    SHA512 sha;
    sha.update(str);
    return sha.finalize();
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
    
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cout << "\nInvalid address/ Address not supported \n";
        return -1;
    }
    
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "\nConnection Failed \n";
        return -1;
    }
    
    string message;
    cout << "Enter message to send: ";
    getline(cin, message);
    
    string hash = sha512(message);
    cout << "Computed SHA-512 Hash: " << hash << endl;
    
    // Send message length first
    int msg_len = message.length();
    send(sock, &msg_len, sizeof(msg_len), 0);
    
    // Send message
    send(sock, message.c_str(), msg_len, 0);
    
    // Send hash (SHA-512 hash is 128 characters long in hex)
    int hash_len = hash.length();
    send(sock, &hash_len, sizeof(hash_len), 0);
    send(sock, hash.c_str(), hash_len, 0);
    
    cout << "Message and Hash sent to receiver." << endl;
    
    close(sock);
    return 0;
}
