#include <bits/stdc++.h>

using namespace std;

int FibonacciSequence(int n)
{
        if (n == 1 || n == 2)
        {
                return 1;
        }

        else
        {
                int fibNMinusOne = FibonacciSequence(n-1);
                int fibNMinusTwo = FibonacciSequence(n-2);
                int fibNumber = fibNMinusOne + fibNMinusTwo;
                return fibNumber;
        }
}

int main()
{
        int n; cin >> n;
        int result = FibonacciSequence(n);
        cout << result;
}