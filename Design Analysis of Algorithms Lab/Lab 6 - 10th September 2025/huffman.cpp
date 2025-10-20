#include <bits/stdc++.h>
using namespace std;

struct Node{
    char ch;
    int freq;
    Node *left,*right;
    Node(char c,int f){ch=c;freq=f;left=right=NULL;}
};

struct cmp{
    bool operator()(Node* a, Node* b){ return a->freq > b->freq; }
};

void printCodes(Node* root,string s,unordered_map<char,string>& codes){
    if(!root) return;
    if(!root->left && !root->right) codes[root->ch]=s;
    printCodes(root->left,s+"0",codes);
    printCodes(root->right,s+"1",codes);
}

int main(){
    int n; cout<<"Enter number of chars: "; cin>>n;
    vector<char> chars(n); vector<int> freq(n);
    for(int i=0;i<n;i++) cin>>chars[i]>>freq[i];

    priority_queue<Node*,vector<Node*>,cmp> pq;
    for(int i=0;i<n;i++) pq.push(new Node(chars[i],freq[i]));

    while(pq.size()>1){
        Node* l=pq.top(); pq.pop();
        Node* r=pq.top(); pq.pop();
        Node* parent=new Node('$',l->freq+r->freq);
        parent->left=l; parent->right=r;
        pq.push(parent);
    }
    Node* root=pq.top();

    unordered_map<char,string> codes;
    printCodes(root,"",codes);

    cout<<"Huffman Codes:\n";
    for(auto c: codes) cout<<c.first<<": "<<c.second<<"\n";

    int fixed=n*(ceil(log2(n)));
    int huffman=0;
    for(int i=0;i<n;i++) huffman+=freq[i]*codes[chars[i]].size();

    cout<<"Fixed-length size: "<<fixed<<"\n";
    cout<<"Huffman size: "<<huffman<<"\n";
}