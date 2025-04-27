#include <bits/stdc++.h>
using namespace std;

void C_LOOK(vector<int> req, int head, string dir) {
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
  cout << "C-LOOK service order: ";
  if (dir == "left") {
    for (int i = left.size() - 1; i >= 0; i--) {
      cout << left[i] << " ";
      seek += abs(head - left[i]);
      head = left[i];
    }
    // jump to highest on right
    head = right.back();
    cout << head << " ";
    for (int i = right.size() - 2; i >= 0; i--) {
      cout << right[i] << " ";
      seek += abs(head - right[i]);
      head = right[i];
    }
  } else {
    for (int r : right) {
      cout << r << " ";
      seek += abs(head - r);
      head = r;
    }
    // jump to lowest on left
    head = left.front();
    cout << head << " ";
    for (size_t i = 1; i < left.size(); i++) {
      cout << left[i] << " ";
      seek += abs(head - left[i]);
      head = left[i];
    }
  }
  cout << "\nTotal head movement = " << seek << "\n\n";
}
