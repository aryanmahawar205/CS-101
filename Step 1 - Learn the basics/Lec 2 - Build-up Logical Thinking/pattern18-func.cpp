void alphaTriangle(int n)
{
    char start = n + 64;

    for (int i = 1; i <= n; i++)
    {
        char ch = start;
        for (int j = 1; j <= i; j++)
        {
            cout << ch << " ";
            ch--;
        }
        cout << endl;
    }
}