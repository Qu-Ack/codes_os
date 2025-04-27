#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

// Simulates LIFO page replacement and returns page-fault count
int simulateLIFO(const vector<int> &refs, int frames) {
  vector<int> frameTable(frames, -1); // holds current pages
  unordered_set<int> inFrame;	      // quick lookup
  stack<int> lifoStack;		      // holds indices of frames by load order
  int faults = 0;

  for (int page : refs) {
    // Hit: already in memory
    if (inFrame.count(page)) {
      continue;
    }
    // Fault
    faults++;
    // Find free frame
    int idx = -1;
    for (int i = 0; i < frames; i++) {
      if (frameTable[i] == -1) {
	idx = i;
	break;
      }
    }
    if (idx == -1) {
      // No free frame: evict the most recently loaded frame
      idx = lifoStack.top();
      lifoStack.pop();
      inFrame.erase(frameTable[idx]);
    }
    // Load new page
    frameTable[idx] = page;
    inFrame.insert(page);
    lifoStack.push(idx);
  }
  return faults;
}

int main() {
  int F;
  cout << "Enter number of frames: ";
  cin >> F;

  cout << "Enter reference string (end with -1): ";
  vector<int> refs;
  while (true) {
    int p;
    cin >> p;
    if (p == -1)
      break;
    refs.push_back(p);
  }

  int faults = simulateLIFO(refs, F);
  cout << "LIFO page faults = " << faults << "\n";
  return 0;
}
