#include <bits/stdc++.h>

using namespace std;

// Function to remove single-line and multi-line comments from a string
string removeComments(const string& code) {
    string result;
    bool inSingleLineComment = false;
    bool inMultiLineComment = false;

    for (size_t i = 0; i < code.length(); ++i) {
        if (!inSingleLineComment && !inMultiLineComment && i + 1 < code.length()) {
            if (code[i] == '/' && code[i + 1] == '/') {
                inSingleLineComment = true;
                ++i;
                continue;
            }
            if (code[i] == '/' && code[i + 1] == '*') {
                inMultiLineComment = true;
                ++i;
                continue;
            }
        }

        if (inSingleLineComment && code[i] == '\n') {
            inSingleLineComment = false;
        } else if (inMultiLineComment && i + 1 < code.length() && code[i] == '*' && code[i + 1] == '/') {
            inMultiLineComment = false;
            ++i;
        } else if (!inSingleLineComment && !inMultiLineComment) {
            result += code[i];
        }
    }

    return result;
}

// Function to clean up extra spaces, tabs, and newlines
string cleanWhitespace(const string& code) {
    string cleaned;

    // 1. Replace tabs with single space
    string temp = regex_replace(code, regex("\t"), " ");

    // 2. Remove multiple spaces with one space
    temp = regex_replace(temp, regex(" +"), " ");

    // 3. Remove spaces before and after newlines
    temp = regex_replace(temp, regex(" *\n *"), "\n");

    // 4. Remove empty lines
    temp = regex_replace(temp, regex("\n+"), "\n");

    return temp;
}

int main() {
    ifstream inputFile("input.txt");
    ofstream outputFile("output_cleaned.txt");

    if (!inputFile) {
        cerr << "Error: input.txt not found.\n";
        return 1;
    }

    stringstream buffer;
    buffer << inputFile.rdbuf();
    string code = buffer.str();

    string noComments = removeComments(code);
    string cleaned = cleanWhitespace(noComments);

    outputFile << cleaned;

    cout << "Cleaning complete...cleaned code in 'output_cleaned.txt'.\n";

    inputFile.close();
    outputFile.close();

    return 0;
}