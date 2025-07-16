void nNumberTriangle(int n)
{
    int num = 1;
    // outer loop
    for (int i = 1; i <= n; i++)
    {
        // inner loop
        for (int j = 1; j <= i; j++)
        {    cout << num << " ";
             num++;
        }
        
        cout << endl;
    }
}