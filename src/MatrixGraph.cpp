#include "MatrixGraph.hpp"
#include <stdexcept>

MatrixGraph::MatrixGraph(int n, bool directed): 
    n(n),
    adj(n,std::vector<std::optional<int>>(n)),
    isDirected(directed)
{
}

void MatrixGraph::addEdge(int source, int dest, int weight) {
    if (source < 0 || source >= n || dest < 0 || dest >= n) {
        throw std::out_of_range("Invalid vertex index");
    }
    adj[source][dest] =weight;
    if (!isDirected) {
        adj[dest][source] =weight;
    }
}