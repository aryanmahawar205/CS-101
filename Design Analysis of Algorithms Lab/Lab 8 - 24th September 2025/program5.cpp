#include <bits/stdc++.h>
using namespace std;

vector<int> bfsPath(vector<vector<int>>& A, int u, int v) {
    int n=A.size();
    vector<bool> vis(n,false);
    vector<int> parent(n,-1);
    queue<int> q;
    vis[u]=true; q.push(u);

    while(!q.empty()){
        int x=q.front(); q.pop();
        for(int j=0;j<n;j++){
            if(A[x][j]==1 && !vis[j]){
                vis[j]=true; parent[j]=x; q.push(j);
            }
        }
    }
    vector<int> path;
    if(!vis[v]) return path;
    for(int cur=v;cur!=-1;cur=parent[cur]) path.push_back(cur);
    reverse(path.begin(),path.end());
    return path;
}

int main(){
    vector<vector<int>> A={
        {0,1,0,0},
        {1,0,1,1},
        {0,1,0,0},
        {0,1,0,0}};
    int u=0,v=2;
    auto path=bfsPath(A,u,v);
    if(path.empty()) cout<<"No path\n";
    else {
        cout<<"Path: ";
        for(int x: path) cout<<x<<" ";
    }
}