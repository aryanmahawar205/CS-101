// tuple to be printed has [spaces, stars, spaces]
// for n = 5, the tuples are as follows [4,1,4], [3,3,3], [2,5,2], [1,7,1], [0,9,0]
// the spaces follow n-i-1 and for the stars, they follow 2*i+1

void nStarTriangle(int n)
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
}