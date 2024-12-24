void reverse(int n)
{
    for (int i = 0; i < n; i++)
    {
        // inner loop for spaces
        for (int j = 0; j < i; j++)
            cout << " ";

        // inner loop for stars
        for (int j = 0; j < 2*n-(2*i+1); j++)
            cout << "*";

        // inner loop for spaces
        for (int j = 0; j < i; j++)
            cout << " ";
        
        cout << endl;
    }
}

void nStarDiamond(int n)
{
    for (int i = 0; i < n; i++)
    {
        // inner loop for spaces
        for (int j = 0; j < n-i-1; j++)
            cout << " ";

        // inner loop for stars
        for (int j = 0; j < 2*i+1; j++)
            cout << "*";

        // inner loop for spaces
        for (int j = 0; j < n-i-1; j++)
            cout << " ";
        
        cout << endl;
    }
    
    reverse(n);
}