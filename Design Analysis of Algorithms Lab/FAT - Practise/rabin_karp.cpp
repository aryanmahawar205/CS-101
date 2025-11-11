#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Number of characters in the input alphabet
#define d 256

/*
 * pat -> pattern
 * txt -> text
 * q -> A prime number
 */
void rabinKarp(string pattern, string text, int q) {
    int m = pattern.length();
    int n = text.length();
    int i, j;

    // Hash value for pattern
    int p = 0; 
    // Hash value for text
    int t = 0; 
    int h = 1;

    // The value of h would be "pow(d, m-1)%q"
    for (i = 0; i < m - 1; i++) {
        h = (h * d) % q;
    }

    // Calculate the hash value of pattern and first window of text
    for (i = 0; i < m; i++) {
        p = (d * p + pattern[i]) % q;
        t = (d * t + text[i]) % q;
    }

    // Slide the pattern over text one by one
    for (i = 0; i <= n - m; i++) {
        // Check the hash values of current window of text and pattern
        // If the hash values match then only check for characters one by one
        if (p == t) {
            /* Check for characters one by one */
            for (j = 0; j < m; j++) {
                if (text[i + j] != pattern[j]) {
                    break;
                }
            }

            // If p == t and pat[0...M-1] = txt[i, i+1, ...i+M-1]
            if (j == m) {
                cout << "Pattern found at index " << i << endl;
            }
        }

        // Calculate hash value for next window of text: Remove leading digit, add trailing digit
        if (i < n - m) {
            t = (d * (t - text[i] * h) + text[i + m]) % q;

            // We might get negative value of t, converting it to positive
            if (t < 0) {
                t = (t + q);
            }
        }
    }
}

// Driver Code
int main() {
    string text = "GEEKSFORGEEKS";
    string pattern = "GEEKS";
    int q = 101; // A prime number

    rabinKarp(pattern, text, q);

    return 0;
}