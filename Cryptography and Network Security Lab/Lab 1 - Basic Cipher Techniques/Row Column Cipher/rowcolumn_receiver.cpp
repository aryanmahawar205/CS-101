#include <netinet/in.h>
#include <iostream>
#include <string>
#include <vector>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 8080
using namespace std;

bool validKey(const vector<int>& key, int n) {
    vector<bool> seen(n + 1, false);
    for (int k : key) {
        if (k < 1 || k > n || seen[k]) return false;
        seen[k] = true;
    }
    return true;
}

string rowColumn_decrypt(string cipher, int rows, int cols,
                         const vector<int>& rowKey,
                         const vector<int>& colKey) {

    if (cipher.length() != rows * cols) {
        cerr << "Cipher length mismatch\n";
        exit(1);
    }

    vector<vector<char>> finalMat(rows, vector<char>(cols));
    int k = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            finalMat[i][j] = cipher[k++];

    vector<vector<char>> colTrans(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            colTrans[rowKey[i] - 1][j] = finalMat[i][j];

    vector<vector<char>> matrix(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][colKey[j] - 1] = colTrans[i][j];

    string plain;
    for (auto& r : matrix)
        for (char c : r)
            plain += c;

    return plain;
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

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

    int rows, cols;
    cout << "Rows: ";
    cin >> rows;
    cout << "Columns: ";
    cin >> cols;

    vector<int> rowKey(rows), colKey(cols);

    cout << "Row key: ";
    for (int i = 0; i < rows; i++) cin >> rowKey[i];

    cout << "Column key: ";
    for (int i = 0; i < cols; i++) cin >> colKey[i];

    if (!validKey(rowKey, rows) || !validKey(colKey, cols)) {
        cerr << "Invalid key permutation\n";
        return 1;
    }

    string plain = rowColumn_decrypt(cipher, rows, cols, rowKey, colKey);
    cout << "Decrypted message: " << plain << endl;

    close(sock);
    close(server_fd);
    return 0;
}