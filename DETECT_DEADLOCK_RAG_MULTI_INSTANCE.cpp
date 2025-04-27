#include <vector>
using namespace std;

vector<int> detect_deadlock(const vector<int> &available,
			    const vector<vector<int>> &allocation,
			    const vector<vector<int>> &request) {
  int n_processes = allocation.size();
  vector<int> deadlocked;
  if (n_processes == 0)
    return deadlocked;

  int n_resources = available.size();
  vector<int> work = available;
  vector<bool> finish(n_processes, false);

  bool found;
  do {
    found = false;
    for (int p = 0; p < n_processes; ++p) {
      if (!finish[p]) {
	bool can_allocate = true;
	// Check if all requested resources can be satisfied
	for (int r = 0; r < n_resources; ++r) {
	  if (request[p][r] > work[r]) {
	    can_allocate = false;
	    break;
	  }
	}

	if (can_allocate) {
	  // Release allocated resources
	  for (int r = 0; r < n_resources; ++r) {
	    work[r] += allocation[p][r];
	  }
	  finish[p] = true;
	  found = true;
	  break; // Restart search after state change
	}
      }
    }
  } while (found);

  // Collect deadlocked processes
  for (int p = 0; p < n_processes; ++p) {
    if (!finish[p]) {
      deadlocked.push_back(p);
    }
  }

  return deadlocked;
}

// Example usage:
#include <iostream>

void print_result(const vector<int> &result) {
  cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    cout << result[i];
    if (i < result.size() - 1)
      cout << ", ";
  }
  cout << "]" << endl;
}

int main() {
  // Example 1: No deadlock
  vector<int> available1 = {0, 0, 0};
  vector<vector<int>> allocation1 = {
      {0, 1, 0}, {2, 0, 0}, {3, 0, 3}, {2, 1, 1}, {0, 0, 2},
  };
  vector<vector<int>> request1 = {
      {0, 0, 0}, {2, 0, 2}, {0, 0, 0}, {1, 0, 0}, {0, 0, 2},
  };
  vector<int> result1 = detect_deadlock(available1, allocation1, request1);
  print_result(result1); // Output: []

  // Example 2: Deadlock present
  vector<int> available2 = {0, 0, 1};
  vector<vector<int>> allocation2 = {{1, 0, 0}, {0, 1, 0}};
  vector<vector<int>> request2 = {{0, 1, 0}, {1, 0, 0}};
  vector<int> result2 = detect_deadlock(available2, allocation2, request2);
  print_result(result2); // Output: [0, 1]

  return 0;
}
