// classical example of [space, aplhabet, space] approach

void alphaHill(int n)
{
    // outer loop
    for (int i = 0; i < n; i++)
    {
        // inner loop(s)

        // space
        for (int j = 0; j < n-i-1; j++)
            cout << " ";

        // character
        char ch = 'A';
        int breakpoint = (2*i+1)/2;

        for (int j = 1; j <= 2*i + 1; j++)
        {
            cout << ch << " ";
            if (j <= breakpoint)
                ch++;
            else
                ch--;
        }

        // space
        for (int j = 0; j < n-i-1; j++)
            cout << " ";
        
        cout << endl;
    }
}