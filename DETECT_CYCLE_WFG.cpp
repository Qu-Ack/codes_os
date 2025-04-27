#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>
using namespace std;

class WaitForGraph {
private:
  unordered_map<int, vector<int>> graph;

  // DFS to detect cycle
  bool hasCycleUtil(int node, set<int> &visited, set<int> &recStack) {
    // Mark current node as visited and add to recursion stack
    visited.insert(node);
    recStack.insert(node);

    // Visit all adjacent vertices
    for (int neighbor : graph[node]) {
      // If not visited, recursively check for cycles
      if (visited.find(neighbor) == visited.end()) {
	if (hasCycleUtil(neighbor, visited, recStack))
	  return true;
      }
      // If already in recursion stack, we found a cycle
      else if (recStack.find(neighbor) != recStack.end()) {
	return true;
      }
    }

    // Remove node from recursion stack before returning
    recStack.erase(node);
    return false;
  }

public:
  // Add an edge from process 'from' waiting for resource held by process 'to'
  void addEdge(int from, int to) {
    graph[from].push_back(to);

    // Make sure 'to' node exists in graph even if it has no outgoing edges
    if (graph.find(to) == graph.end()) {
      graph[to] = vector<int>();
    }
  }

  // Check if the wait-for graph has a cycle (indicates potential deadlock)
  bool hasCycle() {
    set<int> visited;
    set<int> recStack;

    // Check all vertices (some might be disconnected)
    for (auto &pair : graph) {
      int node = pair.first;
      if (visited.find(node) == visited.end()) {
	if (hasCycleUtil(node, visited, recStack))
	  return true;
      }
    }
    return false;
  }

  // Print the graph
  void printGraph() {
    for (auto &pair : graph) {
      cout << "Process " << pair.first << " is waiting for: ";
      for (int neighbor : pair.second) {
	cout << neighbor << " ";
      }
      cout << endl;
    }
  }
};

int main() {
  WaitForGraph g;

  // Example: Process 1 waits for 2, 2 waits for 3, and 3 waits for 1 (cycle)
  g.addEdge(1, 2);
  g.addEdge(2, 3);
  g.addEdge(3, 1);

  cout << "Wait-For Graph:" << endl;
  g.printGraph();

  if (g.hasCycle()) {
    cout << "Cycle detected! Potential deadlock exists." << endl;
  } else {
    cout << "No cycle detected. No deadlock." << endl;
  }

  // Create a graph without cycle
  WaitForGraph g2;
  g2.addEdge(1, 2);
  g2.addEdge(2, 3);
  g2.addEdge(4, 1);

  cout << "\nSecond Wait-For Graph:" << endl;
  g2.printGraph();

  if (g2.hasCycle()) {
    cout << "Cycle detected! Potential deadlock exists." << endl;
  } else {
    cout << "No cycle detected. No deadlock." << endl;
  }

  return 0;
}
