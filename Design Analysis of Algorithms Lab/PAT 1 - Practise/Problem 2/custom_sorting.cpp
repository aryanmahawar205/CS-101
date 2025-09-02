// Given n 2-dimensional points (x1, y1), (x2, y2), . . . , (xn, yn), Design an algorithm that
// follows the ‘Divide-Conquer-Combine’ strategy to
// (a) arrange the n−points in an increasing order of the x coordinates
// (b) arrange the n−points in an increasing order of the y coordinates
// (c) arrange the n − points in decreasing order of the value (x − coordinate + y −
// coordinate)/2) coordinates

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n; cout << "Enter the number of pairs of elements you want - "; cin >> n;

    vector<pair<int, int>> pairs;

    cout << "Enter the pairs separated by a space - " << endl;

    for (int i = 0; i < n; i++)
    {
        int num1; int num2; cin >> num1 >> num2;
        pair<int, int> p = {num1, num2};
        pairs.push_back(p);
    }

    vector<pair<int, int>> part_a = pairs;
    vector<pair<int, int>> part_b = pairs;
    vector<pair<int, int>> part_c = pairs;

    auto comparator_a = [](pair<int, int> &p1, pair<int, int> &p2) {
        if (p1.first < p2.first)
            return true;
        return false;
    };

    auto comparator_b = [](pair<int, int> &p1, pair<int, int> &p2) {
        if (p1.second < p2.second)
            return true;
        return false;
    };

    auto comparator_c = [](pair<int, int> &p1, pair<int, int> &p2) {
        int average_pair_p1 = (p1.first + p1.second) / 2;
        int average_pair_p2 = (p2.first + p2.second) / 2;
        
        if (average_pair_p1 > average_pair_p2)
            return true;
        return false;
    };

    sort(part_a.begin(), part_a.end(), comparator_a);
    sort(part_b.begin(), part_b.end(), comparator_b);
    sort(part_c.begin(), part_c.end(), comparator_c);

    cout << "Part 'A' sorting result - ";
    for (auto it : part_a)
        cout << "(" << it.first << "," << it.second << ")" << " ";
    cout << endl;

    cout << "Part 'B' sorting result - ";
    for (auto it : part_b)
        cout << "(" << it.first << "," << it.second << ")" << " ";
    cout << endl;

    cout << "Part 'C' sorting result - ";
    for (auto it : part_c)
        cout << "(" << it.first << "," << it.second << ")" << " ";
    cout << endl;

    return 0;
}