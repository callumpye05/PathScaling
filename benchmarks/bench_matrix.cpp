#include "MatrixGraph.hpp"
#include <chrono>
#include <iostream>
#include <string>

int main(int argc,char** argv) {
    const int n = argc > 1 ? std::stoi(argv[1]) : 4000;
    if (n < 2){
        std::cerr <<"need at least two vertices\n";
        return 1;
    }

    constexpr int runs =20;
    MatrixGraph graph(n, true);

    for (int i = 0; i < n - 1; ++i) {
        graph.addEdge(i,i + 1, 1);
    }
    long checksum = 0;
    const auto start =std::chrono::steady_clock::now();

    for (int run = 0; run < runs; ++run) {
        checksum += graph.Dijkstra(0).back();
    }
    const auto elapsed =std::chrono::steady_clock::now() -start;
    const double ms =std::chrono::duration<double,std::milli>(elapsed).count();

    std::cout << "vertices=" <<n<< " ms/run=" << ms / runs<< " checksum=" << checksum << '\n';
}