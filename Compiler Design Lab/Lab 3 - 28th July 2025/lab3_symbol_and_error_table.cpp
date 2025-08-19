#include <bits/stdc++.h>

using namespace std;

struct Symbol {
    string name;
    string type;
    string value;
};

struct Error {
    string name;
    string reason;
};

bool isDataType(const string& word) {
    return word == "int" || word == "float" || word == "char" || word == "boolean";
}

bool isValidIdentifier(const string& name) {
    return regex_match(name, regex("^[a-zA-Z_][a-zA-Z0-9_]*$"));
}

bool isNumber(const string& token) {
    return regex_match(token, regex("^[0-9]+(\\.[0-9]+)?$"));
}

int main() {
    ifstream infile("input.txt");
    ofstream symbolOut("output_symbol_table.txt");
    ofstream errorOut("output_error_table.txt");

    if (!infile.is_open()) {
        cerr << "Error opening input.txt" << endl;
        return 1;
    }

    string line;
    unordered_map<string, Symbol> symbolTable;
    vector<Error> errorTable;
    int index = 0;

    while (getline(infile, line)) {
        if (line.empty()) continue;

        // Remove semicolon
        if (line.back() == ';') line.pop_back();

        stringstream ss(line);
        string first;
        ss >> first;

        if (isDataType(first)) {
            string type = first;
            string rest;
            getline(ss, rest);

            stringstream declStream(rest);
            string token;
            while (getline(declStream, token, ',')) {
                string var, val = "-";
                size_t eq = token.find('=');

                if (eq != string::npos) {
                    var = token.substr(0, eq);
                    val = token.substr(eq + 1);
                } else {
                    var = token;
                }

                // Clean spaces
                var.erase(remove_if(var.begin(), var.end(), ::isspace), var.end());
                val.erase(remove_if(val.begin(), val.end(), ::isspace), val.end());

                // Validate identifier
                if (!isValidIdentifier(var)) {
                    errorTable.push_back({var, "Invalid identifier name"});
                    continue;
                }

                symbolTable[var] = {var, type, val.empty() ? "-" : val};
            }
        } else {
            // Assignment or expression
            size_t eq = line.find('=');
            if (eq != string::npos) {
                string lhs = line.substr(0, eq);
                string rhs = line.substr(eq + 1);
                lhs.erase(remove_if(lhs.begin(), lhs.end(), ::isspace), lhs.end());

                if (!isValidIdentifier(lhs)) {
                    errorTable.push_back({lhs, "Invalid identifier name"});
                    continue;
                }

                if (symbolTable.find(lhs) == symbolTable.end()) {
                    errorTable.push_back({lhs, "Undeclared variable"});
                }

                // Tokenize RHS by replacing non-alnum except dot with space
                for (size_t i = 0; i < rhs.length(); ++i) {
                    if (!isalnum(rhs[i]) && rhs[i] != '.' && rhs[i] != '_') rhs[i] = ' ';
                }
                stringstream rhsStream(rhs);
                string token;
                while (rhsStream >> token) {
                    if (!isNumber(token) && !isValidIdentifier(token)) {
                        errorTable.push_back({token, "Invalid identifier name"});
                    } else if (!isNumber(token) && symbolTable.find(token) == symbolTable.end()) {
                        errorTable.push_back({token, "Undeclared variable"});
                    }
                }

                // Update value if declared
                if (symbolTable.find(lhs) != symbolTable.end()) {
                    symbolTable[lhs].value = rhs;
                }
            }
        }
    }

    // Write symbol table with aligned columns
    symbolOut << left << setw(8) << "Index"
              << setw(15) << "Identifier"
              << setw(10) << "Type"
              << setw(10) << "Value" << "\n";

    index = 0;
    for (const auto& entry : symbolTable) {
        symbolOut << left << setw(8) << index++
                  << setw(15) << entry.second.name
                  << setw(10) << entry.second.type
                  << setw(10) << entry.second.value << "\n";
    }

    // Write error table with aligned columns
    errorOut << left << setw(15) << "Identifier"
             << "Reason" << "\n";
    for (const auto& err : errorTable) {
        errorOut << left << setw(15) << err.name
                 << err.reason << "\n";
    }

    cout << "Symbol table and error table generated successfully." << endl;
    return 0;
}