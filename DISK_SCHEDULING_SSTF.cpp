#include <bits/stdc++.h>
using namespace std;

void SSTF(vector<int> req, int head) {
  int n = req.size(), seek = 0;
  vector<bool> done(n, false);

  for (int i = 0; i < n; i++) {
    int best = -1, bestDist = INT_MAX;
    for (int j = 0; j < n; j++) {
      int d = abs(req[j] - head);
      if (!done[j] && d < bestDist) {
	bestDist = d;
	best = j;
      }
    }
    done[best] = true;
    cout << req[best] << " ";
    seek += bestDist;
    head = req[best];
  }
  cout << "\nTotal head movement = " << seek << "\n\n";
}
