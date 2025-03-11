#include "dijkstras.h"

int main(int argc, char *argv[]) {
    Graph G;
    file_to_graph("src/small.txt", G);

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, 0, previous);
    for(int i = 0; i < G.numVertices; ++i){
        print_path(extract_shortest_path(distances, previous, i), distances[i]);
    }

}