#include <bits/stdc++.h>

using namespace std;

// Check if character is an operator
bool isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

// Function to check if parentheses are balanced
bool areParenthesesBalanced(const string& expr) {
    stack<char> s;
    for (char c : expr) {
        if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            if (s.empty()) return false;
            s.pop();
        }
    }
    return s.empty();
}

// Function to validate an arithmetic expression
bool isValidExpression(const string& expr) {
    if (expr.empty()) return false;

    // 1. Check balanced parentheses
    if (!areParenthesesBalanced(expr)) return false;

    bool lastWasOperator = true; // to handle cases like "-a"
    bool hasOperand = false;

    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];

        if (isspace(c)) continue; // ignore spaces

        if (isalnum(c)) { // operand (number or variable)
            hasOperand = true;
            lastWasOperator = false;
        } 
        else if (isOperator(c)) {
            if (lastWasOperator && c != '-') {
                return false; // two operators in a row (except unary minus)
            }
            lastWasOperator = true;
        } 
        else if (c == '(') {
            lastWasOperator = true; 
        } 
        else if (c == ')') {
            if (lastWasOperator) return false; // shouldn't end with operator
            lastWasOperator = false;
        } 
        else {
            return false; // invalid symbol
        }
    }

    if (lastWasOperator) return false; // expression shouldn't end with operator
    if (!hasOperand) return false;     // must have at least one operand

    return true;
}

int main() {
    ifstream inputFile("input_23BDS1095.txt");
    ofstream outputFile("output_23BDS1095.txt");

    if (!inputFile) {
        cerr << "Could not open input_23BDS1095.txt\n";
        return 1;
    }

    string line;
    while (getline(inputFile, line)) {
        if (isValidExpression(line)) {
            outputFile << line << " → Valid\n";
        } else {
            outputFile << line << " → Invalid\n";
        }
    }

    cout << "Validation complete. Check output_23BDS1095.txt\n";

    inputFile.close();
    outputFile.close();
    return 0;
}