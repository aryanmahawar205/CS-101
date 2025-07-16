// every even row starts with 1, then flip
// every odd row starts with 0, then flip

void nBinaryTriangle(int n)
{
    for (int i = 0; i < n; i++)
    {
        int start;
        if (i%2 == 0)
            start = 1;
        else
            start = 0;

        for (int j = 0; j <= i; j++)
        {
            cout << start << " ";
            start = 1-start;
        }
        cout << endl;
    }
}
