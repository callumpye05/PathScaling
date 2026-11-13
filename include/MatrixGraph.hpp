#pragma once

#include <vector>
#include <optional>

class MatrixGraph {
private:
    int n;
    std::vector<std::vector<std::optional<int>>> adj;
    bool isDirected;

public:
    MatrixGraph(int n,bool directed);

    void addEdge(int source, int dest, int weight);
};