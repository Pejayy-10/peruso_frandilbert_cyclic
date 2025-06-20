/*
 * BFS Cycle Detection in Directed Graph
 * Author: [Fran Peruso] 
 * Date: [June 06 2025]
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

class CyclicBFS {
private:
    int vertices;                    // total number of vertices
    vector<vector<int>> adjMatrix;   // adjacency matrix to store graph
    vector<int> inDegree;            // in-degree of each vertex
    vector<int> cyclePath;           // vertices that are part of cycle
    
public:
    // Constructor - set up our data structures
    CyclicBFS(int v) : vertices(v) {
        adjMatrix.resize(v, vector<int>(v, 0));
        inDegree.resize(v, 0);
    }
    
    // Add edge and update in-degree
    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        inDegree[v]++;  // destination vertex in-degree increases
    }
    
    // Get graph input from user
    void inputGraph() {
        cout << "Enter the adjacency matrix (" << vertices << "x" << vertices << "):\n";
        for (int i = 0; i < vertices; i++) {
            for (int j = 0; j < vertices; j++) {
                cin >> adjMatrix[i][j];
                if (adjMatrix[i][j] == 1) {
                    inDegree[j]++;  // count incoming edges
                }
            }
        }
    }
    
    // Display matrix and in-degrees for debugging
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
        
        cout << "\nIn-degrees: ";
        for (int i = 0; i < vertices; i++) {
            cout << "v" << i << "(" << inDegree[i] << ") ";
        }
        cout << "\n";
    }
    
    // Kahn's Algorithm - the heart of our BFS cycle detection
    bool hasCycleKahn() {
        vector<int> tempInDegree = inDegree;  // copy so we don't mess up original
        queue<int> q;
        vector<int> topoOrder;  // topological order result
        
        // start with all vertices having in-degree 0
        for (int i = 0; i < vertices; i++) {
            if (tempInDegree[i] == 0) {
                q.push(i);
            }
        }
        
        cout << "\nKahn's Algorithm Process:\n";
        int step = 1;
        
        // keep processing until queue is empty
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            topoOrder.push_back(u);
            
            cout << "Step " << step++ << ": Processing vertex " << u << "\n";
            
            // for each neighbor of u, reduce their in-degree
            for (int v = 0; v < vertices; v++) {
                if (adjMatrix[u][v] == 1) {  // edge from u to v exists
                    tempInDegree[v]--;
                    cout << "  Reduced in-degree of vertex " << v << " to " << tempInDegree[v] << "\n";
                    
                    // if in-degree becomes 0, add to queue
                    if (tempInDegree[v] == 0) {
                        q.push(v);
                        cout << "  Added vertex " << v << " to queue\n";
                    }
                }
            }
        }
        
        cout << "\nVertices processed: " << topoOrder.size() << "/" << vertices << "\n";
        
        // here's the key insight!
        if (topoOrder.size() == vertices) {
            // we processed all vertices = no cycle
            cout << "Topological order: ";
            for (int i = 0; i < topoOrder.size(); i++) {
                cout << topoOrder[i];
                if (i < topoOrder.size() - 1) cout << " -> ";
            }
            cout << "\n";
            return false;
        } else {
            // couldn't process all vertices = cycle exists!
            vector<bool> processed(vertices, false);
            for (int v : topoOrder) {
                processed[v] = true;
            }
            
            cout << "Vertices in cycle: ";
            cyclePath.clear();
            for (int i = 0; i < vertices; i++) {
                if (!processed[i]) {
                    cyclePath.push_back(i);
                    cout << i << " ";
                }
            }
            cout << "\n";
            
            return true;
        }
    }
    
    // Find strongly connected components to identify cycle better
    void findStronglyConnectedComponents() {
        vector<bool> visited(vertices, false);
        vector<int> component;
        
        // check each unprocessed vertex in our cycle
        for (int start : cyclePath) {
            if (!visited[start]) {
                component.clear();
                dfsComponent(start, visited, component);
                
                if (component.size() > 1) {
                    cout << "Strongly connected component (cycle): ";
                    for (int v : component) {
                        cout << v << " ";
                    }
                    cout << "\n";
                    
                    findCyclePath(component);
                    break;
                }
            }
        }
    }
    
    // DFS to find connected components
    void dfsComponent(int v, vector<bool>& visited, vector<int>& component) {
        visited[v] = true;
        component.push_back(v);
        
        for (int u = 0; u < vertices; u++) {
            if (adjMatrix[v][u] == 1 && !visited[u]) {
                // only visit if it's in our suspected cycle vertices
                if (find(cyclePath.begin(), cyclePath.end(), u) != cyclePath.end()) {
                    dfsComponent(u, visited, component);
                }
            }
        }
    }
    
    // Try to trace the actual cycle path
    void findCyclePath(vector<int>& component) {
        cout << "Tracing actual cycle path:\n";
        
        if (component.size() < 2) return;
        
        // sort component for easier processing
        sort(component.begin(), component.end());
        
        vector<int> path;
        vector<bool> visited(vertices, false);
        
        // start DFS from first vertex in component
        int start = component[0];
        if (dfsForCycle(start, start, component, path, visited, 0)) {
            cout << "Complete cycle path: ";
            for (int i = 0; i < path.size(); i++) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << "\n";
        } else {
            cout << "Cycle exists among these vertices: ";
            for (int v : component) {
                cout << v << " ";
            }
            cout << "\n";
        }
    }
    
    // DFS helper to find actual cycle path
    bool dfsForCycle(int current, int target, vector<int>& component, vector<int>& path, vector<bool>& visited, int depth) {
        path.push_back(current);
        
        if (depth > 0 && current == target) {
            return true; // found complete cycle!
        }
        
        if (depth >= component.size()) {
            path.pop_back();
            return false; // avoid infinite loops
        }
        
        visited[current] = true;
        
        // check all neighbors
        for (int next = 0; next < vertices; next++) {
            if (adjMatrix[current][next] == 1) {
                // only consider vertices in the same component
                if (find(component.begin(), component.end(), next) != component.end()) {
                    if (next == target && depth > 0) {
                        path.push_back(next);
                        return true;
                    }
                    if (!visited[next]) {
                        if (dfsForCycle(next, target, component, path, visited, depth + 1)) {
                            return true;
                        }
                    }
                }
            }
        }
        
        visited[current] = false;
        path.pop_back();
        return false;
    }
    
    // Display cycle results
    void displayCycle() {
        if (cyclePath.empty()) {
            cout << "No cycle vertices identified.\n";
            return;
        }
        
        cout << "\nCycle Analysis:\n";
        cout << "Vertices involved in cycle: ";
        for (int v : cyclePath) {
            cout << v << " ";
        }
        cout << "\n";
        
        findStronglyConnectedComponents();
    }
};

int main() {
    int vertices;
    
    cout << "=== BFS Cycle Detection in Directed Graph ===\n";
    cout << "Enter number of vertices: ";
    cin >> vertices;
    
    if (vertices <= 0) {
        cout << "Invalid number of vertices!\n";
        return 1;
    }
    
    CyclicBFS graph(vertices);
    
    cout << "\nChoose input method:\n";
    cout << "1. Manual adjacency matrix input\n";
    cout << "2. Predefined test case\n";
    cout << "Enter choice (1 or 2): ";
    
    int choice;
    cin >> choice;
    
    if (choice == 1) {
        graph.inputGraph();
    } else if (choice == 2) {
        // simple test case for demonstration
        if (vertices >= 3) {
            graph.addEdge(0, 1);  // create cycle 0->1->2->0
            graph.addEdge(1, 2);
            graph.addEdge(2, 0);
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
    
    cout << "\n=== BFS Cycle Detection Results ===\n";
    
    if (graph.hasCycleKahn()) {
        cout << "\nGraph is CYCLIC!\n";
        graph.displayCycle();
    } else {
        cout << "\nGraph is ACYCLIC (No cycle found).\n";
    }
    
    cout << "\nAlgorithm: BFS (Kahn's Algorithm for Topological Sort)\n";
    cout << "Principle: If topological sort can't process all vertices, cycle exists\n";
    cout << "Time Complexity: O(V + E) - same as DFS but different approach\n";
    cout << "Space Complexity: O(V) for queue and arrays\n";
    
    return 0;
}