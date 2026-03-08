#include <arpa/inet.h>
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8080

using namespace std;

/* ---------- S-DES Tables ---------- */
int P10[] = {3,5,2,7,4,10,1,9,8,6};
int P8[]  = {6,3,7,4,8,5,10,9};
int IP[]  = {2,6,3,1,4,8,5,7};
int IP_INV[] = {4,1,3,5,7,2,8,6};
int EP[]  = {4,1,2,3,2,3,4,1};
int P4[]  = {2,4,3,1};

int S0[4][4] = {
    {1,0,3,2},
    {3,2,1,0},
    {0,2,1,3},
    {3,1,3,2}
};

int S1[4][4] = {
    {0,1,2,3},
    {2,0,1,3},
    {3,0,1,0},
    {2,1,0,3}
};

/* ---------- Utility Functions ---------- */
string permute(string k, int* arr, int n) {
    string out = "";
    for (int i = 0; i < n; i++)
        out += k[arr[i] - 1];
    return out;
}

string shift_left(string k, int shifts) {
    while (shifts--)
        k = k.substr(1) + k[0];
    return k;
}

string xor_str(string a, string b) {
    string out = "";
    for (int i = 0; i < a.length(); i++)
        out += (a[i] == b[i] ? '0' : '1');
    return out;
}

string sbox(string input, int box[4][4]) {
    int row = (input[0]-'0') * 2 + (input[3]-'0');
    int col = (input[1]-'0') * 2 + (input[2]-'0');
    int val = box[row][col];
    return string(1, (val/2)+'0') + string(1, (val%2)+'0');
}

/* ---------- Key Generation ---------- */
void generate_keys(string key, string &k1, string &k2) {
    string p10 = permute(key, P10, 10);
    string left = shift_left(p10.substr(0,5), 1);
    string right = shift_left(p10.substr(5,5), 1);
    k1 = permute(left + right, P8, 8);

    left = shift_left(left, 2);
    right = shift_left(right, 2);
    k2 = permute(left + right, P8, 8);
}

/* ---------- Encryption ---------- */
string fk(string bits, string key) {
    string left = bits.substr(0,4);
    string right = bits.substr(4,4);

    string ep = permute(right, EP, 8);
    string x = xor_str(ep, key);

    string s0 = sbox(x.substr(0,4), S0);
    string s1 = sbox(x.substr(4,4), S1);

    string p4 = permute(s0 + s1, P4, 4);
    left = xor_str(left, p4);

    return left + right;
}

string encrypt_char(char c, string key) {
    string bits = "";
    for (int i = 7; i >= 0; i--)
        bits += ((c >> i) & 1) + '0';

    string k1, k2;
    generate_keys(key, k1, k2);

    bits = permute(bits, IP, 8);
    bits = fk(bits, k1);
    bits = bits.substr(4,4) + bits.substr(0,4);
    bits = fk(bits, k2);
    bits = permute(bits, IP_INV, 8);

    char enc = 0;
    for (int i = 0; i < 8; i++)
        enc = (enc << 1) | (bits[i] - '0');

    return string(1, enc);
}

/* ---------- Main ---------- */
int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("Socket creation failed");
        return 1;
    }

    sockaddr_in serv{};
    serv.sin_family = AF_INET;
    serv.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv.sin_addr) <= 0) {
        perror("Invalid address");
        return 1;
    }

    if (connect(sock, (sockaddr*)&serv, sizeof(serv)) < 0) {
        perror("Connection failed");
        return 1;
    }

    string msg, key;
    cout << "Enter message: ";
    getline(cin, msg);

    cout << "Enter 10-bit key: ";
    cin >> key;

    if (key.length() != 10) {
        cout << "Key must be exactly 10 bits!" << endl;
        return 1;
    }

    string encrypted = "";
    for (char c : msg)
        encrypted += encrypt_char(c, key);

    send(sock, encrypted.c_str(), encrypted.size(), 0);
    cout << "Encrypted message sent\n";

    close(sock);
    return 0;
}