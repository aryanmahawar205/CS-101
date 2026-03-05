#include <arpa/inet.h>
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

string rowColumn_encrypt(string text, int rows, int cols,
                         const vector<int>& rowKey,
                         const vector<int>& colKey) {

    int size = rows * cols;
    while (text.length() < size)
        text += 'X';

    vector<vector<char>> matrix(rows, vector<char>(cols));
    int k = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            matrix[i][j] = text[k++];

    vector<vector<char>> colTrans(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            colTrans[i][j] = matrix[i][colKey[j] - 1];

    vector<vector<char>> finalMat(rows, vector<char>(cols));
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            finalMat[i][j] = colTrans[rowKey[i] - 1][j];

    string cipher;
    for (auto& r : finalMat)
        for (char c : r)
            cipher += c;

    return cipher;
}

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

    connect(sock, (sockaddr*)&addr, sizeof(addr));

    string message;
    int rows, cols;

    cout << "Enter message: ";
    cin >> message;

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

    string cipher = rowColumn_encrypt(message, rows, cols, rowKey, colKey);
    send(sock, cipher.c_str(), cipher.length(), 0);

    cout << "Encrypted message sent: " << cipher << endl;
    close(sock);
    return 0;
}