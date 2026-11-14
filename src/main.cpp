#include <iostream>
#include <vector>
#include <limits>
#include "MatrixGraph.hpp"

int main() {
    MatrixGraph graph(5, true);

    graph.addEdge(0, 1, 10);
    graph.addEdge(0, 2, 3);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 2);
    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 2);
    graph.addEdge(3, 4, 7);
    graph.addEdge(4, 3, 9);

    std::vector<int> distances = graph.Dijkstra(0);

    std::cout << "Dijkstra from vertex 0:\n";

    for (std::size_t i = 0; i < distances.size(); i++) {
        std::cout << "Vertex " << i << ": ";

        if (distances[i] == std::numeric_limits<int>::max()) {
            std::cout << "Unreachable\n";
        } else {
            std::cout << distances[i] << "\n";
        }
    }

    return 0;
}