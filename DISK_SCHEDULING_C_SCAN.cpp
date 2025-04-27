#include <bits/stdc++.h>
using namespace std;

void C_SCAN(vector<int> req, int head, int disk_size, string dir) {
  vector<int> left, right;
  for (int r : req) {
    if (r < head)
      left.push_back(r);
    else
      right.push_back(r);
  }
  left.push_back(0);
  right.push_back(disk_size - 1);
  sort(left.begin(), left.end());
  sort(right.begin(), right.end());

  int seek = 0;
  cout << "C-SCAN service order: ";
  if (dir == "left") {
    // go left
    for (int i = left.size() - 1; i >= 0; i--) {
      cout << left[i] << " ";
      seek += abs(head - left[i]);
      head = left[i];
    }
    // jump to right end
    head = disk_size - 1;
    cout << head << " ";
    // then service right side downward
    for (int i = right.size() - 1; i >= 0; i--) {
      cout << right[i] << " ";
      seek += abs(head - right[i]);
      head = right[i];
    }
  } else {
    // go right
    for (int r : right) {
      cout << r << " ";
      seek += abs(head - r);
      head = r;
    }
    // jump to left end
    head = 0;
    cout << head << " ";
    for (int r : left) {
      cout << r << " ";
      seek += abs(head - r);
      head = r;
    }
  }
  cout << "\nTotal head movement = " << seek << "\n\n";
}
