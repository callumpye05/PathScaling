#pragma once

#include <vector>
#include <optional>

class MatrixGraph {
private:
    int n;
    std::vector<std::vector<std::optional<int>>> adj;
    bool isDirected;
    int negativeCounter;

public:
    MatrixGraph(int n,bool directed);

    void addEdge(int source, int dest, int weight);

    void removeEdge(int source, int dest); 

    void init(int source , std::vector<int> &distance);  

    void relax(int source, int dest , std::vector<int>& distance);

    std::vector<int> Dijkstra(int source);
};