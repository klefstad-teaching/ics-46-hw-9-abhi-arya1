#include "dijkstras.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    Graph G;
    file_to_graph(argv[1], G);
    
    for (int srcNode = 0; srcNode < G.numVertices; srcNode++) {
        vector<int> prev;
        vector<int> distances = dijkstra_shortest_path(G, srcNode, prev);
        
        for (int dst = 0; dst < G.numVertices; dst++) {
            print_path(
                extract_shortest_path(distances, prev, dst), 
                distances[dst]
            );
        }
    }
    
    return 0;
}