// Bellman Ford Algorithm (Single source shortest path):

#include <bits/stdc++.h>

using namespace std;

int main()
{
    int vertex, edge;
    cout << "Enter the no. of vertices in the graph - ";
    cin >> vertex;
    cout << "Enter the no. of edges in the graph - ";
    cin >> edge;
    
    vector<vector<int>> graph(vertex, vector<int>(vertex, 0));
    
    // assign intially all weights as 1e9 (meaning not reachable) and diagonals cost as 0 due to self loop
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
        {
            graph[i][j] = 1e9;
            
            if (i == j)
                graph[i][j] = 0;
        }
    }
    
    int u, v, weight; // edge relationships between vertices u and v with corresponding edge weight
    cout << "Enter the edge relationships with weight - \n";
    
    for (int i = 0; i < edge; i++)
    {
        cin >> u >> v >> weight;
        graph[u][v] = weight;
    }
    
    // actual bellman ford starts
    int source;
    cout << "Enter the source vertex you want to begin with - ";
    cin >> source;
    
    vector<int> res(vertex, 1e9);
    res[source] = 0; // source se distance zero hain baaki sab tak infinity (1e9)
    
    for (int i = 0; i < vertex-1; i++) // n-1 relaxations
    {
        for (int u = 0; u < vertex; u++) // iterate over all vertices
        {
            for (int v = 0; v < vertex; v++) // check all possible destinations
            {
                int w = graph[u][v];
                
                if (w != 1e9 && res[u] + w < res[v])
                    res[v] = res[u] + w;
            }
        }
    }
    
    // print the graph
    cout << endl << "The graph is - " << endl;
    for (int i = 0; i < vertex; i++)
    {
        for (int j = 0; j < vertex; j++)
            cout << graph[i][j] << " ";
        cout << endl;
    }
    
    // print the least distances from source vertex computed by bellman ford
    for (auto it : res)
        cout << it << " ";
    
    return 0;
}