// Standard Rules:
// 1. Identifier must begin with a letter (A-Z or a-z) or underscore (_)
// 2. Cannot begin with a digit
// 3. Can contain letters, digits, and underscores
// 4. Cannot be a keyword (like int, float, etc.)
// 5. Cannot contain any special characters like @, $, %, etc.

// Custom Rules:
// 6. Identifier must be at least 3 characters long
// 7. Identifier must not end with an underscore
// 8. Identifier must not contain two or more consecutive underscores
// 9. Identifier must not contain uppercase letters (i.e., all lowercase only)
// 10. Identifier must not be longer than 20 characters

#include <bits/stdc++.h>

using namespace std;

// List of keywords (for simplicity)
unordered_set<string> keywords = {
    "int", "float", "char", "double", "return", "if", "else", "for", "while", "do", "void", "boolean", "true", "false"
};

bool isValidIdentifier(const string& id, vector<string>& violatedRules) {
    bool valid = true;

    // Standard Rules:
    if (!(isalpha(id[0]) || id[0] == '_')) {
        violatedRules.push_back("Must begin with a letter or underscore");
        valid = false;
    }

    if (isdigit(id[0])) {
        violatedRules.push_back("Cannot begin with a digit");
        valid = false;
    }

    if (!regex_match(id, regex("^[A-Za-z_][A-Za-z0-9_]*$"))) {
        violatedRules.push_back("Can only contain letters, digits, and underscores");
        valid = false;
    }

    if (keywords.find(id) != keywords.end()) {
        violatedRules.push_back("Cannot be a reserved keyword");
        valid = false;
    }

    if (regex_search(id, regex("[@#$%^&*()+=!~`<>?/|\\-]"))) {
        violatedRules.push_back("Cannot contain special characters");
        valid = false;
    }

    // Custom Rules:
    if (id.length() < 3) {
        violatedRules.push_back("Must be at least 3 characters long");
        valid = false;
    }

    if (id.back() == '_') {
        violatedRules.push_back("Cannot end with an underscore");
        valid = false;
    }

    if (id.find("__") != string::npos) {
        violatedRules.push_back("Cannot contain consecutive underscores");
        valid = false;
    }

    if (regex_search(id, regex("[A-Z]"))) {
        violatedRules.push_back("Must not contain uppercase letters");
        valid = false;
    }

    if (id.length() > 20) {
        violatedRules.push_back("Must not be longer than 20 characters");
        valid = false;
    }

    return valid;
}

int main() {
    string identifier;
    cout << "Enter an identifier: ";
    cin >> identifier;

    vector<string> violatedRules;

    if (isValidIdentifier(identifier, violatedRules)) {
        cout << identifier << " is a valid identifier.\n";
    } else {
        cout << identifier << " is not a valid identifier.\n";
        cout << "Violated Rules:\n";
        for (const string& rule : violatedRules) {
            cout << " - " << rule << endl;
        }
    }

    return 0;
}