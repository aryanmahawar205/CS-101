void alphaRamp(int n)
{
    char repeated = 'A';
    // outer loop
    for (int i = 1; i <= n; i++)
    {
        // inner loop
        for (char ch = 'A'; ch < 'A' + i; ch++)
            cout << repeated << " ";

        repeated++;
        cout << endl;
    }
}