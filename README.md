# PathScaling

PathScaling is a C++ project that investigates how graph representation,
algorithm choice, and parallel execution affect the performance of graph
algorithms. Benchmarks run on Linux and measure how runtime changes as graph
size and edge density increase.

## Algorithms

- **Implemented** — Dijkstra's algorithm on an adjacency matrix, with an initial
  benchmark that varies the number of vertices.
- **Planned shortest-path algorithms** — Bellman–Ford and Johnson's algorithm.
- **Planned graph traversals** — breadth-first search (BFS) and depth-first search
  (DFS). BFS also finds shortest paths in unweighted graphs.
- **Planned parallel experiments** — run independent shortest-path searches
  from different source vertices on the same graph and measure how throughput
  changes with the number of worker threads.

## Technologies and benchmark environment

| Tool or component | How PathScaling uses it |
| --- | --- |
| C++17 | Implements graph representations, shortest-path algorithms, and benchmarks. |
| C++ standard library | `std::vector` stores the adjacency matrix and search state. `std::optional<int>` represents an edge weight or the absence of an edge. `std::chrono::steady_clock` measures elapsed search time. |
| GCC (`g++`) | Compiles with `-std=c++17 -O2 -g` to enable optimisation and keep debug information for profiling. |
| Ubuntu Linux and Bash | Runs the benchmarks from the terminal. `bash benchmarks/run.sh` runs the benchmark across several graph sizes. |
| Linux `perf` | `perf stat` measures CPU cycles, instructions, branches, and branch misses. `perf record` and `perf report` identify hot spots down to the assembly level. |
| AMD Ryzen 7 5700 | CPU used for the initial benchmark and profiling runs. |

## Graph representations

### Adjacency matrix

The current implementation uses a nested `std::vector` with `n` rows of `n`
cells, where `n` is the number of vertices. Each cell stores an optional edge
weight, so a missing edge is distinct from an edge with weight zero.

| Operation | Complexity |
| --- | --- |
| Storage | O(n²) |
| Look up, add, or remove an edge between two known vertices | O(1) |
| Find all outgoing edges from one vertex | O(n) |
| BFS or DFS from one source, worst case | O(n²) |

The matrix gives constant-time edge lookup. Finding a vertex's neighbours
requires scanning its entire row, including empty cells. This cost is
especially relevant for sparse graphs, where each vertex may have only a few
neighbours.