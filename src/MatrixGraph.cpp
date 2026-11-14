#include "MatrixGraph.hpp"
#include <stdexcept>
#include <limits>




int validateVertexCount(int n) {
    if (n < 0){
        throw std::invalid_argument("number of vertices cannot be negative");
    }
    return n;
}


// O(V**2) in terms of memory occupied with V being the amount of vertices. 
MatrixGraph::MatrixGraph(int n, bool directed): 
    n(validateVertexCount(n)),
    adj(n,std::vector<std::optional<int>>(n)),
    isDirected(directed), 
    negativeCounter(0)
{
}





// time complexity O(1) , space memory O(1) 
void MatrixGraph::addEdge(int source, int dest, int weight) {
    if (source < 0 || source >= n || dest < 0 || dest >= n) {
        throw std::out_of_range("Invalid vertex index");
    }

    if (adj[source][dest].has_value() &&adj[source][dest].value() < 0) {
        negativeCounter--;
    }
    if (weight < 0) {
        negativeCounter++;
    }

    adj[source][dest] = weight;
    if (!isDirected) {
        adj[dest][source] = weight;
    }
}

// time complexity O(1) ,  space memory O(1) 
void MatrixGraph::removeEdge(int source , int dest) {
    if (source < 0 || source >= n || dest < 0 || dest >= n) {
        throw std::out_of_range("Invalid vertex index");
    }

    if(adj[source][dest] == std::nullopt) {
        throw std::invalid_argument("There is no edge between these vertices");
    }

    if(adj[source][dest].value() < 0 ) {
        negativeCounter--; 
    }

    adj[source][dest] = std::nullopt;
    if(!isDirected) {
        adj[dest][source] = std::nullopt;
    }
}

void MatrixGraph::relax(int source ,int dest , std::vector<int>& distance) {
    int imax = std::numeric_limits<int>::max();

    if (!adj[source][dest].has_value()) {
        return;
    }

    int weight= *adj[source][dest];

    if (distance[source] == imax || distance[source] > imax -weight) {
        return;
    }

    if(distance[source] + adj[source][dest].value() < distance[dest]) {
        distance[dest] = distance[source] + adj[source][dest].value();    
    }
}

std::vector<int> MatrixGraph::Dijkstra(int source) {
    int imax = std::numeric_limits<int>::max();
    std::vector<int> distance(n,imax); 
    std::vector<bool> visited(n , false);
    int availibleVertices = n; 

    if(source >= n || source < 0 ) {
        throw std::invalid_argument("Cannot have incorrect source");
    }
    distance[source] = 0;

    if(negativeCounter > 0) {
        throw std::invalid_argument("Graph contains negative weights");
    }

    while(availibleVertices > 0 ) {
        
        int minDistance = imax;
        int minVertex = -1; 
        for (int i = 0; i < n; i++) {
            if (!visited[i] && distance[i] < minDistance) {
                minDistance = distance[i];
                minVertex = i;
            }
        }
        if(minVertex == -1) {
            break;
        }
        availibleVertices--;
        visited[minVertex] = true; 
        for (int j = 0 ; j < n ; j++) {
            if(adj[minVertex][j]) {
                relax(minVertex , j , distance);
            }
        }
       
    }

    return distance;
}