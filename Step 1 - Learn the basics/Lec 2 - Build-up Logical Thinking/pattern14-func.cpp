void nLetterTriangle(int n)
{
    // outer loop
    for (int i = 1; i <= n; i++)
    {
        // inner loop
        for (char ch = 'A'; ch < 'A' + i; ch++)
            cout << ch << " ";
        
        cout << endl;
    }
}