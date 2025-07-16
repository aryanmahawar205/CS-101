// clasifcal pattern of [number, space, number] approach

void numberCrown(int n)
{
    int first_number = 2*(n-1);
    // outer loop
    for (int i = 1; i <= n; i++)
    {
        // inner loop(s)

        // number
        for (int j = 1; j <= i; j++)
            cout << j << " ";

        // space
        for (int k = 0; k < first_number; k++)
            cout << " ";

        // number (but reversed)
        for (int j = i; j >= 1; j--)
            cout << j << " ";
        
        cout << endl;
        first_number -= 2;
    }
}