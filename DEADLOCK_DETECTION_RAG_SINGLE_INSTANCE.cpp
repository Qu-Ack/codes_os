#include <iostream>
#include <vector>
using namespace std;

// Perform DFS to detect a cycle starting from node u
bool dfsCycle(int u, const vector<vector<int>> &adj, vector<bool> &visited,
	      vector<bool> &inStack) {
  visited[u] = true;
  inStack[u] = true;
  for (int v : adj[u]) {
    if (!visited[v] && dfsCycle(v, adj, visited, inStack))
      return true;
    if (inStack[v])
      return true; // back-edge found → cycle
  }
  inStack[u] = false;
  return false;
}

// Build RAG and detect deadlock
bool detectDeadlock(int P, int R, const vector<pair<int, int>> &req,
		    const vector<pair<int, int>> &alloc) {
  int totalNodes = P + R;
  vector<vector<int>> adj(totalNodes);
  // Map: processes 0..P-1, resources P..P+R-1

  // Add request edges P_i → R_j
  for (auto &e : req) {
    int pi = e.first;
    int rj = P + e.second;
    adj[pi].push_back(rj);
  }
  // Add allocation edges R_j → P_k
  for (auto &e : alloc) {
    int rj = P + e.first;
    int pk = e.second;
    adj[rj].push_back(pk);
  }

  // DFS cycle detection on entire graph
  vector<bool> visited(totalNodes, false), inStack(totalNodes, false);
  for (int u = 0; u < totalNodes; u++) {
    if (!visited[u] && dfsCycle(u, adj, visited, inStack))
      return true;
  }
  return false;
}

int main() {
  int P, R;
  cin >> P >> R; // #processes, #resources
  int nr;
  cin >> nr; // #request edges
  vector<pair<int, int>> req(nr);
  for (int i = 0; i < nr; i++)
    cin >> req[i].first >> req[i].second;
  int na;
  cin >> na; // #allocation edges
  vector<pair<int, int>> alloc(na);
  for (int i = 0; i < na; i++)
    cin >> alloc[i].first >> alloc[i].second;

  bool deadlock = detectDeadlock(P, R, req, alloc);
  cout << (deadlock ? "Deadlock detected\n" : "No deadlock\n");
  return 0;
}
