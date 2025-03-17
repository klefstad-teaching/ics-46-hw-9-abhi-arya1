#include "dijkstras.h" 
#include <iostream> 
#include <fstream>
#include <queue>

using namespace std;


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {;
    vector<int> distances(G.numVertices, INF);
    previous.assign(G.numVertices, -1);
    vector<bool> visited(G.numVertices, false);
    
    priority_queue<Node, vector<Node>, greater<Node>> pq;
    
    distances[source] = 0;
    pq.push(Node(source, 0));
    
    while (!pq.empty()) {
        Node top = pq.top();
        int u = top.vertex;
        pq.pop();
        
        if (visited[u]) continue;
        
        visited[u] = true;
        
        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;
            
            if (!visited[v] && distances[u] != INF && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distances[v]));
            }
        }
    }
    
    return distances;
}


vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> shortest; 

    for (int v = destination; v != -1; v = previous[v]) { 
        shortest.insert(shortest.begin(), v); 
    }
    
    return shortest;
}


void print_path(const vector<int>& path, int total) {
    for (int i = 0; i < path.size(); i++) {
        cout << path[i] << " ";
    }
    
    cout << "\nTotal cost is " << total << endl;
}