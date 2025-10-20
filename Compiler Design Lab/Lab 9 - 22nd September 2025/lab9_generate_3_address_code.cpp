/*
Lab Experiment: Generate Optimized Three Address Code (TAC)
-----------------------------------------------------------
Problem Statement:
Write a C++ program that reads an arithmetic expression from console input
and generates the corresponding optimized three-address code without 
introducing redundant temporaries.

Example:
Input:  a = a+b-c*d
Output:
t1 = c * d
t2 = a + b
a  = t2 - t1
*/

#include <bits/stdc++.h>
using namespace std;

// Utility function to check operator precedence
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

// Convert infix expression to postfix (Shunting Yard Algorithm)
vector<string> infixToPostfix(const string &expr) {
    stack<char> st;
    vector<string> output;
    for (size_t i = 0; i < expr.size(); i++) {
        char c = expr[i];
        if (isspace(c)) continue;

        if (isalnum(c)) {
            string operand(1, c);
            output.push_back(operand);
        } else if (c == '(') {
            st.push(c);
        } else if (c == ')') {
            while (!st.empty() && st.top() != '(') {
                output.push_back(string(1, st.top()));
                st.pop();
            }
            if (!st.empty()) st.pop();
        } else { // operator
            while (!st.empty() && precedence(st.top()) >= precedence(c)) {
                output.push_back(string(1, st.top()));
                st.pop();
            }
            st.push(c);
        }
    }
    while (!st.empty()) {
        output.push_back(string(1, st.top()));
        st.pop();
    }
    return output;
}

// Generate optimized Three Address Code from postfix expression
void generateTAC(const vector<string>& postfix, const string &lhs) {
    stack<string> st;
    int tempCount = 1;

    for (size_t i = 0; i < postfix.size(); i++) {
        string token = postfix[i];
        if (isalnum(token[0])) {
            st.push(token);
        } else {
            string op2 = st.top(); st.pop();
            string op1 = st.top(); st.pop();

            // If this is the last operation, store directly in LHS
            if (i == postfix.size() - 1) {
                cout << lhs << " = " << op1 << " " << token << " " << op2 << endl;
                st.push(lhs);
            } else {
                string temp = "t" + to_string(tempCount++);
                cout << temp << " = " << op1 << " " << token << " " << op2 << endl;
                st.push(temp);
            }
        }
    }
}

int main() {
    string expr;
    cout << "Enter an expression (e.g., a=a+b-c*d): ";
    getline(cin, expr);

    // Split LHS and RHS
    size_t eqPos = expr.find('=');
    if (eqPos == string::npos) {
        cerr << "Invalid expression. Must contain '='." << endl;
        return 1;
    }

    string lhs = expr.substr(0, eqPos);
    string rhs = expr.substr(eqPos + 1);

    // Trim spaces
    lhs.erase(remove_if(lhs.begin(), lhs.end(), ::isspace), lhs.end());
    rhs.erase(remove_if(rhs.begin(), rhs.end(), ::isspace), rhs.end());

    // Convert RHS to postfix
    vector<string> postfix = infixToPostfix(rhs);

    // Generate TAC
    cout << "\nOptimized Three Address Code:\n";
    generateTAC(postfix, lhs);

    return 0;
}