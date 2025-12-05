#include <bits/stdc++.h>

using namespace std;

string encryptMessage(string original_message, int key)
{
    int n = original_message.size();

    string encrypted_message = "";

    unordered_map<int, int> codes;

    int x = 0;
    for (int i = ; i <= 90; i++)
    {
        codes[i] = x;
        x++;
    }

    for (auto &it : original_message)
    {
        int ascii = it;

        if (codes.find(ascii) != codes.end()) // exist karta hain
        {
            int code = codes[ascii];
            code = (code+key) % 26;

            for (auto &it: codes)
            {
                if (it.second == code)
                    encrypted_message += it.first;
            }
        }
    }

    return string(encrypted_message);
}

// string decryptMessage(string encrypted_message, int key)
// {
    
// }

int main()
{
    string original_message;
    cout << "Enter the original message: "; cin >> original_message;
    cout << "Original message is: " << original_message << endl;

    int k;
    cout << "Enter the value of Key (k) shift: "; cin >> k;

    string encrypted_message = encryptMessage(original_message, k);
    cout << "Encrypted message is: " << encrypted_message << endl;

    // string decrypted_message = decryptMessage(encrypted_message, k);
    // cout << "Decrypted message is: " << decrypted_message << endl;

    return 0;
}