#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iomanip>
#include <sstream>

using namespace std;

#define PORT 8081

// MD5 implementation
class MD5 {
public:
    typedef unsigned int size_type; 

    MD5();
    MD5(const std::string& text);
    void update(const unsigned char *buf, size_type length);
    void update(const char *buf, size_type length);
    MD5& finalize();
    std::string hexdigest() const;

private:
    void init();
    typedef unsigned char uint1; //  8bit
    typedef unsigned int uint4;  // 32bit

    void transform(const uint1 block[64]);
    static void decode(uint4 output[], const uint1 input[], size_type len);
    static void encode(uint1 output[], const uint4 input[], size_type len);

    bool finalized;
    uint1 buffer[64]; 
    uint4 count[2];   
    uint4 state[4];   
    uint1 digest[16]; 

    static inline uint4 F(uint4 x, uint4 y, uint4 z);
    static inline uint4 G(uint4 x, uint4 y, uint4 z);
    static inline uint4 H(uint4 x, uint4 y, uint4 z);
    static inline uint4 I(uint4 x, uint4 y, uint4 z);
    static inline uint4 rotate_left(uint4 x, int n);
    static inline void FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
    static inline void II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac);
};

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

inline MD5::uint4 MD5::F(uint4 x, uint4 y, uint4 z) { return (x & y) | (~x & z); }
inline MD5::uint4 MD5::G(uint4 x, uint4 y, uint4 z) { return (x & z) | (y & ~z); }
inline MD5::uint4 MD5::H(uint4 x, uint4 y, uint4 z) { return x ^ y ^ z; }
inline MD5::uint4 MD5::I(uint4 x, uint4 y, uint4 z) { return y ^ (x | ~z); }
inline MD5::uint4 MD5::rotate_left(uint4 x, int n) { return (x << n) | (x >> (32-n)); }
inline void MD5::FF(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a = rotate_left(a + F(b,c,d) + x + ac, s) + b;
}
inline void MD5::GG(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a = rotate_left(a + G(b,c,d) + x + ac, s) + b;
}
inline void MD5::HH(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a = rotate_left(a + H(b,c,d) + x + ac, s) + b;
}
inline void MD5::II(uint4 &a, uint4 b, uint4 c, uint4 d, uint4 x, uint4 s, uint4 ac) {
    a = rotate_left(a + I(b,c,d) + x + ac, s) + b;
}

MD5::MD5() { init(); }
MD5::MD5(const std::string &text) {
    init();
    update(text.c_str(), text.length());
    finalize();
}

void MD5::init() {
    finalized = false;
    count[0] = 0;
    count[1] = 0;
    state[0] = 0x67452301;
    state[1] = 0xefcdab89;
    state[2] = 0x98badcfe;
    state[3] = 0x10325476;
}

void MD5::decode(uint4 output[], const uint1 input[], size_type len) {
    for (unsigned int i = 0, j = 0; j < len; i++, j += 4)
        output[i] = ((uint4)input[j]) | (((uint4)input[j+1]) << 8) |
                    (((uint4)input[j+2]) << 16) | (((uint4)input[j+3]) << 24);
}

void MD5::encode(uint1 output[], const uint4 input[], size_type len) {
    for (size_type i = 0, j = 0; j < len; i++, j += 4) {
        output[j] = input[i] & 0xff;
        output[j+1] = (input[i] >> 8) & 0xff;
        output[j+2] = (input[i] >> 16) & 0xff;
        output[j+3] = (input[i] >> 24) & 0xff;
    }
}

void MD5::update(const unsigned char *input, size_type length) {
    size_type i, index, partlen;
    index = (size_type)((count[0] >> 3) & 0x3F);
    if ((count[0] += ((uint4)length << 3)) < ((uint4)length << 3))
        count[1]++;
    count[1] += ((uint4)length >> 29);
    partlen = 64 - index;
    if (length >= partlen) {
        memcpy(&buffer[index], input, partlen);
        transform(buffer);
        for (i = partlen; i + 63 < length; i += 64)
            transform(&input[i]);
        index = 0;
    } else {
        i = 0;
    }
    memcpy(&buffer[index], &input[i], length - i);
}

void MD5::update(const char *input, size_type length) {
    update((const unsigned char*)input, length);
}

MD5& MD5::finalize() {
    static unsigned char padding[64] = {
        0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
    };
    if (!finalized) {
        uint1 bits[8];
        encode(bits, count, 8);
        size_type index = (size_type)((count[0] >> 3) & 0x3f);
        size_type padLen = (index < 56) ? (56 - index) : (120 - index);
        update(padding, padLen);
        update(bits, 8);
        encode(digest, state, 16);
        memset(buffer, 0, sizeof buffer);
        memset(count, 0, sizeof count);
        finalized = true;
    }
    return *this;
}

std::string MD5::hexdigest() const {
    if (!finalized) return "";
    ostringstream oss;
    for (int i = 0; i < 16; i++)
        oss << hex << setw(2) << setfill('0') << (int)digest[i];
    return oss.str();
}

void MD5::transform(const uint1 block[64]) {
    uint4 a = state[0], b = state[1], c = state[2], d = state[3], x[16];
    decode(x, block, 64);

    /* Round 1 */
    FF(a, b, c, d, x[ 0], S11, 0xd76aa478); FF(d, a, b, c, x[ 1], S12, 0xe8c7b756);
    FF(c, d, a, b, x[ 2], S13, 0x242070db); FF(b, c, d, a, x[ 3], S14, 0xc1bdceee);
    FF(a, b, c, d, x[ 4], S11, 0xf57c0faf); FF(d, a, b, c, x[ 5], S12, 0x4787c62a);
    FF(c, d, a, b, x[ 6], S13, 0xa8304613); FF(b, c, d, a, x[ 7], S14, 0xfd469501);
    FF(a, b, c, d, x[ 8], S11, 0x698098d8); FF(d, a, b, c, x[ 9], S12, 0x8b44f7af);
    FF(c, d, a, b, x[10], S13, 0xffff5bb1); FF(b, c, d, a, x[11], S14, 0x895cd7be);
    FF(a, b, c, d, x[12], S11, 0x6b901122); FF(d, a, b, c, x[13], S12, 0xfd987193);
    FF(c, d, a, b, x[14], S13, 0xa679438e); FF(b, c, d, a, x[15], S14, 0x49b40821);

    /* Round 2 */
    GG(a, b, c, d, x[ 1], S21, 0xf61e2562); GG(d, a, b, c, x[ 6], S22, 0xc040b340);
    GG(c, d, a, b, x[11], S23, 0x265e5a51); GG(b, c, d, a, x[ 0], S24, 0xe9b6c7aa);
    GG(a, b, c, d, x[ 5], S21, 0xd62f105d); GG(d, a, b, c, x[10], S22, 0x02441453);
    GG(c, d, a, b, x[15], S23, 0xd8a1e681); GG(b, c, d, a, x[ 4], S24, 0xe7d3fbc8);
    GG(a, b, c, d, x[ 9], S21, 0x21e1cde6); GG(d, a, b, c, x[14], S22, 0xc33707d6);
    GG(c, d, a, b, x[ 3], S23, 0xf4d50d87); GG(b, c, d, a, x[ 8], S24, 0x455a14ed);
    GG(a, b, c, d, x[13], S21, 0xa9e3e905); GG(d, a, b, c, x[ 2], S22, 0xfcefa3f8);
    GG(c, d, a, b, x[ 7], S23, 0x676f02d9); GG(b, c, d, a, x[12], S24, 0x8d2a4c8a);

    /* Round 3 */
    HH(a, b, c, d, x[ 5], S31, 0xff4477a1); HH(d, a, b, c, x[ 8], S32, 0x6ad7d2bb);
    HH(c, d, a, b, x[11], S33, 0xa4beea44); HH(b, c, d, a, x[14], S34, 0x4bdecfa9);
    HH(a, b, c, d, x[ 1], S31, 0xf6bb4b60); HH(d, a, b, c, x[ 4], S32, 0xbebfbc70);
    HH(c, d, a, b, x[ 7], S33, 0x289b7ec6); HH(b, c, d, a, x[10], S34, 0xeaa127fa);
    HH(a, b, c, d, x[13], S31, 0xd4ef3085); HH(d, a, b, c, x[ 0], S32, 0x04881d05);
    HH(c, d, a, b, x[ 3], S33, 0xd9d4d039); HH(b, c, d, a, x[ 6], S34, 0xe6db99e5);
    HH(a, b, c, d, x[ 9], S31, 0x1fa27cf8); HH(d, a, b, c, x[12], S32, 0xc4ac5665);
    HH(c, d, a, b, x[15], S33, 0xf4292244); HH(b, c, d, a, x[ 2], S34, 0x432aff97);

    /* Round 4 */
    II(a, b, c, d, x[ 0], S41, 0xf4292244); II(d, a, b, c, x[ 7], S42, 0x432aff97);
    II(c, d, a, b, x[14], S43, 0xab9423a7); II(b, c, d, a, x[ 5], S44, 0xfc93a039);
    II(a, b, c, d, x[12], S41, 0x655b59c3); II(d, a, b, c, x[ 3], S42, 0x8f0ccc92);
    II(c, d, a, b, x[10], S43, 0xffeff47d); II(b, c, d, a, x[ 1], S44, 0x85845dd1);
    II(a, b, c, d, x[ 8], S41, 0x6fa87e4f); II(d, a, b, c, x[15], S42, 0xfe2ce6e0);
    II(c, d, a, b, x[ 6], S43, 0xa3014314); II(b, c, d, a, x[13], S44, 0x4e0811a1);
    II(a, b, c, d, x[ 4], S41, 0xf7537e82); II(d, a, b, c, x[11], S42, 0xbd3af235);
    II(c, d, a, b, x[ 2], S43, 0x2ad7d2bb); II(b, c, d, a, x[ 9], S44, 0xeb86d391);

    state[0] += a;
    state[1] += b;
    state[2] += c;
    state[3] += d;
    memset(x, 0, sizeof x);
}

string md5(string str) {
    MD5 md5 = MD5(str);
    return md5.hexdigest();
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
    
    string hash = md5(message);
    cout << "Computed MD5 Hash: " << hash << endl;
    
    // Send message length first
    int msg_len = message.length();
    send(sock, &msg_len, sizeof(msg_len), 0);
    
    // Send message
    send(sock, message.c_str(), msg_len, 0);
    
    // Send hash
    send(sock, hash.c_str(), hash.length(), 0);
    
    cout << "Message and Hash sent to receiver." << endl;
    
    close(sock);
    return 0;
}
