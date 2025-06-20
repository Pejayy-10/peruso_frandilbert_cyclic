/*
 * DFS Cycle Detection in Directed Graph
 * Author: [Fran Peruso]
 * Date: [June 06 2025]
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

class CyclicDFS {
private:
    int vertices;                    // number of vertices in graph
    vector<vector<int>> adjMatrix;   // adjacency matrix representation
    vector<int> visited;             // keeps track of visited vertices
    vector<int> recStack;            // recursion stack to detect back edges
    vector<int> parent;              // parent array to reconstruct cycle path
    vector<int> cyclePath;           // stores the actual cycle path
    
public:
    // Constructor - initialize all our data structures
    CyclicDFS(int v) : vertices(v) {
        adjMatrix.resize(v, vector<int>(v, 0));
        visited.resize(v, 0);
        recStack.resize(v, 0);
        parent.resize(v, -1);
    }
    
    // Helper function to add an edge manually
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
    }
    
    // Get adjacency matrix input from user
    void inputGraph() {
        cout << "Enter the adjacency matrix (" << vertices << "x" << vertices << "):\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                cin >> adjMatrix[i][j];
            }
        }
    }
    
    // Display the adjacency matrix in a nice format
    void displayMatrix() {
        cout << "\nAdjacency Matrix:\n";
        cout << "   ";
        for (int i = 0; i < vertices; i++) {
            cout << i << " ";
        }
        cout << "\n";
        
        for (int i = 0; i < vertices; i++) {
            cout << i << ": ";
            for (int j = 0; j < vertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << "\n";
        }
    }
    
    // Main DFS function - this is where the magic happens!
    bool dfsUtil(int v, int& cycleStart, int& cycleEnd) {
        visited[v] = 1;        // mark current vertex as visited
        recStack[v] = 1;       // add to recursion stack
        
        // check all adjacent vertices
        for (int u = 0; u < vertices; u++) {
            if (adjMatrix[v][u] == 1) {  // there's an edge from v to u
                if (!visited[u]) {
                    parent[u] = v;  // set parent for path reconstruction
                    if (dfsUtil(u, cycleStart, cycleEnd)) {
                        return true;  // cycle found in deeper recursion
                    }
                } else if (recStack[u]) {
                    // BINGO! Back edge found = cycle detected
                    cycleStart = u;
                    cycleEnd = v;
                    return true;
                }
            }
        }
        
        recStack[v] = 0;  // remove from recursion stack when backtracking
        return false;
    }
    
    // Reconstruct the actual cycle path from parent array
    void findCyclePath(int cycleStart, int cycleEnd) {
        cyclePath.clear();
        
        // trace back from cycleEnd to cycleStart using parent array
        vector<int> tempPath;
        int current = cycleEnd;
        
        while (current != cycleStart) {
            tempPath.push_back(current);
            current = parent[current];
        }
        
        tempPath.push_back(cycleStart);  // add the cycle start
        
        // reverse to get correct order since we traced backwards
        reverse(tempPath.begin(), tempPath.end());
        
        cyclePath = tempPath;
        cyclePath.push_back(cycleStart);  // complete the cycle
    }
    
    // Main function to check if graph has cycle
    bool hasCycle() {
        // reset all arrays for fresh detection
        fill(visited.begin(), visited.end(), 0);
        fill(recStack.begin(), recStack.end(), 0);
        fill(parent.begin(), parent.end(), -1);
        
        int cycleStart = -1, cycleEnd = -1;
        
        // try DFS from each unvisited vertex
        for (int i = 0; i < vertices; i++) {
            if (!visited[i]) {
                if (dfsUtil(i, cycleStart, cycleEnd)) {
                    findCyclePath(cycleStart, cycleEnd);
                    return true;
                }
            }
        }
        return false;
    }
    
    // Display the cycle information
    void displayCycle() {
        if (cyclePath.empty()) {
            cout << "No cycle found.\n";
            return;
        }
        
        cout << "Cycle detected! Vertices in cycle: ";
        for (int i = 0; i < cyclePath.size(); i++) {
            cout << cyclePath[i];
            if (i < cyclePath.size() - 1) {
                cout << " -> ";
            }
        }
        cout << "\n";
        
        cout << "Cycle length: " << cyclePath.size() - 1 << " edges\n";
    }
};

int main() {
    int vertices;
    
    cout << "=== DFS Cycle Detection in Directed Graph ===\n";
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    if (vertices <= 0) {
        cout << "Invalid number of vertices!\n";
        return 1;
    }
    
    CyclicDFS graph(vertices);
    
    cout << "\nChoose input method:\n";
    cout << "1. Manual adjacency matrix input\n";
    cout << "2. Predefined test case\n";
    cout << "Enter choice (1 or 2): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        graph.inputGraph();
    } else if (choice == 2) {
        // sample test case with a simple cycle
        if (vertices >= 3) {
            graph.addEdge(0, 1);  // 0 -> 1
            graph.addEdge(1, 2);  // 1 -> 2  
            graph.addEdge(2, 0);  // 2 -> 0 (completes cycle)
            cout << "Using predefined test case with cycle: 0->1->2->0\n";
        } else {
            cout << "Need at least 3 vertices for test case. Using manual input.\n";
            graph.inputGraph();
        }
    } else {
        cout << "Invalid choice. Using manual input.\n";
        graph.inputGraph();
    }
    
    graph.displayMatrix();
    
    cout << "\n=== DFS Cycle Detection Results ===\n";
    
    if (graph.hasCycle()) {
        cout << "Graph is CYCLIC!\n";
        graph.displayCycle();
    } else {
        cout << "Graph is ACYCLIC (No cycle found).\n";
    }
    
    cout << "\nAlgorithm: Depth-First Search (DFS)\n";
    cout << "Time Complexity: O(V + E) where V = vertices, E = edges\n";
    cout << "Space Complexity: O(V) for recursion stack and arrays\n";
    
    return 0;
}