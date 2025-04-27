#include <bits/stdc++.h>
using namespace std;

void LOOK(vector<int> req, int head, string dir) {
  vector<int> left, right;
  for (int r : req) {
    if (r < head)
      left.push_back(r);
    else
      right.push_back(r);
  }
  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int seek = 0;
  cout << "LOOK service order: ";
  if (dir == "left") {
    for (int i = left.size() - 1; i >= 0; i--) {
      cout << left[i] << " ";
      seek += abs(head - left[i]);
      head = left[i];
    }
    for (int r : right) {
      cout << r << " ";
      seek += abs(head - r);
      head = r;
    }
  } else {
    for (int r : right) {
      cout << r << " ";
      seek += abs(head - r);
      head = r;
    }
    for (int i = left.size() - 1; i >= 0; i--) {
      cout << left[i] << " ";
      seek += abs(head - left[i]);
      head = left[i];
    }
  }
  cout << "\nTotal head movement = " << seek << "\n\n";
}
