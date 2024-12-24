// tuple to be printed has [spaces, stars, spaces]
// for n = 5, the tuples are as follows [0,9,0], [1,7,1], [2,5,2], [3,3,3], [4,1,4]
// the spaces follow the number of rows order (ie, they run till i)
// the stars follow the formula - 2n-(2i+1)

void nStarTriangle(int n)
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