void nLetterTriangle(int n)
{
    // outer loop
    for (int i = n; i >= 0; i--)
    {
        // inner loop
        {
            for (char ch = 'A'; ch < 'A' + i; ch++)
                cout << ch << " ";
            
            cout << endl;
        }
    }
}