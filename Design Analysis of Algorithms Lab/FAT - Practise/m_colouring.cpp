// Graph Colouring Problem (M Colouring Problem):

#include <bits/stdc++.h>

using namespace std;

bool isSafe(int node, vector<int> &color, vector<vector<int>> &graph, int N, int col)
{
    for (int k = 0; k < N; k++)
    {
        if (k != node && graph[k][node] == 1 && color[k] == col)
            return false;
    }
    
    return true;
}

bool solve(int node, vector<int> &color, int M, int N, vector<vector<int>> &graph)
{
    if (node == N)
        return true;
        
    // try every colour for every node
    for (int i = 1; i <= M; i++)
    {
        if (isSafe(node, color, graph, N, i))
        {
            color[node] = i;
            if (solve(node+1, color, M, N, graph))
                return true;
            // nahi hua solve
            color[node] = 0; // backtrack
        }
    }
    
    return false;
}

bool mColouringAlgo(vector<vector<int>> &graph, int M, int N)
{
    vector<int> color(N, 0);
    
    if (solve(0, color, M, N, graph))
        return true;
        
    return false;
}

int main()
{
    int vertex, edge;
    cout << "Enter the no. of vertices in the graph - ";
    cin >> vertex;
    cout << "Enter the no. of edges in the graph - ";
    cin >> edge;
    
    vector<vector<int>> graph(vertex, vector<int>(vertex, 0));
    
    int u, v, weight;
    cout << "Enter the edge relationships - \n";
    
    for (int i = 0; i < edge; i++)
    {
        cin >> u >> v;
        graph[u][v] = 1;
        graph[v][u] = 1;
    }
    
    int M;
    cout << "Enter the number maximum number of colours - "; cin >> M;
    
    if (mColouringAlgo(graph, M, vertex))
        cout << "Yes, we can colour the graph with - " << M << " colours";
    
    else
        cout << "No, we cannot colour the graph with - " << M << " colours";
    
    // print the graph
    // cout << endl << "The graph is - " << endl;
    // for (int i = 0; i < vertex; i++)
    // {
    //     for (int j = 0; j < vertex; j++)
    //         cout << graph[i][j] << " ";
    //     cout << endl;
    // }
    
    return 0;
}