#include <iostream>
#include <vector>

using namespace std;

int largestElement(vector<int> &vec, int left, int right)
{
    int mid = (left + right) / 2;

    if (left == right)
        return vec[left];

    int first_half_largest = largestElement(vec, left, mid);
    int second_half_largest = largestElement(vec, mid+1, right);

    return max(first_half_largest, second_half_largest);
}

int main()
{
    int n; cout << "How many elements would you like to have in your array - "; cin >> n;

    vector<int> nums(n);

    cout << "Input the elements one by one..." << endl;

    for (int i = 0; i < n; i++)
    {
        int val; cin >> val;
        nums[i] = val;
    }

    int largest = largestElement(nums, 0, n-1);

    cout << "The largest element in the array is - " << largest << endl;

    return 0;
}