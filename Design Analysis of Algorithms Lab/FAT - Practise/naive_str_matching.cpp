#include <bits/stdc++.h>

using namespace std;

int main()
{
    string text, pattern;
    cout << "Enter the text string - ";
    getline(cin, text);
    cout << "Enter the pattern string - ";
    getline(cin, pattern);

    int text_size = text.size();
    int pattern_size = pattern.size();

    for (int i = 0; i < text_size-pattern_size; i++)
    {
        int j;
        for (j = 0; j < pattern_size; j++)
        {
            if (text[i+j] != pattern[j])
                break;
        }

        if (j == pattern_size)
            cout << "Pattern found at index - " << i << endl;
    }

    return 0;
}