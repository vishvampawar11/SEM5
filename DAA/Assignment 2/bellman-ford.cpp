#include <iostream>
#include <vector>

using namespace std;

int infinity = 1e9;

struct edge
{
    int start;
    int end;
    int weight;
};

bool bellmanFord(int V, int E, vector<edge> &edges, vector<int> &dist)
{
    // relaxing all edges E -1 times
    for (int i = 0; i < E - 1; i++)
    {
        for (auto e : edges)
        {
            if (dist[e.start] + e.weight < dist[e.end])
                dist[e.end] = dist[e.start] + e.weight;
        }
    }

    // checking for cycle by relaxing all edges one more time
    bool isCycle = false;
    for (auto e : edges)
    {
        if (dist[e.start] + e.weight < dist[e.end])
        {
            isCycle = true;
            break;
        }
    }
    return isCycle;
}

int main()
{
    int V, E;
    cout << "Enter the no. of vertces: ";
    cin >> V;
    cout << "Enter the no. of edges: ";
    cin >> E;

    vector<edge> edges;

    cout << "Enter the starting vertex, ending vertex and weight of all edges\n";
    for (int i = 0; i < E; i++)
    {
        edge e;
        int start, end, weight;
        cin >> start >> end >> weight;
        e.start = start;
        e.end = end;
        e.weight = weight;
        edges.push_back(e);
    }

    int source;
    cout << "Enter source: ";
    cin >> source;

    vector<int> dist(V, infinity);
    dist[source] = 0;

    bool isCycle = bellmanFord(V, E, edges, dist);

    if (isCycle)
        cout << "The graph has negative cycle\n";
    else
    {
        cout << "---------------------\n";
        cout << "| Vertex | Distance |\n";
        cout << "---------------------\n";
        for (int i = 0; i < V; i++)
            cout << "|   " << i << "    |    " << dist[i] << "     |"
                 << "\n";
        cout << "---------------------\n";
    }
    return 0;
}

/*

OUTPUT =>
Enter the no. of vertces: 5
Enter the no. of edges: 6
Enter the starting vertex, ending vertex and weight of all edges
0 1 2
0 2 8
1 3 -2
1 4 5
4 2 2
4 3 -4
Enter source: 0
---------------------
| Vertex | Distance |
---------------------
|   0    |    0     |
|   1    |    2     |
|   2    |    8     |
|   3    |    0     |
|   4    |    7     |
---------------------

*/
