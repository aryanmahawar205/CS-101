#include <bits/stdc++.h>
using namespace std;

map<char, vector<string>> grammar;  // Grammar rules
char startSymbol;                   // Start symbol

// Recursive function to check parsing
bool parseString(string input, int pos, char symbol, int &finalPos) {
    // If terminal
    if (!isupper(symbol)) {
        if (pos < input.size() && input[pos] == symbol) {
            finalPos = pos + 1;
            return true;
        }
        return false;
    }

    // If non-terminal: check each production
    for (string prod : grammar[symbol]) {
        int tempPos = pos;
        bool ok = true;

        // Empty production (epsilon, '#')
        if (prod == "#") {
            finalPos = pos;
            return true;
        }

        for (char c : prod) {
            int newPos;
            if (!parseString(input, tempPos, c, newPos)) {
                ok = false;
                break;
            }
            tempPos = newPos;
        }

        if (ok) {
            finalPos = tempPos;
            return true;
        }
    }

    return false;
}

int main() {
    ifstream fin("input_23BDS1095.txt");
    if (!fin.is_open()) {
        cerr << "Error: Could not open grammar file.\n";
        return 1;
    }

    string line;
    bool firstRule = true;
    while (getline(fin, line)) {
        if (line.empty()) continue;

        string lhs, arrow, rhs;
        stringstream ss(line);
        ss >> lhs >> arrow >> rhs;

        if (firstRule) {
            startSymbol = lhs[0];
            firstRule = false;
        }

        string prod = "";
        for (char c : rhs) {
            if (c == '/') {
                grammar[lhs[0]].push_back(prod);
                prod = "";
            } else {
                prod.push_back(c);
            }
        }
        if (!prod.empty()) grammar[lhs[0]].push_back(prod);
    }
    fin.close();

    string input;
    cout << "Enter input string: ";
    cin >> input;

    int finalPos = 0;
    if (parseString(input, 0, startSymbol, finalPos) && finalPos == input.size()) {
        cout << "YES, the string can be parsed by the grammar.\n";
    } else {
        cout << "NO, the string cannot be parsed by the grammar.\n";
    }

    return 0;
}