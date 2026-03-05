#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>
#include <cctype>

#define PORT 8080
using namespace std;

/* ---------- Utility ---------- */
string sanitize(const string& s) {
    string r;
    for (char c : s) {
        if (isalpha(c)) {
            c = toupper(c);
            if (c == 'J') c = 'I';
            r += c;
        }
    }
    return r;
}

/* ---------- Key Table ---------- */
void generateKeyTable(const string& key, vector<vector<char>>& keyTable) {
    vector<bool> used(26, false);
    string table;

    for (char c : key) {
        if (!used[c - 'A']) {
            used[c - 'A'] = true;
            table += c;
        }
    }

    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue;
        if (!used[c - 'A']) table += c;
    }

    int k = 0;
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            keyTable[i][j] = table[k++];
}

bool findPosition(const vector<vector<char>>& keyTable, char ch, int& r, int& c) {
    if (ch == 'J') ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (keyTable[i][j] == ch) {
                r = i; c = j;
                return true;
            }
    return false;
}

/* ---------- Encryption ---------- */
string prepareMessage(const string& msg) {
    string res;
    for (size_t i = 0; i < msg.size();) {
        char a = msg[i];
        char b = (i + 1 < msg.size()) ? msg[i + 1] : 'X';

        if (a == b) {
            res += a;
            res += 'X';
            i++;
        } else {
            res += a;
            res += b;
            i += 2;
        }
    }
    if (res.size() % 2 != 0) res += 'X';
    return res;
}

string playfair_encrypt(string msg, const vector<vector<char>>& keyTable) {
    msg = prepareMessage(msg);
    string cipher;

    for (size_t i = 0; i < msg.size(); i += 2) {
        int r1, c1, r2, c2;
        if (!findPosition(keyTable, msg[i], r1, c1) ||
            !findPosition(keyTable, msg[i + 1], r2, c2)) {
            cerr << "Encryption error\n";
            exit(1);
        }

        if (r1 == r2) {
            cipher += keyTable[r1][(c1 + 1) % 5];
            cipher += keyTable[r2][(c2 + 1) % 5];
        } else if (c1 == c2) {
            cipher += keyTable[(r1 + 1) % 5][c1];
            cipher += keyTable[(r2 + 1) % 5][c2];
        } else {
            cipher += keyTable[r1][c2];
            cipher += keyTable[r2][c1];
        }
    }
    return cipher;
}

/* ---------- MAIN ---------- */
int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) { perror("socket"); return 1; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) < 0) {
        perror("connect"); return 1;
    }

    string message, key;
    cout << "Enter message: ";
    cin >> message;
    cout << "Enter keyword: ";
    cin >> key;

    message = sanitize(message);
    key = sanitize(key);

    vector<vector<char>> keyTable(5, vector<char>(5));
    generateKeyTable(key, keyTable);

    string cipher = playfair_encrypt(message, keyTable);
    send(sock, cipher.c_str(), cipher.size(), 0);

    cout << "Encrypted message sent: " << cipher << endl;
    close(sock);
    return 0;
}