#include <iostream>
#include "MatrixGraph.hpp"

int main() {
    MatrixGraph graph(5, false);
    graph.addEdge(0,1,10);
    graph.addEdge(1, 2,5);
    std::cout << "graph is created\n";
    return 0;
}