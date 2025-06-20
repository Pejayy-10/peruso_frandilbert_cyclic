# Cycle Detection in Directed Graphs

A C++ implementation of cycle detection algorithms for directed graphs using both Depth-First Search (DFS) and Breadth-First Search (BFS) approaches.

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Files](#files)
- [How to Run](#how-to-run)
- [Algorithm Explanation](#algorithm-explanation)
- [Sample Input/Output](#sample-inputoutput)
- [Complexity Analysis](#complexity-analysis)
- [Author](#author)

## 🔍 Overview

This project implements two different algorithms to detect cycles in directed graphs:
1. **DFS-based approach** - Uses depth-first search with recursion stack
2. **BFS-based approach** - Uses Kahn's algorithm for topological sorting

Both programs take a directed graph as input (represented by adjacency matrix) and determine if the graph contains any cycles. If a cycle is found, the programs display the vertices involved in the cycle.

## ✨ Features

- **Interactive Input**: Choose between manual matrix input or predefined test cases
- **Clear Visualization**: Display adjacency matrix in readable format
- **Cycle Path Display**: Shows actual vertices in the detected cycle
- **Algorithm Comparison**: Two different approaches for educational purposes
- **Detailed Execution**: Both versions provide clear output about the detection process
- **Error Handling**: Input validation and edge case handling

## 📁 Files

- `cyclic_dfs.cpp` - DFS-based cycle detection implementation
- `cyclic_bfs.cpp` - BFS-based cycle detection implementation  
- `README.md` - This documentation file

## 🚀 How to Run

### Prerequisites
- C++ compiler (g++, Visual Studio, etc.)
- Basic understanding of graph theory

### Compilation
```bash
# Compile DFS version
g++ -o cyclic_dfs cyclic_dfs.cpp

# Compile BFS version  
g++ -o cyclic_bfs cyclic_bfs.cpp
```

### Execution
```bash
# Run DFS version
./cyclic_dfs

# Run BFS version
./cyclic_bfs
```

### Input Format
1. Enter number of vertices
2. Choose input method:
   - Option 1: Manual adjacency matrix input
   - Option 2: Use predefined test case (creates cycle 0→1→2→0)

For manual input, enter the adjacency matrix row by row:
```
Enter the adjacency matrix (3x3):
0 1 0
0 0 1  
1 0 0
```

## 🔬 Algorithm Explanation

### DFS Approach (cyclic_dfs.cpp)
- **Concept**: Uses recursion stack to detect back edges
- **Key Idea**: If we find an edge to a vertex already in our current path, we found a cycle
- **Implementation**: 
  - Maintains `visited[]` and `recStack[]` arrays
  - Uses parent array to reconstruct cycle path
  - Time: O(V + E), Space: O(V)

### BFS Approach (cyclic_bfs.cpp)  
- **Concept**: Uses Kahn's algorithm for topological sorting
- **Key Idea**: If we can't process all vertices topologically, a cycle exists
- **Implementation**:
  - Maintains in-degree for each vertex
  - Uses queue to process vertices with in-degree 0
  - Time: O(V + E), Space: O(V)

## 📊 Sample Input/Output

### Example 1: Graph with Cycle
**Input:**
```
Number of vertices: 3
Adjacency Matrix:
0 1 0
0 0 1
1 0 0
```

**Output (DFS approach):**
```
Graph is CYCLIC!
Cycle detected! Vertices in cycle: 0 -> 1 -> 2 -> 0
Cycle length: 3 edges
```

**Output (BFS approach):**
```
Graph is CYCLIC!
Vertices in cycle: 0 -> 1 -> 2 -> 0
Algorithm could not complete topological sort, indicating cycle presence.
```

### Example 2: Acyclic Graph
**Input:**
```
Number of vertices: 3
Adjacency Matrix:
0 1 1
0 0 1
0 0 0
```

**Output (DFS approach):**
```
Graph is ACYCLIC (No cycle found).
```

**Output (BFS approach):**
```
Graph is ACYCLIC (No cycle found).
Topological order: 0 -> 1 -> 2
```

## ⚡ Complexity Analysis

| Algorithm | Time Complexity | Space Complexity | Approach                   |
|-----------|-----------------|------------------|----------------------------|
| DFS       | O(V + E)        | O(V)             | Back edge detection        |
| BFS       | O(V + E)        | O(V)             | Topological sort failure   |

Where:
- V = number of vertices
- E = number of edges

## 🎯 Key Learning Points

1. **DFS vs BFS**: Different approaches to same problem
2. **Graph Representation**: Adjacency matrix usage
3. **Cycle Detection**: Multiple algorithmic strategies
4. **Path Reconstruction**: Tracing back detected cycles
5. **Topological Sorting**: Connection to cycle detection

## 🐛 Testing

The programs include built-in test cases:
- **Simple 3-vertex cycle**: 0→1→2→0
- **Isolated vertices**: Handling disconnected components
- **Self-loops**: Single vertex cycles
- **Multiple cycles**: Detection of first encountered cycle

## 📝 Notes

- Both programs detect **directed graph cycles** only
- For undirected graphs, the algorithms would need modification
- The BFS approach provides topological sorting as an additional feature
- The DFS approach is more direct for cycle detection
- Both implementations are optimized for educational clarity rather than maximum performance

## 👨‍💻 Author

**Fran Peruso**  
BSCS 2-C
Algorithms and Complexity
Western Mindanao State University
June 2025

---

*This project was created as part of Algorithms and Complexity assignment to demonstrate different approaches to cycle detection in directed graphs.*