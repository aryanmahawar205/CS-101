#include <bits/stdc++.h>

using namespace std;

// List of C++ keywords
const set<string> keywords = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double",
    "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long",
    "register", "restrict", "return", "short", "signed", "sizeof", "static", "struct",
    "switch", "typedef", "union", "unsigned", "void", "volatile", "while", "bool",
    "namespace", "class", "public", "private", "protected", "true", "false", "using"
};

// Set of punctuations and operators (for simplicity)
const set<char> punctuations = {
    ';', ',', '.', '(', ')', '{', '}', '[', ']', '=', '+', '-', '*', '/', '<', '>', '!', '&', '|', ':'
};

// Check if a token is a literal
bool isLiteral(const string& token) {
    return regex_match(token, regex(R"(^\d+(\.\d+)?$)")) ||                      // int or float
           regex_match(token, regex(R"(^'.'$)")) ||                              // char
           regex_match(token, regex(R"(^\".*\"$)"));                             // string
}

// Check if token is valid identifier
bool isIdentifier(const string& token) {
    return regex_match(token, regex(R"(^[a-zA-Z_]\w*$)")) && !keywords.count(token);
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    if (!input) {
        cerr << "Could not open input.txt\n";
        return 1;
    }
    string line;
    set<string> found_keywords;
    set<string> found_literals;
    set<string> found_identifiers;
    set<char> found_punctuations;

    while (getline(input, line)) {
        // Remove comments
        line = regex_replace(line, regex(R"(//.*)"), "");

        // Tokenize using regex (separate operators and words)
        stringstream ss;
        for (char ch : line) {
            if (punctuations.count(ch)) {
                ss << ' ' << ch << ' ';
                found_punctuations.insert(ch);
            } else {
                ss << ch;
            }
        }

        string token;
        while (ss >> token) {
            if (keywords.count(token)) {
                found_keywords.insert(token);
            } else if (isLiteral(token)) {
                found_literals.insert(token);
            } else if (isIdentifier(token)) {
                found_identifiers.insert(token);
            }
        }
    }

    // Output results
    output << "=== Token Analysis ===\n\n";

    output << "Keywords (" << found_keywords.size() << "):\n";
    for (const string& k : found_keywords) output << "  - " << k << "\n";

    output << "\nLiterals (" << found_literals.size() << "):\n";
    for (const string& l : found_literals) output << "  - " << l << "\n";

    output << "\nIdentifiers (" << found_identifiers.size() << "):\n";
    for (const string& id : found_identifiers) output << "  - " << id << "\n";

    output << "\nPunctuations/Operators (" << found_punctuations.size() << "):\n";
    for (char p : found_punctuations) output << "  - " << p << "\n";

    cout << "Token analysis complete. Check 'output.txt'.\n";
    input.close();
    output.close();

    return 0;
}