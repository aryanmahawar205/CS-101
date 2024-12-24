PATTERN 10 FROM CODING NINJAS

void nStarTriangle(int n)
{
    for (int i = 0; i < 2*n; i++)
    {
        int stars = i;

        if (i > n)
            stars = 2*n-i;

        for (int j = 0; j < stars; j++)
            cout << "*";
        cout << endl;
    }
}