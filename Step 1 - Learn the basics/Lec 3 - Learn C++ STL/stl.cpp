// vectors (has dynamic size when compared to array)
vector<int> = {1, 2, 3};

Syntax:
vector<object_type> variable_name;
Example:

vector<int> v1;
vector<char> v2;
vector<string> v3;
Most used functions in Vector:
begin() - it returns an iterator pointing to the first element of the vector.
auto iterator = itr;

itr = v1.begin();
end() - it returns an iterator pointing to the element theoretically after the last element of the vector.
auto iterator = itr;

itr = v1.end();
push_back() - it accepts a parameter and insert the element passed in the parameter in the vectors, the element is inserted at the end.
vector<int> v1;

v1.push_back(1);
v1.push_back(2);
insert() - it is used to insert an element at a specified position.
auto it= v1.begin();
v1.insert(it,5); //inserting 5 at the beginning
erase() - it is used to delete a specific element
vector<int> v1;
auto it= v1.begin();
v1.erase(it);// erasing the first element
pop_back() - it deletes the last element and returns it to the calling function.
v1.pop_back();
front() - it returns a reference to the first element of the vector.
v1.front();
back() - it returns a reference to the last element of the vector.
v1.back();
clear() - deletes all the elements from the vector.
v1.clear();
empty() - to check if the vector is empty or not.
v1.empty();
size() - returns the size of the vector
v1.size();

#include<bits/stdc++.h>

using namespace std;

int main() {
  vector < int > v;

  for (int i = 0; i < 10; i++) {
    v.push_back(i); //inserting elements in the vector
  }

  cout << "the elements in the vector: ";
  for (auto it = v.begin(); it != v.end(); it++)
    cout << * it << " ";

  cout << "\nThe front element of the vector: " << v.front();
  cout << "\nThe last element of the vector: " << v.back();
  cout << "\nThe size of the vector: " << v.size();
  cout << "\nDeleting element from the end: " << v[v.size() - 1];
  v.pop_back();

  cout << "\nPrinting the vector after removing the last element:" << endl;
  for (int i = 0; i < v.size(); i++)
    cout << v[i] << " ";

  cout << "\nInserting 5 at the beginning:" << endl;
  v.insert(v.begin(), 5);
  cout << "The first element is: " << v[0] << endl;
  cout << "Erasing the first element" << endl;
  v.erase(v.begin());
  cout << "Now the first element is: " << v[0] << endl;

  if (v.empty())
    cout << "\nvector is empty";
  else
    cout << "\nvector is not empty" << endl;

  v.clear();
  cout << "Size of the vector after clearing the vector: " << v.size();

}

// Sets
A set in STL is a container that stores unique elements in a particular order. Every operation on a set takes O(1) complexity in the average case and takes O(n) in the worst case.

Syntax:
set<object_type> variable_name;
Example:
set<int> s;
set<string> str;
Functions in set:
insert() – to insert an element in the set.
set<int> s;
s.insert(1);
s.insert(2);
begin() – return an iterator pointing to the first element in the set.
s.begin();
end() – returns an iterator to the theoretical element after the last element.
s.end();
count() – returns true or false based on whether the element is present in the set or not.
set<int> s;
s.insert(1);
s.insert(2);
s.count(2); //returns true
clear() – deletes all the elements in the set.
s.clear();
find() – to search an element in the set.
set<int> s;
s.insert(1);
s.insert(2);
if(s.find(2)!=s.end())
cout<<"true"<<endl;
erase() – to delete a single element or elements between a particular range.
s.erase();
size() – returns the size of the set.
s.size();
empty() – to check if the set is empty or not.
s.empty();

Other functions:
cbegin() – it refers to the first element of the set.
cend() – it refers to the theoretical element after the last element of the set.
rbegin() – it points to the last element of the set.
rend() – it points to the theoretical element before the first element of the set.
bucket_size() – gives the total number of elements present in a specific bucket in a set.
emplace() – to insert an element in the set.
max_size() – the maximum elements a set can hold.
max_bucket_count() – to check the maximum number of buckets a set can hold.

#include<bits/stdc++.h>

using namespace std;

int main() {
  set < int > s;
  for (int i = 1; i <= 10; i++) {
    s.insert(i);
  }

  cout << "Elements present in the set: ";
  for (auto it = s.begin(); it != s.end(); it++) {
    cout << * it << " ";
  }
  cout << endl;
  int n = 2;
  if (s.find(2) != s.end())
    cout << n << " is present in set" << endl;

  s.erase(s.begin());
  cout << "Elements after deleting the first element: ";
  for (auto it = s.begin(); it != s.end(); it++) {
    cout << * it << " ";
  }
  cout << endl;

  cout << "The size of the set is: " << s.size() << endl;

  if (s.empty() == false)
    cout << "The set is not empty " << endl;
  else
    cout << "The set is empty" << endl;
  s.clear();
  cout << "Size of the set after clearing all the elements: " << s.size();
}