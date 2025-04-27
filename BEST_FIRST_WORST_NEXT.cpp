#include <climits>
#include <iostream>
#include <vector>
using namespace std;

// First Fit: allocate to the first hole that fits
vector<int> firstFit(const vector<int> &blockSize,
		     const vector<int> &procSize) {
  int m = blockSize.size(), n = procSize.size();
  vector<int> alloc(n, -1);
  vector<bool> used(m, false);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (!used[j] && blockSize[j] >= procSize[i]) {
	alloc[i] = j;
	used[j] = true;
	break;
      }
    }
  }
  return alloc;
}

// Next Fit: resume search from last allocated index
vector<int> nextFit(const vector<int> &blockSize, const vector<int> &procSize) {
  int m = blockSize.size(), n = procSize.size();
  vector<int> alloc(n, -1);
  vector<bool> used(m, false);
  int start = 0;
  for (int i = 0; i < n; i++) {
    int cnt = 0, j = start;
    while (cnt < m) {
      if (!used[j] && blockSize[j] >= procSize[i]) {
	alloc[i] = j;
	used[j] = true;
	start = j; // next search starts here
	break;
      }
      j = (j + 1) % m;
      cnt++;
    }
  }
  return alloc;
}

// Best Fit: choose hole that leaves smallest leftover
vector<int> bestFit(const vector<int> &blockSize, const vector<int> &procSize) {
  int m = blockSize.size(), n = procSize.size();
  vector<int> alloc(n, -1);
  vector<bool> used(m, false);
  for (int i = 0; i < n; i++) {
    int bestIdx = -1, minDiff = INT_MAX;
    for (int j = 0; j < m; j++) {
      int diff = blockSize[j] - procSize[i];
      if (!used[j] && diff >= 0 && diff < minDiff) {
	minDiff = diff;
	bestIdx = j;
      }
    }
    if (bestIdx != -1) {
      alloc[i] = bestIdx;
      used[bestIdx] = true;
    }
  }
  return alloc;
}

// Worst Fit: choose hole that leaves largest leftover
vector<int> worstFit(const vector<int> &blockSize,
		     const vector<int> &procSize) {
  int m = blockSize.size(), n = procSize.size();
  vector<int> alloc(n, -1);
  vector<bool> used(m, false);
  for (int i = 0; i < n; i++) {
    int worstIdx = -1, maxDiff = -1;
    for (int j = 0; j < m; j++) {
      int diff = blockSize[j] - procSize[i];
      if (!used[j] && diff >= 0 && diff > maxDiff) {
	maxDiff = diff;
	worstIdx = j;
      }
    }
    if (worstIdx != -1) {
      alloc[i] = worstIdx;
      used[worstIdx] = true;
    }
  }
  return alloc;
}

// Utility to print allocation table
void printAlloc(const string &name, const vector<int> &blockSize,
		const vector<int> &procSize, const vector<int> &alloc) {
  cout << name << " Allocation:\n";
  cout << "Proc#\tSize\tBlock#\tBlkSize\tFrag\n";
  int totalFrag = 0;
  for (int i = 0; i < (int)procSize.size(); i++) {
    int b = alloc[i];
    int frag = (b == -1 ? 0 : blockSize[b] - procSize[i]);
    totalFrag += frag;
    cout << i << "\t" << procSize[i] << "\t" << (b == -1 ? -1 : b) << "\t"
	 << (b == -1 ? 0 : blockSize[b]) << "\t" << frag << "\n";
  }
  cout << "Total internal fragmentation = " << totalFrag << "\n\n";
}

int main() {
  int m, n;
  cout << "Enter #blocks and #processes: ";
  cin >> m >> n;
  vector<int> blockSize(m), procSize(n);
  cout << "Enter block sizes:\n";
  for (int &b : blockSize)
    cin >> b;
  cout << "Enter process sizes:\n";
  for (int &p : procSize)
    cin >> p;

  // Run all strategies
  printAlloc("First Fit", blockSize, procSize, firstFit(blockSize, procSize));
  printAlloc("Next Fit", blockSize, procSize, nextFit(blockSize, procSize));
  printAlloc("Best Fit", blockSize, procSize, bestFit(blockSize, procSize));
  printAlloc("Worst Fit", blockSize, procSize, worstFit(blockSize, procSize));
  return 0;
}
