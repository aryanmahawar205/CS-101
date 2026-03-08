#include <netinet/in.h>
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

/* ---------- Decryption ---------- */
string playfair_decrypt(const string& cipher, const vector<vector<char>>& keyTable) {
    if (cipher.size() % 2 != 0) {
        cerr << "Invalid ciphertext length\n";
        exit(1);
    }

    string plain;
    for (size_t i = 0; i < cipher.size(); i += 2) {
        int r1, c1, r2, c2;
        if (!findPosition(keyTable, cipher[i], r1, c1) ||
            !findPosition(keyTable, cipher[i + 1], r2, c2)) {
            cerr << "Decryption error\n";
            exit(1);
        }

        if (r1 == r2) {
            plain += keyTable[r1][(c1 + 4) % 5];
            plain += keyTable[r2][(c2 + 4) % 5];
        } else if (c1 == c2) {
            plain += keyTable[(r1 + 4) % 5][c1];
            plain += keyTable[(r2 + 4) % 5][c2];
        } else {
            plain += keyTable[r1][c2];
            plain += keyTable[r2][c1];
        }
    }
    return plain;
}

/* ---------- MAIN ---------- */
int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) { perror("socket"); return 1; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    bind(server_fd, (sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 3);

    int sock = accept(server_fd, nullptr, nullptr);

    char buffer[1024] = {};
    int n = read(sock, buffer, 1024);
    string cipher(buffer, n);

    cout << "Encrypted message received: " << cipher << endl;

    string key;
    cout << "Enter keyword: ";
    cin >> key;
    key = sanitize(key);

    vector<vector<char>> keyTable(5, vector<char>(5));
    generateKeyTable(key, keyTable);

    string plain = playfair_decrypt(cipher, keyTable);
    cout << "Decrypted message: " << plain << endl;

    close(sock);
    close(server_fd);
    return 0;
}